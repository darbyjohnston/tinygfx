// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUI/PieChart.h>

#include <tgUI/DrawUtil.h>
#include <tgUI/LayoutUtil.h>

#include <tgCore/Format.h>

using namespace tg::core;

namespace tg
{
    namespace ui
    {
        PieChartData::PieChartData()
        {}

        PieChartData::PieChartData(
            const std::string& text,
            float percentage,
            const Color4F& color) :
            text(text),
            percentage(percentage),
            color(color)
        {}

        bool PieChartData::operator == (const PieChartData& other) const
        {
            return
                text == other.text &&
                percentage == other.percentage &&
                color == other.color;
        }

        bool PieChartData::operator != (const PieChartData& other) const
        {
            return !(*this == other);
        }

        struct PieChart::Private
        {
            std::vector<PieChartData> data;
            FontRole fontRole = FontRole::Label;
            int sizeMult = 5;

            struct SizeData
            {
                bool init = true;
                float displayScale = 0.F;
                int margin = 0;
                int spacing = 0;
                FontInfo fontInfo;
                FontMetrics fontMetrics;

                int pieDiameter = 0;
                Size2I textSize;
            };
            SizeData size;

            struct DrawData
            {
                struct PercentageLabel
                {
                    std::string text;
                    Size2I size;
                    V2I pos;
                    std::vector<std::shared_ptr<Glyph> > glyphs;
                };
                std::vector<PercentageLabel> percentageLabels;
                std::vector<TriMesh2F> pieSliceMeshes;
                struct TextLabel
                {
                    std::string text;
                    Size2I size;
                    V2I pos;
                    std::vector<std::shared_ptr<Glyph> > glyphs;
                    Color4F color;
                    TriMesh2F circleMesh;
                };
                std::vector<TextLabel> textLabels;
            };
            DrawData draw;
        };

        void PieChart::_init(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            IWidget::_init(context, "tg::ui::PieChart", parent);
        }

        PieChart::PieChart() :
            _p(new Private)
        {}

        PieChart::~PieChart()
        {}

        std::shared_ptr<PieChart> PieChart::create(
            const std::shared_ptr<Context>& context,
            const std::shared_ptr<IWidget>& parent)
        {
            auto out = std::shared_ptr<PieChart>(new PieChart);
            out->_init(context, parent);
            return out;
        }

        void PieChart::setData(const std::vector<PieChartData>& value)
        {
            TG_P();
            if (value == p.data)
                return;
            p.data = value;
            _setSizeUpdate();
            _setDrawUpdate();
        }

        void PieChart::setFontRole(FontRole value)
        {
            TG_P();
            if (value == p.fontRole)
                return;
            p.fontRole = value;
            p.size.init = true;
            _setSizeUpdate();
            _setDrawUpdate();
        }

        void PieChart::setSizeMult(int value)
        {
            TG_P();
            if (value == p.sizeMult)
                return;
            p.sizeMult = value;
            _setSizeUpdate();
            _setDrawUpdate();
        }

