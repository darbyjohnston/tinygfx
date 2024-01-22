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
            "RGB_U16",
            "RGB_U32",
            "RGB_F16",
            "RGB_F32",
            "RGBA_U8",
            "RGBA_U16",
            "RGBA_U32",
            "RGBA_F16",
            "RGBA_F32");
        
        size_t getByteCount(PixelType value)
        {
            const std::array<size_t, static_cast<size_t>(PixelType::Count)> data =
            {
                0,
                
                1 * sizeof(uint8_t),
                1 * sizeof(uint16_t),
                1 * sizeof(uint32_t),
                1 * 2,
                1 * sizeof(float),
                
                2 * sizeof(uint8_t),
                2 * sizeof(uint16_t),
                2 * sizeof(uint32_t),
                2 * 2,
                2 * sizeof(float),
                
                3 * sizeof(uint8_t),
                3 * sizeof(uint16_t),
                3 * sizeof(uint32_t),
                3 * 2,
                3 * sizeof(float),
                
                4 * sizeof(uint8_t),
                4 * sizeof(uint16_t),
                4 * sizeof(uint32_t),
                4 * 2,
                4 * sizeof(float)
            };
            return data[static_cast<size_t>(value)];
        }
        
        Image::Image(const ImageInfo& info) :
            _info(info)
        {
            const size_t byteCount = info.getByteCount();
            _data.reserve(byteCount);
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
            memset(_data.data(), 0, _data.size());
        }
    }
}

