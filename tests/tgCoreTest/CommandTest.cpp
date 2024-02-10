// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCoreTest/CommandTest.h>

#include <tgCore/Assert.h>
#include <tgCore/Command.h>

using namespace tg::core;

namespace tg
{
    namespace core_test
    {
        CommandTest::CommandTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::core_test::CommandTest")
        {}

        CommandTest::~CommandTest()
        {}

        std::shared_ptr<CommandTest> CommandTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<CommandTest>(new CommandTest(context));
        }
        
        namespace
        {
            struct Data
            {
                int value = 0;
            };

            class AddCommand : public ICommand
            {
            public:
                AddCommand(
                    int value,
                    const std::shared_ptr<Data>& data) :
                    _value(value),
                    _data(data)
                {}

                virtual ~AddCommand() {}

                void exec() override
                {
                    _data->value += _value;
                }
                void undo() override
                {
                    _data->value -= _value;
                }

            private:
                int _value = 0;
                std::shared_ptr<Data> _data;
            };
        }

        void CommandTest::run()
        {
            {
                auto data = std::make_shared<Data>();

                auto commandStack = CommandStack::create();
                bool hasUndo = false;
                bool hasRedo = false;
                auto undoObserver = ValueObserver<bool>::create(
                    commandStack->observeHasUndo(),
                    [&hasUndo](bool value)
                    {
                        hasUndo = value;
                    });
                auto redoObserver = ValueObserver<bool>::create(
                    commandStack->observeHasRedo(),
                    [&hasRedo](bool value)
                    {
                        hasRedo = value;
                    });
                TG_ASSERT(!hasUndo);
                TG_ASSERT(!hasRedo);

                commandStack->push(std::make_shared<AddCommand>(1, data));
                commandStack->push(std::make_shared<AddCommand>(2, data));
                commandStack->push(std::make_shared<AddCommand>(3, data));
                TG_ASSERT(6 == data->value);
                TG_ASSERT(hasUndo);

                commandStack->undo();
                TG_ASSERT(3 == data->value);
                TG_ASSERT(hasRedo);
                commandStack->redo();
                TG_ASSERT(6 == data->value);
                commandStack->undo();
                TG_ASSERT(3 == data->value);

                commandStack->undo();
                TG_ASSERT(1 == data->value);
                commandStack->undo();
                TG_ASSERT(0 == data->value);
                TG_ASSERT(!hasUndo);

                commandStack->redo();
                TG_ASSERT(1 == data->value);
                commandStack->redo();
                TG_ASSERT(3 == data->value);
                commandStack->redo();
                TG_ASSERT(6 == data->value);

                commandStack->clear();
                TG_ASSERT(!hasUndo);
                TG_ASSERT(!hasRedo);
            }
        }
    }
}

