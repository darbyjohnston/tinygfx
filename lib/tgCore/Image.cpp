// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#include <tgCore/Image.h>

#include <tgCore/Error.h>
#include <tgCore/String.h>

#include <array>
#include <cstring>

namespace tg
{
    namespace core
    {
        TG_ENUM_IMPL(
            PixelType,
            "None",
            "L_U8",
            "L_U16",
            "L_U32",
            "L_F16",
            "L_F32",
            "LA_U8",
            "LA_U16",
            "LA_U32",
            "LA_F16",
            "LA_F32",
            "RGB_U8",
            "RGB_U10",
            "RGB_U16",
            "RGB_U32",
            "RGB_F16",
            "RGB_F32",
            "RGBA_U8",
            "RGBA_U16",
            "RGBA_U32",
            "RGBA_F16",
            "RGBA_F32",
            "YUV_420P_U8",
            "YUV_422P_U8",
            "YUV_444P_U8",
            "YUV_420P_U16",
            "YUV_422P_U16",
            "YUV_444P_U16",
            "ARGB_4444_Premult");

        int getChannelCount(PixelType value)
        {
            const std::array<int, static_cast<size_t>(PixelType::Count)> values =
            {
                0,
                1, 1, 1, 1, 1,
                2, 2, 2, 2, 2,
                3, 3, 3, 3, 3, 3,
                4, 4, 4, 4, 4,
                3, 3, 3,
                3, 3, 3,
                4
            };
            return values[static_cast<size_t>(value)];
        }

        int getBitDepth(PixelType value)
        {
            const std::array<int, static_cast<size_t>(PixelType::Count)> values =
            {
                0,
                8, 16, 32, 16, 32,
                8, 16, 32, 16, 32,
                8, 10, 16, 32, 16, 32,
                8, 16, 32, 16, 32,
                8, 8, 8,
                16, 16, 16,
                4
            };
            return values[static_cast<size_t>(value)];
        }

        TG_ENUM_IMPL(
            YUVCoefficients,
            "REC709",
            "BT2020");

        V4F getYUVCoefficients(YUVCoefficients value)
        {
            const std::array<V4F, static_cast<size_t>(YUVCoefficients::Count)> data =
            {
                V4F(1.79274F, 2.1124F, .213242F, .532913F),
                V4F(1.67867F, 2.14177F, .187332F, .650421F)
            };
            return data[static_cast<size_t>(value)];
        }

        TG_ENUM_IMPL(
            VideoLevels,
            "FullRange",
            "LegalRange");

        size_t ImageInfo::getByteCount() const
        {
            std::size_t out = 0;
            const size_t w = size.w;
            const size_t h = size.h;
            const size_t alignment = layout.alignment;
            switch (pixelType)
            {
            case PixelType::L_U8:     out = getAlignedByteCount(w, alignment) * h; break;
            case PixelType::L_U16:    out = getAlignedByteCount(w * 2, alignment) * h; break;
            case PixelType::L_U32:    out = getAlignedByteCount(w * 4, alignment) * h; break;
            case PixelType::L_F16:    out = getAlignedByteCount(w * 2, alignment) * h; break;
            case PixelType::L_F32:    out = getAlignedByteCount(w * 4, alignment) * h; break;

            case PixelType::LA_U8:    out = getAlignedByteCount(w * 2, alignment) * h; break;
            case PixelType::LA_U16:   out = getAlignedByteCount(w * 2 * 2, alignment) * h; break;
            case PixelType::LA_U32:   out = getAlignedByteCount(w * 2 * 4, alignment) * h; break;
            case PixelType::LA_F16:   out = getAlignedByteCount(w * 2 * 2, alignment) * h; break;
            case PixelType::LA_F32:   out = getAlignedByteCount(w * 2 * 4, alignment) * h; break;

            case PixelType::RGB_U8:   out = getAlignedByteCount(w * 3, alignment) * h; break;
            case PixelType::RGB_U10:  out = getAlignedByteCount(w * 4, alignment) * h; break;
            case PixelType::RGB_U16:  out = getAlignedByteCount(w * 3 * 2, alignment) * h; break;
            case PixelType::RGB_U32:  out = getAlignedByteCount(w * 3 * 4, alignment) * h; break;
            case PixelType::RGB_F16:  out = getAlignedByteCount(w * 3 * 2, alignment) * h; break;
            case PixelType::RGB_F32:  out = getAlignedByteCount(w * 3 * 4, alignment) * h; break;

            case PixelType::RGBA_U8:  out = getAlignedByteCount(w * 4, alignment) * h; break;
            case PixelType::RGBA_U16: out = getAlignedByteCount(w * 4 * 2, alignment) * h; break;
            case PixelType::RGBA_U32: out = getAlignedByteCount(w * 4 * 4, alignment) * h; break;
            case PixelType::RGBA_F16: out = getAlignedByteCount(w * 4 * 2, alignment) * h; break;
            case PixelType::RGBA_F32: out = getAlignedByteCount(w * 4 * 4, alignment) * h; break;

            //! \todo Is YUV data aligned?
            case PixelType::YUV_420P_U8:  out = w * h + (w / 2 * h / 2) + (w / 2 * h / 2); break;
            case PixelType::YUV_422P_U8:  out = w * h + (w / 2 * h) + (w / 2 * h); break;
            case PixelType::YUV_444P_U8:  out = w * h * 3; break;
            case PixelType::YUV_420P_U16: out = (w * h + (w / 2 * h / 2) + (w / 2 * h / 2)) * 2; break;
            case PixelType::YUV_422P_U16: out = (w * h + (w / 2 * h) + (w / 2 * h)) * 2; break;
            case PixelType::YUV_444P_U16: out = (w * h * 3) * 2; break;

            case PixelType::ARGB_4444_Premult: out = w * h * 4 * 2; break;

            default: break;
            }
            return out;
        }
        
        Image::Image(const ImageInfo& info) :
            _info(info)
        {
            _byteCount = info.getByteCount();
            _data.reserve(_byteCount);
        }

        Image::~Image()
        {}

        std::shared_ptr<Image> Image::create(const ImageInfo& info)
        {
            return std::shared_ptr<Image>(new Image(info));
        }

        std::shared_ptr<Image> Image::create(const Size2I& size, PixelType pixelType)
        {
            return std::shared_ptr<Image>(new Image(ImageInfo(size, pixelType)));
        }

        std::shared_ptr<Image> Image::create(int w, int h, PixelType pixelType)
        {
            return std::shared_ptr<Image>(new Image(ImageInfo(w, h, pixelType)));
        }
        
        void Image::zero()
        {
            memset(_data.data(), 0, _byteCount);
        }
    }
}

