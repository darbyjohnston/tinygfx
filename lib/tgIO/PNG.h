// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgIO/ImageIO.h>

#include <png.h>

namespace tg
{
    namespace io
    {
        namespace png
        {
            //! \name PNG
            ///@{

            //! PNG error.
            struct ErrorStruct
            {
                std::string message;
            };

            //! PNG image reader.
            class ImageReader : public IImageReader
            {
            public:
                ImageReader(
                    const std::string& fileName,
                    const core::InMemoryFile*,
                    const Options&);
                
                virtual ~ImageReader();

                const core::ImageInfo& getInfo() const override;
                std::shared_ptr<core::Image> read() override;

            private:
                png_structp        _png = nullptr;
                png_infop          _pngInfo = nullptr;
                png_infop          _pngInfoEnd = nullptr;
                FILE*              _f = nullptr;
                core::InMemoryFile _memory;
                ErrorStruct        _error;
                size_t             _scanlineSize = 0;
                core::ImageInfo    _info;
            };

            //! PNG image writer.
            class ImageWriter : public IImageWriter
            {
            public:
                ImageWriter(
                    const std::string& fileName,
                    const core::ImageInfo&,
                    const Options&);

                virtual ~ImageWriter();

                void write(const std::shared_ptr<core::Image>&) override;

            private:
                png_structp _png = nullptr;
                png_infop   _pngInfo = nullptr;
                FILE*       _f = nullptr;
                ErrorStruct _error;
            };
            
            //! PNG image I/O plugin.
            class ImagePlugin : public IImagePlugin
            {
            public:
                ImagePlugin();

                virtual ~ImagePlugin();

                bool canRead(
                    const std::string& fileName,
                    const Options& = Options());
                std::shared_ptr<IImageReader> read(
                    const std::string& fileName,
                    const Options& = Options()) override;
                std::shared_ptr<IImageReader> read(
                    const std::string& fileName,
                    const core::InMemoryFile&,
                    const Options& = Options()) override;
                bool canWrite(
                    const std::string& fileName,
                    const core::ImageInfo&,
                    const Options& = Options());
                std::shared_ptr<IImageWriter> write(
                    const std::string& fileName,
                    const core::ImageInfo&,
                    const Options& = Options()) override;
            };
            
            ///@}
        }
    }
}

//! \name PNG
///@{

extern "C"
{
    void pngErrorFunc(png_structp, png_const_charp);
    void pngWarningFunc(png_structp, png_const_charp);
}

///@}

