// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUIApp/Window.h>

#include <tgCore/Timer.h>

#include <array>

namespace tg
{
    namespace examples
    {
        namespace gol
        {
            class Window : public ui::Window
            {
            protected:
                void _init(
                    const std::shared_ptr<core::Context>&,
                    const std::string& name,
                    const core::Size2I&);

            public:
                virtual ~Window();

                static std::shared_ptr<Window> create(
                    const std::shared_ptr<core::Context>&,
                    const std::string& name,
                    const core::Size2I&);

                void setGeometry(const core::Box2I&) override;
                void sizeHintEvent(const ui::SizeHintEvent&) override;
                void drawEvent(const core::Box2I&, const ui::DrawEvent&) override;

            private:
                core::V2I _wrap(const core::V2I&) const;
                uint8_t _getCell(size_t index, const core::V2I&) const;
                void _setCell(size_t index, const core::V2I&, uint8_t);
                void _randomize(size_t index);
                void _tick();

                int _cellSize = 0;
                core::Size2I _cellsSize;
                std::array<std::vector<uint8_t>, 2> _cells;
                size_t _currentCells = 0;
                double _noiseZ = 0.0;
                std::shared_ptr<core::Timer> _timer;
                std::shared_ptr<core::Timer> _timer2;
            };
        }
    }
}

