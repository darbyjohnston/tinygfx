// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/DragAndDropTest.h>

#include <tgUITest/App.h>
#include <tgUITest/Window.h>

#include <tgUI/RowLayout.h>
#include <tgUI/Spacer.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        namespace
        {
            class DragAndDropData : public ui::DragAndDropData
            {
            public:
                DragAndDropData(int value) :
                    _number(value)
                {}

                virtual ~DragAndDropData()
                {}

                int getNumber() const
                {
                    return _number;
                }

            private:
                int _number = 0;
            };

            class DragAndDropWidget : public ui::IWidget
            {
            protected:
                void _init(
                    const std::shared_ptr<core::Context>&,
                    int number,
                    const std::shared_ptr<IWidget>& parent);

                DragAndDropWidget() = default;

            public:
                virtual ~DragAndDropWidget();

                static std::shared_ptr<DragAndDropWidget> create(
                    const std::shared_ptr<core::Context>&,
                    int number,
                    const std::shared_ptr<IWidget>& parent = nullptr);

                int getNumber() const;

                void sizeHintEvent(const ui::SizeHintEvent&) override;
                void mouseMoveEvent(ui::MouseMoveEvent&) override;
                void dragEnterEvent(ui::DragAndDropEvent&) override;
                void dragLeaveEvent(ui::DragAndDropEvent&) override;
                void dropEvent(ui::DragAndDropEvent&) override;

            private:
                int _number = 0;
                int _dragLength = 0;
                bool _dropTarget = false;;
            };

            void DragAndDropWidget::_init(
                const std::shared_ptr<Context>& context,
                int number,
                const std::shared_ptr<IWidget>& parent)
            {
                IWidget::_init(context, "tg::examples::dnd::DragAndDropWidget", parent);

                setStretch(Stretch::Expanding);

                _setMouseHoverEnabled(true);
                _setMousePressEnabled(true);

                _number = number;
            }

            DragAndDropWidget::~DragAndDropWidget()
            {}

            std::shared_ptr<DragAndDropWidget> DragAndDropWidget::create(
                const std::shared_ptr<Context>& context,
                int number,
                const std::shared_ptr<IWidget>& parent)
            {
                auto out = std::shared_ptr<DragAndDropWidget>(new DragAndDropWidget);
                out->_init(context, number, parent);
                return out;
            }

            int DragAndDropWidget::getNumber() const
            {
                return _number;
            }

            void DragAndDropWidget::sizeHintEvent(const SizeHintEvent& event)
            {
                IWidget::sizeHintEvent(event);
                _dragLength = event.style->getSizeRole(SizeRole::DragLength, event.displayScale);
                _setSizeHint(Size2I(100, 100));
            }

            void DragAndDropWidget::mouseMoveEvent(MouseMoveEvent& event)
            {
                IWidget::mouseMoveEvent(event);
                if (_isMousePressed())
                {
                    const float length = core::length(event.pos - _getMousePressPos());
                    if (length > _dragLength)
                    {
                        event.dndData = std::make_shared<DragAndDropData>(_number);
                        const Box2I& g = getGeometry();
                        const int w = g.w();
                        const int h = g.h();
                        event.dndCursor = Image::create(w, h, ImageType::RGBA_U8);
                        uint8_t* p = event.dndCursor->getData();
                        for (int y = 0; y < h; ++y)
                        {
                            for (int x = 0; x < w; ++x)
                            {
                                p[0] = 255;
                                p[1] = 255;
                                p[2] = 255;
                                p[3] = 63;
                                p += 4;
                            }
                        }
                        event.dndCursorHotspot = _getMousePos() - g.min;
                    }
                }
            }

            void DragAndDropWidget::dragEnterEvent(DragAndDropEvent& event)
            {
                event.accept = true;
                _dropTarget = true;
            }

            void DragAndDropWidget::dragLeaveEvent(DragAndDropEvent& event)
            {
                event.accept = true;
                _dropTarget = false;
            }

            void DragAndDropWidget::dropEvent(DragAndDropEvent& event)
            {
                if (auto data = std::dynamic_pointer_cast<DragAndDropData>(event.data))
                {
                    event.accept = true;
                    _number = data->getNumber();
                }
            }
        }

        DragAndDropTest::DragAndDropTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::DragAndDropTest")
        {}

        DragAndDropTest::~DragAndDropTest()
        {}

        std::shared_ptr<DragAndDropTest> DragAndDropTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<DragAndDropTest>(new DragAndDropTest(context));
        }
                
        void DragAndDropTest::run()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("DragAndDropTest");
                auto app = App::create(
                    context,
                    argv,
                    "DragAndDropTest",
                    "Drag and drop test.");
                auto window = Window::create(context, app, "DragAndDropTest");
                auto layout = HorizontalLayout::create(context, window);
                auto dndWidget0 = DragAndDropWidget::create(context, 0, layout);
                auto dndWidget1 = DragAndDropWidget::create(context, 1, layout);
                auto spacer = Spacer::create(context, Orientation::Horizontal, layout);
                spacer->setStretch(Stretch::Expanding);
                app->addWindow(window);
                window->show();
                app->tick();

                window->setCursorEnter(true);
                window->setCursorPos(center(dndWidget0->getGeometry()));
                window->setButton(0, true);
                window->setCursorPos(center(dndWidget1->getGeometry()));
                window->setCursorPos(center(dndWidget1->getGeometry()));
                window->setButton(0, false);
                TG_ASSERT(0 == dndWidget1->getNumber());

                window->setCursorPos(center(dndWidget0->getGeometry()));
                window->setButton(0, true);
                window->setCursorPos(center(spacer->getGeometry()));
                window->setCursorPos(center(spacer->getGeometry()));
                window->setButton(0, false);

                window->setCursorPos(center(dndWidget0->getGeometry()));
                window->setButton(0, true, 0);
                window->setCursorPos(center(dndWidget1->getGeometry()));
                window->setCursorPos(center(dndWidget1->getGeometry()));
                window->hide();
                window->show();
            }
        }
    }
}
