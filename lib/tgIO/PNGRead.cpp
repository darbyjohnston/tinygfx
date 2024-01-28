// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgIO/PNG.h>

#include <tgCore/Memory.h>
#include <tgCore/Format.h>
#include <tgCore/String.h>

#include <cstring>

using namespace tg::core;

namespace tg
{
    namespace io
    {
        namespace png
        {
            namespace
            {
                void memoryRead(png_structp png_ptr, png_bytep outBytes, png_size_t byteCountToRead)
                {
                    png_voidp io_ptr = png_get_io_ptr(png_ptr);
                    InMemoryFile* memory = static_cast<InMemoryFile*>(io_ptr);
                    if (byteCountToRead > memory->size)
                    {
                        png_error(png_ptr, "Cannot read");
                    }
                    memcpy(outBytes, memory->p, byteCountToRead);
                    memory->p += byteCountToRead;
                    memory->size -= byteCountToRead;
                }

                bool open(
                    FILE* f,
                    InMemoryFile* memory,
                    png_structp png,
                    png_infop* pngInfo,
                    png_infop* pngInfoEnd,
                    uint16_t& width,
                    uint16_t& height,
                    uint8_t& channels,
                    uint8_t& bitDepth)
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

                    *pngInfoEnd = png_create_info_struct(png);
                    if (!*pngInfoEnd)
                    {
                        return false;
                    }

                    uint8_t tmp[8];
                    if (memory->p)
                    {
                        if (memory->size < 8)
                        {
                            return false;
                        }
                        memcpy(tmp, memory->p, 8);
                        memory->p += 8;
                        memory->size -= 8;
                    }
                    else
                    {
                        if (fread(tmp, 8, 1, f) != 1)
                        {
                            return false;
                        }
                    }
                    if (png_sig_cmp(tmp, 0, 8))
                    {
                        return false;
                    }

                    if (memory->p)
                    {
                        png_set_read_fn(png, memory, memoryRead);
                    }
                    else
                    {
                        png_init_io(png, f);
                    }
                    png_set_sig_bytes(png, 8);
                    png_read_info(png, *pngInfo);

                    if (png_get_interlace_type(png, *pngInfo) != PNG_INTERLACE_NONE)
                    {
                        return false;
                    }

                    png_set_expand(png);
                    //png_set_gray_1_2_4_to_8(png);
                    png_set_palette_to_rgb(png);
                    png_set_tRNS_to_alpha(png);

                    width = png_get_image_width(png, *pngInfo);
                    height = png_get_image_height(png, *pngInfo);

                    channels = png_get_channels(png, *pngInfo);
                    if (png_get_color_type(png, *pngInfo) == PNG_COLOR_TYPE_PALETTE)
                    {
                        channels = 3;
                    }
                    if (png_get_valid(png, *pngInfo, PNG_INFO_tRNS))
                    {
                        ++channels;
                    }
                    bitDepth = png_get_bit_depth(png, *pngInfo);
                    if (bitDepth < 8)
                    {
                        bitDepth = 8;
                    }

                    if (bitDepth >= 16 && Endian::LSB == getEndian())
                    {
                        png_set_swap(png);
                    }

                    return true;
                }

                bool scanline(png_structp png, uint8_t* out)
                {
                    if (setjmp(png_jmpbuf(png)))
                    {
                        return false;
                    }
                    png_read_row(png, out, 0);
                    return true;
                }

                bool end(png_structp png, png_infop pngInfo)
                {
                    if (setjmp(png_jmpbuf(png)))
                    {
                        return false;
                    }
                    png_read_end(png, pngInfo);
                    return true;
                }
            }

            ImageReader::ImageReader(
                const std::string& fileName,
                const InMemoryFile* memory,
                const Options& options) :
                IImageReader(fileName, memory, options)
            {
                
                _png = png_create_read_struct(
                    PNG_LIBPNG_VER_STRING,
                    &_error,
                    pngErrorFunc,
                    pngWarningFunc);

                if (memory)
                {
                    _memory.p = memory->p;
                    _memory.size = memory->size;
                }
                else
                {
#if defined(_WINDOWS)
                    if (_wfopen_s(&_f, toWide(fileName).c_str(), L"rb") != 0)
                    {
                        _f = nullptr;
                    }
#else // _WINDOWS
                    _f = fopen(fileName.c_str(), "rb");
#endif // _WINDOWS
                    if (!_f)
                    {
                        throw std::runtime_error(Format("{0}: Cannot open").arg(fileName));
                    }
                }

                uint16_t width = 0;
                uint16_t height = 0;
                uint8_t channels = 0;
                uint8_t bitDepth = 0;
                if (!open(
                    _f,
                    &_memory,
                    _png,
                    &_pngInfo,
                    &_pngInfoEnd,
                    width,
                    height,
                    channels,
                    bitDepth))
                {
                    throw std::runtime_error(Format("{0}: Cannot open").arg(fileName));
                }
                _scanlineSize = width * channels * bitDepth / 8;

                PixelType pixelType = PixelType::None;
                switch (channels)
                {
                    case 1:
                        switch (bitDepth)
                        {
                        case 8: pixelType = PixelType::L_U8; break;
                        case 16: pixelType = PixelType::L_U16; break;
                        default: break;
                        }
                        break;
                    case 2:
                        switch (bitDepth)
                        {
                        case 8: pixelType = PixelType::LA_U8; break;
                        case 16: pixelType = PixelType::LA_U16; break;
                        default: break;
                        }
                        break;
                    case 3:
                        switch (bitDepth)
                        {
                        case 8: pixelType = PixelType::RGB_U8; break;
                        case 16: pixelType = PixelType::RGB_U16; break;
                        default: break;
                        }
                        break;
                    case 4:
                        switch (bitDepth)
                        {
                        case 8: pixelType = PixelType::RGBA_U8; break;
                        case 16: pixelType = PixelType::RGBA_U16; break;
                        default: break;
                        }
                        break;
                    default: break;
                }
                if (PixelType::None == pixelType)
                {
                    throw std::runtime_error(Format("{0}: Cannot open").arg(fileName));
                }

                _info = ImageInfo(width, height, pixelType);
                _info.layout.mirror.y = true;
            }
            
            ImageReader::~ImageReader()
            {
                if (_f)
                {
                    fclose(_f);
                }
                if (_png || _pngInfo || _pngInfoEnd)
                {
                    png_destroy_read_struct(
                        _png ? &_png : nullptr,
                        _pngInfo ? &_pngInfo : nullptr,
                        _pngInfoEnd ? &_pngInfoEnd : nullptr);
                }
            }

            const ImageInfo& ImageReader::getInfo() const
            {
                return _info;
            }

            std::shared_ptr<Image> ImageReader::read()
            {
                auto out = Image::create(_info);
                uint8_t* p = out->getData();
                for (uint16_t y = 0; y < _info.size.h; ++y, p += _scanlineSize)
                {
                    if (!scanline(_png, p))
                    {
                        break;
                    }
                }
                end(_png, _pngInfoEnd);
                return out;
            }
        }
    }
}

