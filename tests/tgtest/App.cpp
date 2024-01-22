// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include "App.h"

#if defined(TINYGFX_API_GL_4_1) || defined(TINYGFX_API_GLES_2)
#include <tgGLTest/MeshTest.h>
#include <tgGLTest/OffscreenBufferTest.h>
#include <tgGLTest/TextureTest.h>
#include <tgGLTest/RenderTest.h>
#include <tgGLTest/ShaderTest.h>
#include <tgGLTest/WindowTest.h>
#endif // TINYGFX_API_GL_4_1

#include <tgCoreTest/BoxTest.h>
#include <tgCoreTest/ColorTest.h>
#include <tgCoreTest/ErrorTest.h>
#include <tgCoreTest/FormatTest.h>
#include <tgCoreTest/ImageTest.h>
#include <tgCoreTest/MathTest.h>
#include <tgCoreTest/MatrixTest.h>
#include <tgCoreTest/MemoryTest.h>
#include <tgCoreTest/MeshTest.h>
#include <tgCoreTest/OSTest.h>
#include <tgCoreTest/ObservableTest.h>
#include <tgCoreTest/RangeTest.h>
#include <tgCoreTest/SizeTest.h>
#include <tgCoreTest/StringTest.h>
#include <tgCoreTest/SystemTest.h>
#include <tgCoreTest/TimeTest.h>
#include <tgCoreTest/TimerTest.h>
#include <tgCoreTest/VectorTest.h>

#if defined(TINYGFX_API_GL_4_1) || defined(TINYGFX_API_GLES_2)
#include <tgGL/Init.h>
#endif // TINYGFX_API_GL_4_1

#include <tgCore/Context.h>
#include <tgCore/Time.h>

#include <iostream>

using namespace tg::core;

namespace tg
{
    namespace tests
    {
        struct App::Private
        {
            std::vector<std::shared_ptr<test::ITest> > tests;
        };
        
        void App::_init(
            const std::shared_ptr<Context>& context,
            const std::string& name,
            std::vector<std::string>& args)
        {
            base_app::IApp::_init(context, name, args);
            TG_P();
#if defined(TINYGFX_API_GL_4_1) || defined(TINYGFX_API_GLES_2)
            gl::init(context);
#endif // TINYGFX_API_GL_4_1

            p.tests.push_back(core_test::BoxTest::create(context));
            p.tests.push_back(core_test::ColorTest::create(context));
            p.tests.push_back(core_test::ErrorTest::create(context));
            p.tests.push_back(core_test::FormatTest::create(context));
            p.tests.push_back(core_test::ImageTest::create(context));
            p.tests.push_back(core_test::MathTest::create(context));
            p.tests.push_back(core_test::MatrixTest::create(context));
            p.tests.push_back(core_test::MemoryTest::create(context));
            p.tests.push_back(core_test::MeshTest::create(context));
            p.tests.push_back(core_test::OSTest::create(context));
            p.tests.push_back(core_test::ObservableTest::create(context));
            p.tests.push_back(core_test::RangeTest::create(context));
            p.tests.push_back(core_test::SizeTest::create(context));
            p.tests.push_back(core_test::StringTest::create(context));
            p.tests.push_back(core_test::SystemTest::create(context));
            p.tests.push_back(core_test::TimeTest::create(context));
            p.tests.push_back(core_test::TimerTest::create(context));
            p.tests.push_back(core_test::VectorTest::create(context));

#if defined(TINYGFX_API_GL_4_1) || defined(TINYGFX_API_GLES_2)
            p.tests.push_back(gl_test::MeshTest::create(context));
            p.tests.push_back(gl_test::OffscreenBufferTest::create(context));
            p.tests.push_back(gl_test::TextureTest::create(context));
            p.tests.push_back(gl_test::RenderTest::create(context));
            p.tests.push_back(gl_test::ShaderTest::create(context));
            p.tests.push_back(gl_test::WindowTest::create(context));
#endif // TINYGFX_API_GL_4_1
        }

        App::App() :
            _p(new Private)
        {}

        App::~App()
        {}
        
        std::shared_ptr<App> App::create(
            const std::shared_ptr<Context>& context,
            const std::string& name,
            std::vector<std::string>& args)
        {
            auto out = std::shared_ptr<App>(new App);
            out->_init(context, name, args);
            return out;
        }
        
        int App::run()
        {
            TG_P();

            // Run the tests.
            for (const auto& test : p.tests)
            {
                _context->tick();
                std::cout << "Running test: " << test->getName() << std::endl;
                test->run();
            }

            // Tick the tests.
            bool tickTests = false;
            do
            {
                auto t0 = std::chrono::steady_clock::now();
                tickTests = false;
                for (const auto& test : p.tests)
                {
                    _context->tick();
                    if (test->doTick())
                    {
                        tickTests = true;
                        test->tick();
                    }
                    auto t1 = std::chrono::steady_clock::now();
                    sleep(std::chrono::milliseconds(5), t0, t1);
                    t0 = t1;
                }
            }
            while (tickTests);
            
            std::cout << "Finished tests" << std::endl;
            return 0;
        }
    }
}