        void PieChart::sizeHintEvent(const SizeHintEvent& event)
        {
            IWidget::sizeHintEvent(event);
            TG_P();

            const bool displayScaleChanged = event.displayScale != p.size.displayScale;
            if (displayScaleChanged || p.size.init)
            {
                p.size.init = false;
                p.size.displayScale = event.displayScale;
                p.size.margin = event.style->getSizeRole(SizeRole::MarginSmall, p.size.displayScale);
                p.size.spacing = event.style->getSizeRole(SizeRole::SpacingSmall, p.size.displayScale);
                p.size.fontInfo = event.style->getFontRole(p.fontRole, p.size.displayScale);
                p.size.fontMetrics = event.fontSystem->getMetrics(p.size.fontInfo);
            }

            // Create the percentage labels.
            p.draw.percentageLabels.clear();
            int percentageWidthMax = 0;
            for (const auto& data : p.data)
            {
                Private::DrawData::PercentageLabel label;
                label.text = Format("{0}%").arg(data.percentage, 0);
                label.size = event.fontSystem->getSize(label.text, p.size.fontInfo);
                label.glyphs = event.fontSystem->getGlyphs(label.text, p.size.fontInfo);
                p.draw.percentageLabels.push_back(label);
                percentageWidthMax = std::max(percentageWidthMax, label.size.w);
            }
            float a = 0.F;
            for (size_t i = 0; i < p.data.size(); ++i)
            {
                auto& label = p.draw.percentageLabels[i];
                const float d = a + p.data[i].percentage / 2.F;
                const float r = p.size.fontMetrics.lineHeight * p.sizeMult / 2.F +
                    p.size.spacing +
                    label.size.w / 2.F;
                label.pos.x = cos(deg2rad(d / 100.F * 360.F - 90.F)) * r -
                    label.size.w / 2;
                label.pos.y = sin(deg2rad(d / 100.F * 360.F - 90.F)) * r -
                    label.size.h / 2;
                a += p.data[i].percentage;
            }

            // Create the pie slices.
            p.draw.pieSliceMeshes.clear();
            p.draw.pieSliceMeshes.resize(p.data.size());
            const float r = p.size.fontMetrics.lineHeight * p.sizeMult / 2.F;
            a = 0.F;
            for (size_t i = 0; i < p.data.size(); ++i)
            {
                TriMesh2F& mesh = p.draw.pieSliceMeshes[i];
                const float d = p.data[i].percentage;
                const float inc = 2.F;
                for (int i = a; i < a + d; i += inc)
                {
                    const size_t size = mesh.v.size();
                    mesh.v.push_back(V2F(0.F, 0.F));
                    mesh.v.push_back(V2F(
                        cos(deg2rad(i / 100.F * 360.F - 90.F)) * r,
                        sin(deg2rad(i / 100.F * 360.F - 90.F)) * r));
                    mesh.v.push_back(V2F(
                        cos(deg2rad(std::min(i + inc, a + d) / 100.F * 360.F - 90.F)) * r,
                        sin(deg2rad(std::min(i + inc, a + d) / 100.F * 360.F - 90.F)) * r));
                    mesh.triangles.push_back({ size + 1, size + 2, size + 3 });
                }
                a += p.data[i].percentage;
            }

            // Create the text labels.
            p.size.textSize = Size2I();
            p.draw.textLabels.clear();
            const float r2 = p.size.fontMetrics.lineHeight;
            for (size_t i = 0; i < p.data.size(); ++i)
            {
                Private::DrawData::TextLabel label;
                label.text = p.data[i].text;
                label.size = event.fontSystem->getSize(label.text, p.size.fontInfo);
                label.pos.y = p.size.textSize.h;
                label.glyphs = event.fontSystem->getGlyphs(label.text, p.size.fontInfo);
                label.color = p.data[i].color;
                label.circleMesh = circle(V2I(r2 / 2.F, r2 / 2.F), r2 / 2.F, 60);
                p.draw.textLabels.push_back(label);
                p.size.textSize.w = std::max(
                    p.size.textSize.w,
                    static_cast<int>(r2) + p.size.spacing + label.size.w);
                p.size.textSize.h += p.size.fontMetrics.lineHeight;
                if (i < p.data.size() - 1)
                {
                    p.size.textSize.h += p.size.spacing;
                }
            }

            // Set the size hint.
            p.size.pieDiameter =
                p.size.fontMetrics.lineHeight * p.sizeMult +
                p.size.spacing * 2 +
                percentageWidthMax * 2;
            _setSizeHint(Size2I(
                p.size.pieDiameter +
                p.size.spacing +
                p.size.textSize.w +
                p.size.margin * 2,
                std::max(p.size.pieDiameter, p.size.textSize.h) +
                p.size.margin * 2));
        }

        void PieChart::drawEvent(
            const Box2I& drawRect,
            const DrawEvent& event)
        {
            IWidget::drawEvent(drawRect, event);
            TG_P();

            //event.render->drawRect(_geometry, Color4F(.5F, .3F, .3F));

            const Box2I g = align(
                margin(getGeometry() , -p.size.margin),
                getSizeHint(),
                Stretch::Fixed,
                Stretch::Fixed,
                getHAlign(),
                getVAlign());

            // Draw the percentage labels.
            const Box2I g2(
                g.min.x,
                g.min.y,
                p.size.pieDiameter,
                p.size.pieDiameter);
            const V2I c = center(g2);
            for (const auto& label : p.draw.percentageLabels)
            {
                event.render->drawText(
                    label.glyphs,
                    V2F(
                        c.x + label.pos.x,
                        c.y + label.pos.y + p.size.fontMetrics.ascender),
                    event.style->getColorRole(ColorRole::Text));
            }

            // Draw the pie slices.
            for (size_t i = 0; i < p.data.size(); ++i)
            {
                event.render->drawMesh(
                    p.draw.pieSliceMeshes[i],
                    p.data[i].color,
                    V2F(c.x, c.y));
            }

            // Draw the text labels.
            V2I pos(
                g.min.x + p.size.pieDiameter + p.size.spacing,
                g.min.y + g.h() / 2 - p.size.textSize.h / 2);
            for (const auto& label : p.draw.textLabels)
            {
                event.render->drawMesh(
                    label.circleMesh,
                    label.color,
                    V2F(
                        pos.x + label.pos.x,
                        pos.y + label.pos.y));
                event.render->drawText(
                    label.glyphs,
                    V2F(
                        pos.x +
                        label.pos.x +
                        p.size.fontMetrics.lineHeight +
                        p.size.spacing,
                        pos.y +
                        label.pos.y +
                        p.size.fontMetrics.ascender),
                    event.style->getColorRole(ColorRole::Text));
            }
        }
    }
}
