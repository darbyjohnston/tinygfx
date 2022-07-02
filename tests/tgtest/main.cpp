// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include <tgCoreTest/BBoxTest.h>
#include <tgCoreTest/ErrorTest.h>
#include <tgCoreTest/FileTest.h>
#include <tgCoreTest/FileIOTest.h>
#include <tgCoreTest/ListObserverTest.h>
#include <tgCoreTest/MapObserverTest.h>
#include <tgCoreTest/MathTest.h>
#include <tgCoreTest/MatrixTest.h>
#include <tgCoreTest/MemoryTest.h>
#include <tgCoreTest/PathTest.h>
#include <tgCoreTest/RangeTest.h>
#include <tgCoreTest/StringTest.h>
#include <tgCoreTest/StringFormatTest.h>
#include <tgCoreTest/ValueObserverTest.h>
#include <tgCoreTest/VectorTest.h>

#include <iostream>
#include <vector>

using namespace tg;
using namespace tg::tests;

int main(int argc, char* argv[])
{
    std::vector<std::shared_ptr<tests::ITest> > tests;
    if (0)
    {
        tests.push_back(core_tests::MatrixTest::create());
    }
    else
    {
        tests.push_back(core_tests::BBoxTest::create());
        tests.push_back(core_tests::ErrorTest::create());
        tests.push_back(core_tests::FileTest::create());
        tests.push_back(core_tests::FileIOTest::create());
        tests.push_back(core_tests::ListObserverTest::create());
        tests.push_back(core_tests::MapObserverTest::create());
        tests.push_back(core_tests::MathTest::create());
        tests.push_back(core_tests::MatrixTest::create());
        tests.push_back(core_tests::MemoryTest::create());
        tests.push_back(core_tests::PathTest::create());
        tests.push_back(core_tests::RangeTest::create());
        tests.push_back(core_tests::StringTest::create());
        tests.push_back(core_tests::StringFormatTest::create());
        tests.push_back(core_tests::ValueObserverTest::create());
        tests.push_back(core_tests::VectorTest::create());
    }
    for (const auto& i : tests)
    {
        std::cout << "Running test: " << i->getName() << std::endl;
        i->run();
    }

    return 0;
}
