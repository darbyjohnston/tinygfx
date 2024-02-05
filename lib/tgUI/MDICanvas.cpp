// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/MDICanvas.h>

#include <tgUI/MDIWidget.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        struct MDICanvas::Private
        {
            Size2I canvasSize = Size2I(1000, 1000);
            Size2I gridSize = Size2I(20, 20);
            std::vector<std::pair<V2I, std::shared_ptr<IWidget> > > newWidgets;

            struct SizeData
            {
                Size2I gridSize;
            };
            SizeData size;

            struct MouseData
            {
                std::shared_ptr<IWidget> widget;
                Box2I geom;
            };
            MouseData mouse;
        };

        void MDICanvas::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "tg::ui::MDICanvas", parent);
            setBackgroundRole(ColorRole::Base);
            _setMouseHover(true);
            _setMousePress(true);
        }

        MDICanvas::MDICanvas() :
            _p(new Private)
        {}

        MDICanvas::~MDICanvas()
        {}

        std::shared_ptr<MDICanvas> MDICanvas::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<MDICanvas>(new MDICanvas);
            out->_init(context, parent);
            return out;
        }

        const Size2I& MDICanvas::getCanvasSize() const
        {
            return _p->canvasSize;
        }

        void MDICanvas::setCanvasSize(const Size2I& value)
        {
            TG_P();
            if (value == p.canvasSize)
                return;
            p.canvasSize = value;
            _updates |= Update::Size;
            _updates |= Update::Draw;
        }

        const Size2I& MDICanvas::getGridSize() const
        {
            return _p->gridSize;
        }

        void MDICanvas::setGridSize(const Size2I& value)
        {
            TG_P();
            if (value == p.gridSize)
                return;
            p.gridSize = value;
            _updates |= Update::Size;
            _updates |= Update::Draw;
        }

        std::shared_ptr<MDIWidget> MDICanvas::addWidget(
            const std::string& title,
            const core::V2I& pos,
            const std::shared_ptr<IWidget>& value)
        {
            TG_P();
            std::shared_ptr<MDIWidget> out;
            if (auto context = _context.lock())
            {
                out = MDIWidget::create(context, title, shared_from_this());
                out->setWidget(value);
                out->setPressCallback(
                    [this, out](bool value)
                    {
                        if (value)
                        {
                            moveToFront(out);
                            _p->mouse.widget = out;
                            _p->mouse.geom = out->getGeometry();
                        }
                        else
                        {
                            _p->mouse.widget.reset();
                            _p->mouse.geom = Box2I();
                        }
                    });
                out->setMoveCallback(
                    [this](const V2I& move)
                    {
                        if (auto widget = _p->mouse.widget)
                        {
                            const Box2I& pg = getGeometry();
                            const Size2I& gridSize = _p->size.gridSize;
                            const Box2I g(
                                clamp(
                                    (_p->mouse.geom.min.x - pg.min.x + move.x) / gridSize.w,
                                    0,
                                    (pg.w() - _p->mouse.geom.w()) / gridSize.w) *
                                gridSize.w + pg.min.x,
                                clamp(
                                    (_p->mouse.geom.min.y - pg.min.y + move.y) / gridSize.h,
                                    0,
                                    (pg.h() - _p->mouse.geom.h()) / gridSize.h) *
                                gridSize.h + pg.min.y,
                                _p->mouse.geom.w(),
                                _p->mouse.geom.h());
                            widget->setGeometry(g);
                        }
                    });
                out->setResizeCallback(
                    [this](MDIResize value, const V2I& move)
                    {
                        if (auto widget = _p->mouse.widget)
                        {
                            const Box2I& pg = getGeometry();
                            const Size2I& gridSize = _p->size.gridSize;
                            const Size2F gridSizeF(gridSize.w, gridSize.h);
                            const Size2I& sizeHint = widget->getSizeHint();
                            Box2I g = _p->mouse.geom;
                            switch (value)
                            {
                            case MDIResize::North:
                                g.min.y = clamp(
                                    (g.min.y - pg.min.y + move.y) / gridSize.h,
                                    0,
                                    (g.max.y - pg.min.y - sizeHint.h) / gridSize.h) *
                                    gridSize.h + pg.min.y;
                                break;
                            case MDIResize::NorthEast:
                                g.min.y = clamp(
                                    (g.min.y - pg.min.y + move.y) / gridSize.h,
                                    0,
                                    (g.max.y - pg.min.y - sizeHint.h) / gridSize.h) *
                                    gridSize.h + pg.min.y;
                                g.max.x = clamp(
                                    (g.max.x - pg.min.x + move.x) / gridSize.w,
                                    (g.min.x - pg.min.x + sizeHint.w) / gridSize.w,
                                    pg.w() / gridSize.w) *
                                    gridSize.w - 1 + pg.min.x;
                                break;
                            case MDIResize::East:
                                g.max.x = clamp(
                                    (g.max.x - pg.min.x + move.x) / gridSize.w,
                                    (g.min.x - pg.min.x + sizeHint.w) / gridSize.w,
                                    pg.w() / gridSize.w) *
                                    gridSize.w - 1 + pg.min.x;
                                break;
                            case MDIResize::SouthEast:
                                g.max.x = clamp(
                                    (g.max.x - pg.min.x + move.x) / gridSize.w,
                                    (g.min.x - pg.min.x + sizeHint.w) / gridSize.w,
                                    pg.w() / gridSize.w) *
                                    gridSize.w - 1 + pg.min.x;
                                g.max.y = clamp(
                                    (g.max.y - pg.min.y + move.y) / gridSize.h,
                                    (g.min.y - pg.min.y + sizeHint.h) / gridSize.h,
                                    pg.h() / gridSize.h) *
                                    gridSize.h - 1 + pg.min.y;
                                break;
                            case MDIResize::South:
                                g.max.y = clamp(
                                    (g.max.y - pg.min.y + move.y) / gridSize.h,
                                    (g.min.y - pg.min.y + sizeHint.h) / gridSize.h,
                                    pg.h() / gridSize.h) *
                                    gridSize.h - 1 + pg.min.y;
                                break;
                            case MDIResize::SouthWest:
                                g.min.x = clamp(
                                    (g.min.x - pg.min.x + move.x) / gridSize.w,
                                    0,
                                    (g.max.x - pg.min.x - sizeHint.w) / gridSize.w) *
                                    gridSize.w + pg.min.x;
                                g.max.y = clamp(
                                    (g.max.y - pg.min.y + move.y) / gridSize.h,
                                    (g.min.y - pg.min.y + sizeHint.h) / gridSize.h,
                                    pg.h() / gridSize.h) *
                                    gridSize.h - 1 + pg.min.y;
                                break;
                            case MDIResize::West:
                                g.min.x = clamp(
                                    (g.min.x - pg.min.x + move.x) / gridSize.w,
                                    0,
                                    (g.max.x - pg.min.x - sizeHint.w) / gridSize.w) *
                                    gridSize.w + pg.min.x;
                                break;
                            case MDIResize::NorthWest:
                                g.min.x = clamp(
                                    (g.min.x - pg.min.x + move.x) / gridSize.w,
                                    0,
                                    (g.max.x - pg.min.x - sizeHint.w) / gridSize.w) *
                                    gridSize.w + pg.min.x;
                                g.min.y = clamp(
                                    (g.min.y - pg.min.y + move.y) / gridSize.h,
                                    0,
                                    (g.max.y - pg.min.y - sizeHint.h) / gridSize.h) *
                                    gridSize.h + pg.min.y;
                                break;
                            default: break;
                            }
                            if (g.w() < sizeHint.w)
                            {
                                g.max.x += gridSize.w;
                            }
                            if (g.h() < sizeHint.h)
                            {
                                g.max.y += gridSize.h;
                            }
                            widget->setGeometry(g);
                        }
                    });
                p.newWidgets.push_back(std::make_pair(pos, out));
                _updates |= Update::Size;
                _updates |= Update::Draw;
            }
            return out;
        }

        void MDICanvas::setGeometry(const Box2I& value)
        {
            V2I offset = value.min - _geometry.min;
            IWidget::setGeometry(value);
            TG_P();

            const Box2I& pg = getGeometry();
            const Size2I& gridSize = p.size.gridSize;
            for (auto i : p.newWidgets)
            {
                const Size2I& gridSize = _p->size.gridSize;
                const Size2I& sizeHint = i.second->getSizeHint();
                Box2I g(
                    i.first.x / gridSize.w * gridSize.w,
                    i.first.y / gridSize.h * gridSize.h,
                    sizeHint.w / gridSize.w * gridSize.w,
                    sizeHint.h / gridSize.h * gridSize.h);
                if (g.w() < sizeHint.w)
                {
                    g.max.x += gridSize.w;
                }
                if (g.h() < sizeHint.h)
                {
                    g.max.y += gridSize.h;
                }
                i.second->setGeometry(g);
            }
            p.newWidgets.clear();
            
            for (const auto& child : _children)
            {
                Box2I g = child->getGeometry();
             
                // Add the parent offset.
                g.min = g.min + offset;
                g.max = g.max + offset;

                // Clamp to the parent geometry.
                if (g.min.x < pg.min.x ||
                    g.min.y < pg.min.y ||
                    g.max.x > pg.max.x ||
                    g.max.y > pg.max.y)
                {
                    const Size2I& gridSize = _p->size.gridSize;
                    const Size2F gridSizeF(gridSize.w, gridSize.h);
                    const Size2I& sizeHint = child->getSizeHint();
                    const Size2I sizeHintGrid(
                        ceilf(sizeHint.w / gridSizeF.w),
                        ceilf(sizeHint.h / gridSizeF.h));
                    g.min.x = clamp(
                        (g.min.x - pg.min.x) / gridSize.w,
                        0,
                        pg.w() / gridSize.w - sizeHintGrid.w) *
                        gridSize.w + pg.min.x;
                    g.min.y = clamp(
                        (g.min.y - pg.min.y) / gridSize.h,
                        0,
                        pg.h() / gridSize.h - sizeHintGrid.h) *
                        gridSize.h + pg.min.y;
                    g.max.x = clamp(
                        (g.max.x - pg.min.x) / gridSize.w,
                        sizeHintGrid.w,
                        pg.w() / gridSize.w) *
                        gridSize.w - 1 + pg.min.x;
                    g.max.y = clamp(
                        (g.max.y - pg.min.y) / gridSize.h,
                        sizeHintGrid.h,
                        pg.h() / gridSize.h) *
                        gridSize.h - 1 + pg.min.y;
                    if (g.w() < sizeHint.w)
                    {
                        g.max.x += gridSize.w;
                    }
                    if (g.h() < sizeHint.h)
                    {
                        g.max.y += gridSize.h;
                    }
                }

                child->setGeometry(g);
            }
        }

        void MDICanvas::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            TG_P();
            p.size.gridSize = p.gridSize * static_cast<int>(event.displayScale);
            _sizeHint = p.canvasSize * static_cast<int>(event.displayScale);
        }

        void MDICanvas::drawEvent(const Box2I& drawRect, const DrawEvent& event)
        {
            IWidget::drawEvent(drawRect, event);
            TG_P();
            const Box2I& g = _geometry;

            const Size2I& gridSize = p.size.gridSize;
            V2I offset;
            offset.x = g.min.x % gridSize.w;
            offset.y = g.min.y % gridSize.h;

            Box2I grid = intersect(g, drawRect);
            grid.min.x = (grid.min.x / gridSize.w - 2) * gridSize.w + offset.x;
            grid.min.y = (grid.min.y / gridSize.h - 2) * gridSize.h + offset.y;
            grid.max.x = (grid.max.x / gridSize.w + 2) * gridSize.w + offset.x;
            grid.max.y = (grid.max.y / gridSize.h + 2) * gridSize.h + offset.y;

            LineOptions options;
            options.width = 1 * event.displayScale;
            for (int x = grid.min.x; x < grid.max.x; x += gridSize.w)
            {
                event.render->drawLine(
                    V2F(x, grid.min.y),
                    V2F(x, grid.max.y),
                    event.style->getColorRole(ColorRole::Border),
                    options);
            }
            for (int y = grid.min.y; y < grid.max.y; y += gridSize.h)
            {
                event.render->drawLine(
                    V2F(grid.min.x, y),
                    V2F(grid.max.x, y),
                    event.style->getColorRole(ColorRole::Border),
                    options);
            }
        }

        void MDICanvas::mouseMoveEvent(MouseMoveEvent& event)
        {
            IWidget::mouseMoveEvent(event);
        }

        void MDICanvas::mousePressEvent(MouseClickEvent& event)
        {
            IWidget::mousePressEvent(event);
        }

        void MDICanvas::mouseReleaseEvent(MouseClickEvent& event)
        {
            IWidget::mouseReleaseEvent(event);
        }
    }
}
