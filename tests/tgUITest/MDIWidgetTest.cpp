// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/MDIWidgetTest.h>

#include <tgUITest/App.h>
#include <tgUITest/Window.h>

#include <tgUI/Label.h>
#include <tgUI/MDICanvas.h>
#include <tgUI/MDIWidget.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

using namespace tg::core;
using namespace tg::ui;

namespace tg
{
    namespace ui_test
    {
        MDIWidgetTest::MDIWidgetTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::ui_test::MDIWidgetTest")
        {}

        MDIWidgetTest::~MDIWidgetTest()
        {}

        std::shared_ptr<MDIWidgetTest> MDIWidgetTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<MDIWidgetTest>(new MDIWidgetTest(context));
        }
                
        void MDIWidgetTest::run()
        {
            _enums();
            _widget();
        }

        void MDIWidgetTest::_enums()
        {
            TINYGFX_TEST_ENUM(MDIResize);
        }

        void MDIWidgetTest::_widget()
        {
            if (auto context = _context.lock())
            {
                std::vector<std::string> argv;
                argv.push_back("DoubleSliderTest");
                auto app = App::create(
                    context,
                    argv,
                    "DoubleSliderTest",
                    "Double slider test.");
                auto window = Window::create(context, app, "DoubleSliderTest");
                app->addWindow(window);
                window->show();
                app->tick();

                auto canvas = MDICanvas::create(context, window);
                canvas->setCanvasSize(Size2I(100, 100));
                canvas->setCanvasSize(Size2I(100, 100));
                TG_ASSERT(Size2I(100, 100) == canvas->getCanvasSize());
                canvas->setCanvasSize(Size2I(1000, 1000));
                canvas->setGridSize(Size2I(2, 2));
                canvas->setGridSize(Size2I(2, 2));
                TG_ASSERT(Size2I(2, 2) == canvas->getGridSize());
                canvas->setGridSize(Size2I(20, 20));

                auto label = Label::create(context, "Label");
                auto widget = canvas->addWidget("Widget 0", V2I(100, 100), label);
                TG_ASSERT("Widget 0" == widget->getTitle());
                widget->setTitle("Widget");
                TG_ASSERT("Widget" == widget->getTitle());
                app->tick();
                label.reset();
                widget->setParent(nullptr);
                widget.reset();
                label = Label::create(context, "Label 1");
                widget = canvas->addWidget("Widget 1", V2I(100, 100), label);
                label = Label::create(context, "Label 2");
                widget->setWidget(label);
                widget->setWidget(label);
                TG_ASSERT(label == widget->getWidget());
                widget->setPos(V2I(200, 200));
                widget->setSize(Size2I(1000, 1000));
            }
        }
    }
}

