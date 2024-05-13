// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include "dnd.h"

#include <tgUIApp/App.h>

#include <tgUI/DrawUtil.h>
#include <tgUI/GridLayout.h>
#include <tgUI/ScrollWidget.h>

#include <iomanip>
#include <sstream>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace examples
    {
        namespace dnd
        {
            DragAndDropData::DragAndDropData(int value) :
                _number(value)
            {}

            DragAndDropData::~DragAndDropData()
            {}

            int DragAndDropData::getNumber() const
            {
                return _number;
            }

            void DragAndDropWidget::_init(
                const std::shared_ptr<Context>& context,
                int number,
                const std::shared_ptr<IWidget>& parent)
            {
                IWidget::_init(context, "tg::examples::dnd::DragAndDropWidget", parent);

                _setMouseHoverEnabled(true);
                _setMousePressEnabled(true);

                _number = number;

                _label = Label::create(context, shared_from_this());
                _label->setHAlign(HAlign::Center);
                _label->setVAlign(VAlign::Center);
                _label->setMarginRole(SizeRole::Margin);

                _textUpdate();
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

            void DragAndDropWidget::setGeometry(const Box2I& value)
            {
                IWidget::setGeometry(value);
                _label->setGeometry(getGeometry());
            }

            void DragAndDropWidget::sizeHintEvent(const SizeHintEvent& event)
            {
                IWidget::sizeHintEvent(event);
                _border = event.style->getSizeRole(SizeRole::Border, event.displayScale);
                _dragLength = event.style->getSizeRole(SizeRole::DragLength, event.displayScale);
                _setSizeHint(_label->getSizeHint());
            }

            void DragAndDropWidget::drawEvent(
                const Box2I& drawRect,
                const DrawEvent& event)
            {
                IWidget::drawEvent(drawRect, event);

                const Box2I& g = getGeometry();
                event.render->drawMesh(
                    border(g, _border),
                    event.style->getColorRole(ColorRole::Border));

                const Box2I g2 = margin(g, -_border);
                event.render->drawRect(
                    convert(g2),
                    event.style->getColorRole(ColorRole::Button));

                if (_isMousePressed())
                {
                    event.render->drawRect(
                        convert(g2),
                        event.style->getColorRole(ColorRole::Pressed));
                }
                else if (_isMouseInside())
                {
                    event.render->drawRect(
                        convert(g2),
                        event.style->getColorRole(ColorRole::Hover));
                }

                if (_dropTarget)
                {
                    auto color = event.style->getColorRole(ColorRole::Checked);
                    color.a = .5F;
                    event.render->drawRect(convert(g2), color);
                }
            }

            void DragAndDropWidget::mouseEnterEvent()
            {
                IWidget::mouseEnterEvent();
                _setDrawUpdate();
            }

            void DragAndDropWidget::mouseLeaveEvent()
            {
                IWidget::mouseLeaveEvent();
                _setDrawUpdate();
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

            void DragAndDropWidget::mousePressEvent(MouseClickEvent& event)
            {
                IWidget::mousePressEvent(event);
                _setDrawUpdate();
            }

            void DragAndDropWidget::mouseReleaseEvent(MouseClickEvent& event)
            {
                IWidget::mouseReleaseEvent(event);
                _setDrawUpdate();
            }

            void DragAndDropWidget::dragEnterEvent(DragAndDropEvent& event)
            {
                event.accept = true;
                _dropTarget = true;
                _setDrawUpdate();
            }

            void DragAndDropWidget::dragLeaveEvent(DragAndDropEvent& event)
            {
                event.accept = true;
                _dropTarget = false;
                _setDrawUpdate();
            }

            void DragAndDropWidget::dropEvent(DragAndDropEvent& event)
            {
                if (auto data = std::dynamic_pointer_cast<DragAndDropData>(event.data))
                {
                    event.accept = true;
                    _number = data->getNumber();
                    _textUpdate();
                    _setSizeUpdate();
                    _setDrawUpdate();
                }
            }

            void DragAndDropWidget::_textUpdate()
            {
                std::stringstream ss;
                ss << std::setfill('0') << std::setw(3) << _number;
                _label->setText(ss.str());
            }

            void Window::_init(
                const std::shared_ptr<Context>& context,
                const std::string& name,
                const Size2I& size)
            {
                ui::Window::_init(context, name, size);

                // Create the scroll widget.
                auto scrollWidget = ScrollWidget::create(
                    context,
                    ScrollType::Both,
                    shared_from_this());

                // Create the grid layout.
                auto layout = GridLayout::create(context);
                layout->setMarginRole(SizeRole::MarginSmall);
                layout->setSpacingRole(SizeRole::SpacingSmall);
                scrollWidget->setWidget(layout);

                // Create the drag and drop widgets.
                const size_t count = 20;
                for (size_t i = 0; i < count; ++i)
                {
                    for (size_t j = 0; j < count; ++j)
                    {
                        auto widget = DragAndDropWidget::create(
                            context,
                            i * count + j,
                            layout);
                        layout->setGridPos(widget, i, j);
                    }
                }
            }

            Window::~Window()
            {}

            std::shared_ptr<Window> Window::create(
                const std::shared_ptr<Context>& context,
                const std::string& name,
                const Size2I& size)
            {
                auto out = std::shared_ptr<Window>(new Window);
                out->_init(context, name, size);
                return out;
            }
        }
    }
}

TG_MAIN()
{
    int r = 0;
    try
    {
        auto context = Context::create();
        auto args = tg::app::convert(argc, argv);
        auto app = App::create(context, args, "dnd", "Drag and drop example");
        r = app->getExit();
        if (0 == r)
        {
            auto window = tg::examples::dnd::Window::create(
                context,
                "dnd",
                Size2I(1280, 720));
            app->addWindow(window);
            window->show();
            app->run();
        }
    }
    catch (const std::exception& e)
    {
        std::cout << "ERROR: " << e.what() << std::endl;
    }
    return r;
}

