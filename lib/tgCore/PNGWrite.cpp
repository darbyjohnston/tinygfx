// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCore/PNGPrivate.h>

#include <tgCore/Error.h>
#include <tgCore/Format.h>
#include <tgCore/Memory.h>
#include <tgCore/String.h>

namespace tg
{
    namespace core
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
                    switch (info.type)
                    {
                    case ImageType::L_U8:
                    case ImageType::L_U16:
                        colorType = PNG_COLOR_TYPE_GRAY;
                        break;
                    case ImageType::LA_U8:
                    case ImageType::LA_U16:
                        colorType = PNG_COLOR_TYPE_GRAY_ALPHA;
                        break;
                    case ImageType::RGB_U8:
                    case ImageType::RGB_U16:
                        colorType = PNG_COLOR_TYPE_RGB;
                        break;
                    case ImageType::RGBA_U8:
                    case ImageType::RGBA_U16:
                        colorType = PNG_COLOR_TYPE_RGB_ALPHA;
                        break;
                    default: return false;
                    }

                    const int bitDepth = getBitDepth(info.type);
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

            struct ImageWriter::Private
            {
                png_structp png = nullptr;
                png_infop   pngInfo = nullptr;
                FILE*       f = nullptr;
                ErrorStruct error;
            };

            ImageWriter::ImageWriter(
                const std::filesystem::path& path,
                const core::ImageInfo&,
                const Options& options) :
                IImageWriter(path, options),
                _p(new Private)
            {
                TG_P();
                p.png = png_create_write_struct(
                    PNG_LIBPNG_VER_STRING,
                    &p.error,
                    pngErrorFunc,
                    pngWarningFunc);
                if (!p.png)
                {
                    throw std::runtime_error(Format("{0}: Cannot open").arg(path.string()));
                }

#if defined(_WINDOWS)
                if (_wfopen_s(&p.f, path.wstring().c_str(), L"wb") != 0)
                {
                    p.f = nullptr;
                }
#else // _WINDOWS
                p.f = fopen(path.string().c_str(), "wb");
#endif // _WINDOWS
                if (!p.f)
                {
                    throw std::runtime_error(Format("{0}: Cannot open").arg(path.string()));
                }
            }
            
            void ImageWriter::write(const std::shared_ptr<Image>& image)
            {
                TG_P();
                const ImageInfo& info = image->getInfo();
                if (!open(p.f, p.png, &p.pngInfo, info))
                {
                    throw std::runtime_error(Format("{0}: Cannot open").arg(_path.string()));
                }

                size_t scanlineByteCount = 0;
                switch (info.type)
                {
                case ImageType::L_U8: scanlineByteCount = info.size.w; break;
                case ImageType::L_U16: scanlineByteCount = static_cast<size_t>(info.size.w) * 2; break;
                case ImageType::LA_U8: scanlineByteCount = static_cast<size_t>(info.size.w) * 2; break;
                case ImageType::LA_U16: scanlineByteCount = static_cast<size_t>(info.size.w) * 2 * 2; break;
                case ImageType::RGB_U8: scanlineByteCount = static_cast<size_t>(info.size.w) * 3; break;
                case ImageType::RGB_U16: scanlineByteCount = static_cast<size_t>(info.size.w) * 3 * 2; break;
                case ImageType::RGBA_U8: scanlineByteCount = static_cast<size_t>(info.size.w) * 4; break;
                case ImageType::RGBA_U16: scanlineByteCount = static_cast<size_t>(info.size.w) * 4 * 2; break;
                default: break;
                }
                scanlineByteCount = getAlignedByteCount(scanlineByteCount, info.layout.alignment);
                const uint8_t* data = image->getData() + (info.size.h - 1) * scanlineByteCount;
                for (uint16_t y = 0; y < info.size.h; ++y, data -= scanlineByteCount)
                {
                    if (!scanline(p.png, data))
                    {
                        throw std::runtime_error(Format("{0}: Cannot write scanline: {1}").arg(_path.string()).arg(y));
                    }
                }
                if (!end(p.png, p.pngInfo))
                {
                    throw std::runtime_error(Format("{0}: Cannot close").arg(_path.string()));
                }
            }

            ImageWriter::~ImageWriter()
            {
                TG_P();
                if (p.f)
                {
                    fclose(p.f);
                }
                if (p.png || p.pngInfo)
                {
                    png_destroy_write_struct(
                        p.png ? &p.png : nullptr,
                        p.pngInfo ? &p.pngInfo : nullptr);
                }
            }
        }
    }
}
