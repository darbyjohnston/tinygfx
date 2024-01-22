// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCoreTest/LRUCacheTest.h>

#include <tgCore/Assert.h>
#include <tgCore/Format.h>
#include <tgCore/LRUCache.h>

using namespace tg::core;

namespace tg
{
    namespace core_test
    {
        LRUCacheTest::LRUCacheTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::core_test::LRUCacheTest")
        {}

        LRUCacheTest::~LRUCacheTest()
        {}

        std::shared_ptr<LRUCacheTest> LRUCacheTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<LRUCacheTest>(new LRUCacheTest(context));
        }
        
        void LRUCacheTest::run()
        {
            LRUCache<int, bool> c;
            c.setMax(3);
            c.setMax(3);
            TG_ASSERT(3 == c.getMax());
            TG_ASSERT(0 == c.getSize());
            TG_ASSERT(0 == c.getCount());
            _print(Format("Percentage: {0}").arg(c.getPercentage()));
            
            c.add(0, true);
            _print(Format("Percentage: {0}").arg(c.getPercentage()));
            c.add(1, true);
            _print(Format("Percentage: {0}").arg(c.getPercentage()));
            c.add(2, true);
            _print(Format("Percentage: {0}").arg(c.getPercentage()));
            c.add(3, true);
            _print(Format("Percentage: {0}").arg(c.getPercentage()));
            TG_ASSERT(3 == c.getSize());

            TG_ASSERT(c.contains(2));
            bool v = false;
            TG_ASSERT(c.get(2, v));
            TG_ASSERT(v);
            TG_ASSERT(!c.get(0, v));
            c.remove(2);
            TG_ASSERT(!c.contains(2));
            c.clear();
            TG_ASSERT(0 == c.getSize());
            
            c.add(0, true);
            c.add(1, true);
            c.add(2, true);
            c.add(3, true);
            TG_ASSERT(1 == c.getKeys()[0]);
            TG_ASSERT(2 == c.getKeys()[1]);
            TG_ASSERT(3 == c.getKeys()[2]);
            TG_ASSERT(c.getValues()[0]);
            TG_ASSERT(c.getValues()[1]);
            TG_ASSERT(c.getValues()[2]);
            
            c.setMax(2);
            TG_ASSERT(2 == c.getSize());
        }
    }
}

