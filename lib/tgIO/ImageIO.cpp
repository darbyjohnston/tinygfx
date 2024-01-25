// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgIO/ImageIO.h>

#include <tgIO/PNG.h>

using namespace tg::core;

namespace tg
{
    namespace io
    {
        IImageReader::IImageReader(
            const std::string& fileName,
            const core::FileMemoryRead*,
            const Options&) :
            _fileName(fileName)
        {}
        
        IImageReader::~IImageReader()
        {}

        IImageWriter::IImageWriter(
            const std::string& fileName,
            const Options&) :
            _fileName(fileName)
        {}

        IImageWriter::~IImageWriter()
        {}
        
        ImageIO::ImageIO(const std::shared_ptr<Context>& context) :
            ISystem(context, "tg::io::ImageIO")
        {
            _plugins.push_back(std::shared_ptr<IImageIOPlugin>(new png::ImageIOPlugin));
        }

        ImageIO::~ImageIO()
        {}

        std::shared_ptr<ImageIO> ImageIO::create(const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<ImageIO>(new ImageIO(context));
        }

        std::shared_ptr<IImageReader> ImageIO::read(
            const std::string& fileName,
            const Options& options)
        {
            return _plugins.front()->read(fileName, options);
        }

        std::shared_ptr<IImageReader> ImageIO::read(
            const std::string& fileName,
            const FileMemoryRead& memory,
            const Options& options)
        {
            return _plugins.front()->read(fileName, memory, options);
        }
        
        std::shared_ptr<IImageWriter> ImageIO::write(
            const std::string& fileName,
            const Options& options)
        {
            return _plugins.front()->write(fileName, options);
        }
    }
}

