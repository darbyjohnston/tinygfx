// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgUITest/MDIWidgetTest.h>

#include <tgUI/MDICanvas.h>
#include <tgUI/MDIWidget.h>
#include <tgUI/PushButton.h>

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
                _app = App::create(
                    context,
                    argv,
                    "DoubleSliderTest",
                    "Double slider test.");
                _window = Window::create(context, _app, "DoubleSliderTest");
                _app->addWindow(_window);
                _window->show();
                _app->tick();

                auto canvas = MDICanvas::create(context, _window);
                canvas->setCanvasSize(Size2I(100, 100));
                canvas->setCanvasSize(Size2I(100, 100));
                TG_ASSERT(Size2I(100, 100) == canvas->getCanvasSize());
                canvas->setCanvasSize(Size2I(1000, 1000));
                canvas->setGridSize(Size2I(2, 2));
                canvas->setGridSize(Size2I(2, 2));
                TG_ASSERT(Size2I(2, 2) == canvas->getGridSize());
                canvas->setGridSize(Size2I(20, 20));

                auto button = PushButton::create(context, "Button");
                auto widget = canvas->addWidget(
                    "Button",
                    V2I(100, 100),
                    button);
                _app->tick();
                TG_ASSERT("Button" == widget->getTitle());
            }
        }
    }
}

