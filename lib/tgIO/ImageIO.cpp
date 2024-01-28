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
        Options merge(const Options& a, const Options& b)
        {
            Options out = b;
            for (const auto& i : a)
            {
                out[i.first] = i.second;
            }
            return out;
        }
        
        IImageReader::IImageReader(
            const std::string& fileName,
            const InMemoryFile*,
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

        IImagePlugin::IImagePlugin(const std::string& name) :
            _name(name)
        {}

        IImagePlugin::~IImagePlugin()
        {}
            
        const std::string& IImagePlugin::getName() const
        {
            return _name;
        }
            
        std::shared_ptr<IImageReader> IImagePlugin::read(
            const std::string&,
            const Options&)
        {
            return nullptr;
        }
        
        std::shared_ptr<IImageReader> IImagePlugin::read(
            const std::string&,
            const InMemoryFile&,
            const Options&)
        {
            return nullptr;
        }

        std::shared_ptr<IImageWriter> IImagePlugin::write(
            const std::string&,
            const Options&)
        {
            return nullptr;
        }

        ImageIO::ImageIO(const std::shared_ptr<Context>& context) :
            ISystem(context, "tg::io::ImageIO")
        {
            _plugins.push_back(std::shared_ptr<IImagePlugin>(new png::ImagePlugin));
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
            const InMemoryFile& memory,
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

