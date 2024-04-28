// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgUI/IWidget.h>

namespace tg
{
    namespace ui
    {
        //! \name Chart Widgets
        ///@{

        //! Pie chart data.
        struct PieChartData
        {
            PieChartData();
            PieChartData(
                const std::string&   text,
                float                percentage,
                const core::Color4F& color);

            std::string   text;
            float         percentage;
            core::Color4F color;

            bool operator == (const PieChartData&) const;
            bool operator != (const PieChartData&) const;
        };

        //! Pie chart widget.
        class PieChart : public IWidget
        {
        protected:
            void _init(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent);

            PieChart();

        public:
            virtual ~PieChart();

            //! Create a new widget.
            static std::shared_ptr<PieChart> create(
                const std::shared_ptr<core::Context>&,
                const std::shared_ptr<IWidget>& parent = nullptr);

            //! Get the pie chart data.
            const std::vector<PieChartData>& getData() const;

            //! Set the pie chart data.
            void setData(const std::vector<PieChartData>&);

            //! Get the font role.
            FontRole getFontRole() const;

            //! Set the font role.
            void setFontRole(FontRole);

            //! Set the size multiplier.
            int getSizeMult() const;

            //! Set the size multiplier.
            void setSizeMult(int);

            void sizeHintEvent(const SizeHintEvent&) override;
            void drawEvent(const core::Box2I&, const DrawEvent&) override;

        private:
            TG_PRIVATE();
        };

        ///@}
    }
}
