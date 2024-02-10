// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCore/Command.h>

namespace tg
{
    namespace core
    {
        ICommand::~ICommand()
        {}

        struct CommandStack::Private
        {
            std::vector<std::shared_ptr<ICommand> > commands;
            int64_t currentIndex = -1;
            std::shared_ptr<ObservableValue<bool> > hasUndo;
            std::shared_ptr<ObservableValue<bool> > hasRedo;
        };

        CommandStack::CommandStack() :
            _p(new Private)
        {
            TG_P();
            p.hasUndo = ObservableValue<bool>::create(false);
            p.hasRedo = ObservableValue<bool>::create(false);
        }

        CommandStack::~CommandStack()
        {}

        std::shared_ptr<CommandStack> CommandStack::create()
        {
            auto out = std::shared_ptr<CommandStack>(new CommandStack);
            return out;
        }

        void CommandStack::push(const std::shared_ptr<ICommand>&command)
        {
            TG_P();
            while (static_cast<int64_t>(p.commands.size()) - 1 > p.currentIndex)
            {
                p.commands.pop_back();
            }
            p.commands.push_back(command);
            p.currentIndex = p.currentIndex + 1;
            command->exec();
            p.hasUndo->setIfChanged(true);
        }

        std::shared_ptr<IObservableValue<bool> > CommandStack::observeHasUndo() const
        {
            return _p->hasUndo;
        }

        std::shared_ptr<IObservableValue<bool> > CommandStack::observeHasRedo() const
        {
            return _p->hasRedo;
        }

        void CommandStack::undo()
        {
            TG_P();
            if (p.commands.size() && p.currentIndex >= 0)
            {
                p.commands[p.currentIndex]->undo();
                p.currentIndex = p.currentIndex - 1;
                p.hasUndo->setIfChanged(p.currentIndex >= 0);
                p.hasRedo->setIfChanged(p.currentIndex < static_cast<int64_t>(p.commands.size()) - 1);
            }
        }

        void CommandStack::redo()
        {
            TG_P();
            if (p.commands.size() && p.currentIndex < static_cast<int64_t>(p.commands.size()) - 1)
            {
                const int64_t index = p.currentIndex + 1;
                p.commands[index]->exec();
                p.currentIndex = index;
                p.hasUndo->setIfChanged(p.currentIndex >= 0);
                p.hasRedo->setIfChanged(p.currentIndex < static_cast<int64_t>(p.commands.size()) - 1);
            }
        }

        void CommandStack::clear()
        {
            TG_P();
            if (!p.commands.empty())
            {
                p.commands.clear();
                p.currentIndex = -1;
                p.hasUndo->setIfChanged(false);
                p.hasRedo->setIfChanged(false);
            }
        }
    }
}
