// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgIO/PNG.h>

using namespace tg::core;

namespace tg
{
    namespace io
    {
        namespace png
        {
            ImagePlugin::ImagePlugin() :
                IImagePlugin("PNG")
            {}

            ImagePlugin::~ImagePlugin()
            {}

            std::shared_ptr<IImageReader> ImagePlugin::read(
                const std::string& fileName,
                const Options& options)
            {
                return std::shared_ptr<ImageReader>(
                    new ImageReader(fileName, nullptr, options));
            }

            std::shared_ptr<IImageReader> ImagePlugin::read(
                const std::string& fileName,
                const InMemoryFile& memory,
                const Options& options)
            {
                return std::shared_ptr<ImageReader>(
                    new ImageReader(fileName, &memory, options));
            }

            std::shared_ptr<IImageWriter> ImagePlugin::write(
                const std::string& fileName,
                const Options& options)
            {
                return std::shared_ptr<ImageWriter>(
                    new ImageWriter(fileName, options));
            }
        }
    }
}

extern "C"
{
    void pngErrorFunc(png_structp in, png_const_charp msg)
    {
        auto error = reinterpret_cast<tg::io::png::ErrorStruct*>(png_get_error_ptr(in));
        error->message = msg;
        longjmp(png_jmpbuf(in), 1);
    }

    void pngWarningFunc(png_structp in, png_const_charp msg)
    {
        auto error = reinterpret_cast<tg::io::png::ErrorStruct*>(png_get_error_ptr(in));
        error->message = msg;
    }
}

