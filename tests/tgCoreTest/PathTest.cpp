// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include <tgCoreTest/PathTest.h>

#include <tgCore/Assert.h>
#include <tgCore/Path.h>

using namespace tg::file;

namespace tg
{
    namespace core_tests
    {
        PathTest::PathTest() :
            ITest("core_tests::PathTest")
        {}

        std::shared_ptr<PathTest> PathTest::create()
        {
            return std::shared_ptr<PathTest>(new PathTest);
        }

        void PathTest::run()
        {
            {
                Path path;
                TINYGFX_ASSERT(path.isEmpty());
                TINYGFX_ASSERT(path.getDirectory().empty());
                TINYGFX_ASSERT(path.getBaseName().empty());
                TINYGFX_ASSERT(path.getNumber().empty());
                TINYGFX_ASSERT(path.getExtension().empty());
            }
            {
                TINYGFX_ASSERT(Path("/tmp/file.txt").get() == "/tmp/file.txt");
                TINYGFX_ASSERT(Path("/tmp", "file.txt").get() == "/tmp/file.txt");
                TINYGFX_ASSERT(Path("/tmp/", "file.txt").get() == "/tmp/file.txt");
                TINYGFX_ASSERT(Path("\\tmp\\file.txt").get() == "/tmp/file.txt");
            }
            {
                struct Data
                {
                    std::string fileName;
                    std::string directory;
                    std::string baseName;
                    std::string number;
                    int padding = 0;
                    std::string extension;
                };
                const std::vector<Data> data =
                {
                    { "", "", "", "", 0, "" },
                    { "file", "", "file", "", 0, "" },
                    { "file.txt", "", "file", "", 0, ".txt" },
                    { "/tmp/file.txt", "/tmp/", "file", "", 0, ".txt" },
                    { "/tmp/render.1.exr", "/tmp/", "render.", "1", 0, ".exr" },
                    { "/tmp/render.0001.exr", "/tmp/", "render.", "0001", 4, ".exr" },
                    { "/tmp/render0001.exr", "/tmp/", "render", "0001", 4, ".exr" }
                };
                for (const auto& i : data)
                {
                    Path path(i.fileName);
                    TINYGFX_ASSERT(i.fileName == path.get());
                    TINYGFX_ASSERT(i.directory == path.getDirectory());
                    TINYGFX_ASSERT(i.baseName == path.getBaseName());
                    TINYGFX_ASSERT(i.number == path.getNumber());
                    TINYGFX_ASSERT(i.padding == path.getPadding());
                    TINYGFX_ASSERT(i.extension == path.getExtension());
                }
            }
            {
                TINYGFX_ASSERT(Path("/").isAbsolute());
                TINYGFX_ASSERT(Path("/tmp").isAbsolute());
                TINYGFX_ASSERT(Path("\\").isAbsolute());
                TINYGFX_ASSERT(Path("C:").isAbsolute());
                TINYGFX_ASSERT(Path("C:\\tmp").isAbsolute());
                TINYGFX_ASSERT(!Path("").isAbsolute());
                TINYGFX_ASSERT(!Path("../..").isAbsolute());
                TINYGFX_ASSERT(!Path("..\\..").isAbsolute());
            }
        }
    }
}
