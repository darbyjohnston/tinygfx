// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCoreTest/BoxPackTest.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>

#include <sstream>

using namespace tg::core;

namespace tg
{
    namespace core_test
    {
        BoxPackTest::BoxPackTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::core_test::BoxPackTest")
        {}

        BoxPackTest::~BoxPackTest()
        {}

        std::shared_ptr<BoxPackTest> BoxPackTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<BoxPackTest>(new BoxPackTest(context));
        }
        
        void BoxPackTest::run()
        {
            {
                auto pack = BoxPack::create(Size2I(100, 100));
                auto node = pack->insert(Size2I(100, 100));
                TG_ASSERT(node);
                node = pack->insert(Size2I(100, 100));
                TG_ASSERT(node);
                _printPack(pack);
            }
            {
                auto pack = BoxPack::create(Size2I(100, 100));
                auto node = pack->insert(Size2I(50, 100));
                TG_ASSERT(node);
                node = pack->insert(Size2I(50, 100));
                TG_ASSERT(node);
                _printPack(pack);
            }
            {
                auto pack = BoxPack::create(Size2I(100, 100));
                for (size_t i = 0; i < 5; ++i)
                {
                    auto node = pack->insert(Size2I(50, 50));
                    TG_ASSERT(node);
                }
                _printPack(pack);
            }
            {
                auto pack = BoxPack::create(Size2I(104, 104), 1);
                for (size_t i = 0; i < 5; ++i)
                {
                    auto node = pack->insert(Size2I(50, 50));
                    TG_ASSERT(node);
                }
                _printPack(pack);
            }
        }

        void BoxPackTest::_printPack(const std::shared_ptr<BoxPack>& pack)
        {
            _printNode(pack->getRoot());
        }
        
        void BoxPackTest::_printNode(
            const std::shared_ptr<core::BoxPackNode>& node,
            int indent,
            char pad)
        {
            _print(Format("{0}: {1},{2}-{3}x{4} [{5}]").
                arg(int(node->id), indent, pad).
                arg(node->box.x()).
                arg(node->box.y()).
                arg(node->box.w()).
                arg(node->box.h()).
                arg(node->timestamp));
            if (node->children[0].get())
            {
                _printNode(node->children[0], indent + 4, '.');
            }
            if (node->children[1].get())
            {
                _printNode(node->children[1], indent + 4, '.');
            }
        }
    }
}

