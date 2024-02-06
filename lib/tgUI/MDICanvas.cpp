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
            Size2I canvasSize = Size2I(500, 500);
            Size2I gridSize = Size2I(20, 20);
            std::vector<std::pair<V2I, std::shared_ptr<MDIWidget> > > newWidgets;
            std::map<std::shared_ptr<MDIWidget>, Size2I> sizeHints;

            struct SizeData
            {
                Size2I gridSize;
            };
            SizeData size;

            struct MouseData
            {
                std::shared_ptr<MDIWidget> widget;
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
                            Box2I g = widget->removeMargins(_p->mouse.geom);
                            g = Box2I(
                                clamp(
                                    _snapToGridX(g.min.x - pg.min.x + move.x),
                                    0,
                                    _snapToGridX(pg.max.x + 1 - pg.min.x - g.w())) + pg.min.x,
                                clamp(
                                    _snapToGridY(g.min.y - pg.min.y + move.y),
                                    0,
                                    _snapToGridY(pg.max.y + 1 - pg.min.y - g.h())) + pg.min.y,
                                g.w(),
                                g.h());
                            widget->setGeometry(widget->addMargins(g));
                        }
                    });
                out->setResizeCallback(
                    [this](MDIResize value, const V2I& move)
                    {
                        if (auto widget = _p->mouse.widget)
                        {
                            const Box2I& pg = getGeometry();
                            const Size2I sizeHintGrid = _snapToGrid(widget->removeMargins(widget->getSizeHint()));
                            Box2I g = widget->removeMargins(_p->mouse.geom);
                            switch (value)
                            {
                            case MDIResize::North:
                                g.min.y = clamp(
                                    _snapToGridY(g.min.y - pg.min.y + move.y),
                                    0,
                                    _snapToGridY(g.max.y + 1 - pg.min.y) - sizeHintGrid.h) + pg.min.y;
                                break;
                            case MDIResize::NorthEast:
                                g.min.y = clamp(
                                    _snapToGridY(g.min.y - pg.min.y + move.y),
                                    0,
                                    _snapToGridY(g.max.y + 1 - pg.min.y) - sizeHintGrid.h) + pg.min.y;
                                g.max.x = clamp(
                                    _snapToGridX(g.max.x + 1 - pg.min.x + move.x),
                                    _snapToGridX(g.min.x - pg.min.x) + sizeHintGrid.w,
                                    _snapToGridX(pg.max.x + 1 - pg.min.x)) - 1 + pg.min.x;
                                break;
                            case MDIResize::East:
                                g.max.x = clamp(
                                    _snapToGridX(g.max.x + 1 - pg.min.x + move.x),
                                    _snapToGridX(g.min.x - pg.min.x) + sizeHintGrid.w,
                                    _snapToGridX(pg.max.x + 1 - pg.min.x)) - 1 + pg.min.x;
                                break;
                            case MDIResize::SouthEast:
                                g.max.x = clamp(
                                    _snapToGridX(g.max.x + 1 - pg.min.x + move.x),
                                    _snapToGridX(g.min.x - pg.min.x) + sizeHintGrid.w,
                                    _snapToGridX(pg.max.x + 1 - pg.min.x)) - 1 + pg.min.x;
                                g.max.y = clamp(
                                    _snapToGridY(g.max.y + 1 - pg.min.y + move.y),
                                    _snapToGridY(g.min.y - pg.min.y) + sizeHintGrid.h,
                                    _snapToGridY(pg.max.y + 1 - pg.min.y)) - 1 + pg.min.y;
                                break;
                            case MDIResize::South:
                                g.max.y = clamp(
                                    _snapToGridY(g.max.y + 1 - pg.min.y + move.y),
                                    _snapToGridY(g.min.y - pg.min.y) + sizeHintGrid.h,
                                    _snapToGridY(pg.max.y + 1 - pg.min.y)) - 1 + pg.min.y;
                                break;
                            case MDIResize::SouthWest:
                                g.min.x = clamp(
                                    _snapToGridX(g.min.x - pg.min.x + move.x),
                                    0,
                                    _snapToGridX(g.max.x + 1 - pg.min.x) - sizeHintGrid.w) + pg.min.x;
                                g.max.y = clamp(
                                    _snapToGridY(g.max.y + 1 - pg.min.y + move.y),
                                    _snapToGridY(g.min.y - pg.min.y) + sizeHintGrid.h,
                                    _snapToGridY(pg.max.y + 1 - pg.min.y)) - 1 + pg.min.y;
                                break;
                            case MDIResize::West:
                                g.min.x = clamp(
                                    _snapToGridX(g.min.x - pg.min.x + move.x),
                                    0,
                                    _snapToGridX(g.max.x + 1 - pg.min.x) - sizeHintGrid.w) + pg.min.x;
                                break;
                            case MDIResize::NorthWest:
                                g.min.x = clamp(
                                    _snapToGridX(g.min.x - pg.min.x + move.x),
                                    0,
                                    _snapToGridX(g.max.x + 1 - pg.min.x) - sizeHintGrid.w) + pg.min.x;
                                g.min.y = clamp(
                                    _snapToGridY(g.min.y - pg.min.y + move.y),
                                    0,
                                    _snapToGridY(g.max.y + 1 - pg.min.y) - sizeHintGrid.h) + pg.min.y;
                                break;
                            default: break;
                            }
                            widget->setGeometry(widget->addMargins(g));
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

            // Place new child widgets on the canvas.
            const Box2I& pg = getGeometry();
            const Size2I& gridSize = p.size.gridSize;
            for (auto i : p.newWidgets)
            {
                const Size2I& sizeHint = i.second->getSizeHint();
                p.sizeHints[i.second] = sizeHint;
                Box2I g = i.second->removeMargins(Box2I(i.first, sizeHint));
                const Size2I sizeHintGrid = _snapToGrid(i.second->removeMargins(sizeHint));
                g = Box2I(
                    _snapToGridX(g.min.x),
                    _snapToGridY(g.min.y),
                    sizeHintGrid.w,
                    sizeHintGrid.h);
                i.second->setGeometry(i.second->addMargins(g));
            }
            p.newWidgets.clear();
            
            // Update the child widget geometry.
            for (const auto& child : _children)
            {
                if (auto mdi = std::dynamic_pointer_cast<MDIWidget>(child))
                {
                    Box2I g = mdi->removeMargins(mdi->getGeometry());

                    // Add the parent offset.
                    g.min = g.min + offset;
                    g.max = g.max + offset;

                    // Update the size hint.
                    const Size2I& sizeHint = mdi->getSizeHint();
                    const auto i = p.sizeHints.find(mdi);
                    if (i != p.sizeHints.end() && i->second != sizeHint)
                    {
                        p.sizeHints[mdi] = sizeHint;
                        const Size2I sizeHintGrid = _snapToGrid(mdi->removeMargins(sizeHint));
                        g = Box2I(
                            g.min.x,
                            g.min.y,
                            std::max(g.w(), sizeHintGrid.w),
                            std::max(g.h(), sizeHintGrid.h));
                    }

                    // Clamp to the parent geometry.
                    if (g.min.x < pg.min.x ||
                        g.min.y < pg.min.y ||
                        g.max.x > pg.max.x ||
                        g.max.y > pg.max.y)
                    {
                        const Size2I sizeHintGrid = _snapToGrid(mdi->removeMargins(sizeHint));
                        g.min.x = clamp(
                            _snapToGridX(g.min.x - pg.min.x),
                            0,
                            _snapToGridX(pg.max.x + 1 - pg.min.x) - sizeHintGrid.w) + pg.min.x;
                        g.min.y = clamp(
                            _snapToGridY(g.min.y - pg.min.y),
                            0,
                            _snapToGridY(pg.max.y + 1 - pg.min.y) - sizeHintGrid.h) + pg.min.y;
                        g.max.x = clamp(
                            _snapToGridX(g.max.x + 1 - pg.min.x),
                            _snapToGridX(g.min.x - pg.min.x) + sizeHintGrid.w,
                            _snapToGridX(pg.max.x + 1 - pg.min.x)) - 1 + pg.min.x;
                        g.max.y = clamp(
                            _snapToGridX(g.max.y + 1 - pg.min.y),
                            _snapToGridX(g.min.y - pg.min.y) + sizeHintGrid.h,
                            _snapToGridX(pg.max.y + 1 - pg.min.y)) - 1 + pg.min.y;
                    }

                    mdi->setGeometry(mdi->addMargins(g));
                }
            }
        }

        void MDICanvas::childRemovedEvent(const ChildEvent& event)
        {
            IWidget::childRemovedEvent(event);
            TG_P();
            const auto i = p.sizeHints.find(std::dynamic_pointer_cast<MDIWidget>(event.child));
            if (i != p.sizeHints.end())
            {
                p.sizeHints.erase(i);
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

            // Draw the grid.
            const Size2I& gridSize = p.size.gridSize;
            V2I offset;
            offset.x = g.min.x % gridSize.w;
            offset.y = g.min.y % gridSize.h;
            Box2I gridRect = intersect(g, drawRect);
            gridRect.min.x = (gridRect.min.x / gridSize.w - 2) * gridSize.w + offset.x;
            gridRect.min.y = (gridRect.min.y / gridSize.h - 2) * gridSize.h + offset.y;
            gridRect.max.x = (gridRect.max.x / gridSize.w + 2) * gridSize.w + offset.x;
            gridRect.max.y = (gridRect.max.y / gridSize.h + 2) * gridSize.h + offset.y;
            LineOptions options;
            options.width = 1 * event.displayScale;
            std::vector<std::pair<V2F, V2F> > lines;
            for (int x = gridRect.min.x; x < gridRect.max.x; x += gridSize.w)
            {
                lines.push_back({ V2F(x, gridRect.min.y), V2F(x, gridRect.max.y) });
            }
            for (int y = gridRect.min.y; y < gridRect.max.y; y += gridSize.h)
            {
                lines.push_back({ V2F(gridRect.min.x, y), V2F(gridRect.max.x, y) });
            }
            event.render->drawLines(
                lines,
                event.style->getColorRole(ColorRole::Border),
                options);
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

        int MDICanvas::_snapToGridX(int value) const
        {
            TG_P();
            return value / p.size.gridSize.w * p.size.gridSize.w;
        }

        int MDICanvas::_snapToGridY(int value) const
        {
            TG_P();
            return value / p.size.gridSize.h * p.size.gridSize.h;
        }

        Size2I MDICanvas::_snapToGrid(const Size2I& value) const
        {
            TG_P();
            return Size2I(
                ceilf(value.w / static_cast<float>(p.size.gridSize.w)) * p.size.gridSize.w,
                ceilf(value.h / static_cast<float>(p.size.gridSize.h)) * p.size.gridSize.h);
        }
    }
}
