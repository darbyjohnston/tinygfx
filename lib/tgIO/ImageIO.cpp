// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgIO/ImageIO.h>

#include <tgIO/PNG.h>

#include <algorithm>

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
            
        bool IImagePlugin::canRead(
            const std::string&,
            const Options&)
        {
            return false;
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
            
        bool IImagePlugin::canWrite(
            const std::string&,
            const ImageInfo&,
            const Options&)
        {
            return false;
        }

        std::shared_ptr<IImageWriter> IImagePlugin::write(
            const std::string&,
            const ImageInfo&,
            const Options&)
        {
            return nullptr;
        }

        ImageIO::ImageIO(const std::shared_ptr<Context>& context) :
            ISystem(context, "tg::io::ImageIO")
        {
            _plugins.push_front(std::shared_ptr<IImagePlugin>(new png::ImagePlugin));
        }

        ImageIO::~ImageIO()
        {}

        std::shared_ptr<ImageIO> ImageIO::create(const std::shared_ptr<Context>& context)
        {
            return std::shared_ptr<ImageIO>(new ImageIO(context));
        }
        
        const std::list<std::shared_ptr<IImagePlugin> >& ImageIO::getPlugins() const
        {
            return _plugins;
        }

        void ImageIO::addPlugin(const std::shared_ptr<IImagePlugin>& plugin)
        {
            _plugins.push_front(plugin);
        }

        std::shared_ptr<IImageReader> ImageIO::read(
            const std::string& fileName,
            const Options& options)
        {
            std::shared_ptr<IImageReader> out;
            for (const auto& plugin : _plugins)
            {
                if (plugin->canRead(fileName, options))
                {
                    out = plugin->read(fileName, options);
                    break;
                }
            }
            return out;
        }

        std::shared_ptr<IImageReader> ImageIO::read(
            const std::string& fileName,
            const InMemoryFile& memory,
            const Options& options)
        {
            std::shared_ptr<IImageReader> out;
            for (const auto& plugin : _plugins)
            {
                if (plugin->canRead(fileName, options))
                {
                    out = plugin->read(fileName, memory, options);
                    break;
                }
            }
            return out;
        }
        
        std::shared_ptr<IImageWriter> ImageIO::write(
            const std::string& fileName,
            const core::ImageInfo& info,
            const Options& options)
        {
            std::shared_ptr<IImageWriter> out;
            for (const auto& plugin : _plugins)
            {
                if (plugin->canWrite(fileName, info, options))
                {
                    out = plugin->write(fileName, info, options);
                    break;
                }
            }
            return out;
        }
    }
}

