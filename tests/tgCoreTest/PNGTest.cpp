// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCoreTest/PNGTest.h>

#include <tgCore/Assert.h>
#include <tgCore/Context.h>
#include <tgCore/FileIO.h>
#include <tgCore/Format.h>
#include <tgCore/ImageIO.h>

using namespace tg::core;

namespace tg
{
    namespace core_test
    {
        PNGTest::PNGTest(const std::shared_ptr<Context>& context) :
            ITest(context, "tg::core_test::PNGTest")
        {}

        PNGTest::~PNGTest()
        {}

        std::shared_ptr<PNGTest> PNGTest::create(
            const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<PNGTest>(new PNGTest(context));
        }
        
        void PNGTest::run()
        {
            if (auto context = _context.lock())
            {
                auto io = context->getSystem<ImageIO>();
                const std::vector<Size2I> sizes =
                {
                    Size2I(512, 512),
                    Size2I(1, 1),
                    Size2I(0, 0)
                };
                const std::vector<PixelType> pixelTypes =
                {
                    PixelType::L_U8,
                    PixelType::L_U16,
                    PixelType::LA_U8,
                    PixelType::LA_U16,
                    PixelType::RGB_U8,
                    PixelType::RGB_U16,
                    PixelType::RGBA_U8,
                    PixelType::RGBA_U16,
                    PixelType::None
                };
                for (auto size : sizes)
                {
                    for (auto pixelType : pixelTypes)
                    {
                        try
                        {
                            const ImageInfo info(size, pixelType);
                            auto image = Image::create(info);
                            image->zero();
                            const std::string fileName = Format(
                                "PNGTest_{0}_{1}_{2}.png").
                                arg(size.w).
                                arg(size.h).
                                arg(pixelType);

                            auto write = io->write(fileName, info);
                            if (write)
                            {
                                write->write(image);
                                write.reset();
                            }

                            auto read = io->read(fileName);
                            auto info2 = read->getInfo();
                            TG_ASSERT(info.size == info2.size);
                            TG_ASSERT(info.pixelType == info2.pixelType);
                            auto image2 = read->read();
                            TG_ASSERT(image2);
                            read.reset();
                            
                            auto fileIO = FileIO::create(fileName, FileMode::Read);
                            const size_t size = fileIO->getSize();
                            InMemoryFile memory(fileIO->getMemoryStart(), size);
                            read = io->read(fileName, memory);
                            info2 = read->getInfo();
                            TG_ASSERT(info.size == info2.size);
                            TG_ASSERT(info.pixelType == info2.pixelType);
                            image2 = read->read();
                            TG_ASSERT(image2);
                            read.reset();
                            
                            truncateFile(fileName, 0);
                            read = io->read(fileName);
                            image2 = read->read();
                            TG_ASSERT(false);
                        }
                        catch (const std::exception& e)
                        {
                            _error(e.what());
                        }
                    }
                }
            }
        }
    }
}

