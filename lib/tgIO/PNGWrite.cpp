// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgIO/PNG.h>

#include <tgCore/Error.h>
#include <tgCore/Format.h>
#include <tgCore/Memory.h>
#include <tgCore/String.h>

using namespace tg::core;

namespace tg
{
    namespace io
    {
        namespace png
        {
            namespace
            {
                bool open(
                    FILE* f,
                    png_structp png,
                    png_infop* pngInfo,
                    const ImageInfo& info)
                {
                    if (setjmp(png_jmpbuf(png)))
                    {
                        return false;
                    }
                    *pngInfo = png_create_info_struct(png);
                    if (!*pngInfo)
                    {
                        return false;
                    }
                    png_init_io(png, f);

                    int colorType = 0;
                    switch (info.pixelType)
                    {
                    case PixelType::L_U8:
                    case PixelType::L_U16:
                        colorType = PNG_COLOR_TYPE_GRAY;
                        break;
                    case PixelType::LA_U8:
                    case PixelType::LA_U16:
                        colorType = PNG_COLOR_TYPE_GRAY_ALPHA;
                        break;
                    case PixelType::RGB_U8:
                    case PixelType::RGB_U16:
                        colorType = PNG_COLOR_TYPE_RGB;
                        break;
                    case PixelType::RGBA_U8:
                    case PixelType::RGBA_U16:
                        colorType = PNG_COLOR_TYPE_RGB_ALPHA;
                        break;
                    default: return false;
                    }

                    const int bitDepth = getBitDepth(info.pixelType);
                    png_set_IHDR(
                        png,
                        *pngInfo,
                        info.size.w,
                        info.size.h,
                        bitDepth,
                        colorType,
                        PNG_INTERLACE_NONE,
                        PNG_COMPRESSION_TYPE_DEFAULT,
                        PNG_FILTER_TYPE_DEFAULT);
                    png_write_info(png, *pngInfo);

                    if (bitDepth > 8 && Endian::LSB == getEndian())
                    {
                        png_set_swap(png);
                    }

                    return true;
                }

                bool scanline(png_structp png, const uint8_t* in)
                {
                    if (setjmp(png_jmpbuf(png)))
                        return false;
                    png_write_row(png, reinterpret_cast<const png_byte*>(in));
                    return true;
                }

                bool end(png_structp png, png_infop pngInfo)
                {
                    if (setjmp(png_jmpbuf(png)))
                        return false;
                    png_write_end(png, pngInfo);
                    return true;
                }
            }

            ImageWriter::ImageWriter(
                const std::string& fileName,
                const core::ImageInfo&,
                const Options& options) :
                IImageWriter(fileName, options)
            {
                _png = png_create_write_struct(
                    PNG_LIBPNG_VER_STRING,
                    &_error,
                    pngErrorFunc,
                    pngWarningFunc);
                if (!_png)
                {
                    throw std::runtime_error(Format("{0}: Cannot open").arg(fileName));
                }

#if defined(_WINDOWS)
                if (_wfopen_s(&_f, toWide(fileName).c_str(), L"wb") != 0)
                {
                    _f = nullptr;
                }
#else // _WINDOWS
                _f = fopen(fileName.c_str(), "wb");
#endif // _WINDOWS
                if (!_f)
                {
                    throw std::runtime_error(Format("{0}: Cannot open").arg(fileName));
                }
            }
            
            void ImageWriter::write(const std::shared_ptr<Image>& image)
            {
                const ImageInfo& info = image->getInfo();
                if (!open(_f, _png, &_pngInfo, info))
                {
                    throw std::runtime_error(Format("{0}: Cannot open").arg(_fileName));
                }

                size_t scanlineByteCount = 0;
                switch (info.pixelType)
                {
                case PixelType::L_U8: scanlineByteCount = info.size.w; break;
                case PixelType::L_U16: scanlineByteCount = static_cast<size_t>(info.size.w) * 2; break;
                case PixelType::LA_U8: scanlineByteCount = static_cast<size_t>(info.size.w) * 2; break;
                case PixelType::LA_U16: scanlineByteCount = static_cast<size_t>(info.size.w) * 2 * 2; break;
                case PixelType::RGB_U8: scanlineByteCount = static_cast<size_t>(info.size.w) * 3; break;
                case PixelType::RGB_U16: scanlineByteCount = static_cast<size_t>(info.size.w) * 3 * 2; break;
                case PixelType::RGBA_U8: scanlineByteCount = static_cast<size_t>(info.size.w) * 4; break;
                case PixelType::RGBA_U16: scanlineByteCount = static_cast<size_t>(info.size.w) * 4 * 2; break;
                default: break;
                }
                scanlineByteCount = getAlignedByteCount(scanlineByteCount, info.layout.alignment);
                const uint8_t* p = image->getData() + (info.size.h - 1) * scanlineByteCount;
                for (uint16_t y = 0; y < info.size.h; ++y, p -= scanlineByteCount)
                {
                    if (!scanline(_png, p))
                    {
                        throw std::runtime_error(Format("{0}: Cannot write scanline: {1}").arg(_fileName).arg(y));
                    }
                }
                if (!end(_png, _pngInfo))
                {
                    throw std::runtime_error(Format("{0}: Cannot close").arg(_fileName));
                }
            }

            ImageWriter::~ImageWriter()
            {
                if (_f)
                {
                    fclose(_f);
                }
                if (_png || _pngInfo)
                {
                    png_destroy_write_struct(
                        _png ? &_png : nullptr,
                        _pngInfo ? &_pngInfo : nullptr);
                }
            }
        }
    }
}
