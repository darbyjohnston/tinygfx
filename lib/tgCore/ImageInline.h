// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

namespace tg
{
    namespace core
    {
        inline ImageInfo::ImageInfo(const Size2I& size, PixelType pixelType) :
            size(size),
            pixelType(pixelType)
        {}
        
        inline ImageInfo::ImageInfo(int w, int h, PixelType pixelType) :
            size(w, h),
            pixelType(pixelType)
        {}

        inline bool ImageInfo::isValid() const
        {
            return size[0] > 0 && size[1] > 0 && pixelType != PixelType::None;
        }

        inline size_t ImageInfo::getByteCount() const
        {
            return size.w() * size.h() * core::getByteCount(pixelType);
        }

        inline bool ImageInfo::operator == (const ImageInfo& other) const
        {
            return size == other.size && pixelType == other.pixelType;
        }
        
        inline bool ImageInfo::operator != (const ImageInfo& other) const
        {
            return !(*this == other);
        }

        inline const ImageInfo& Image::getInfo() const
        {
            return _info;
        }

        inline const Size2I& Image::getSize() const
        {
            return _info.size;
        }

        inline int Image::getWidth() const
        {
            return _info.size[0];
        }

        inline int Image::getHeight() const
        {
            return _info.size[1];
        }

        inline float Image::getAspect() const
        {
            return aspectRatio(_info.size);
        }

        inline PixelType Image::getPixelType() const
        {
            return _info.pixelType;
        }

        inline bool Image::isValid() const
        {
            return _info.isValid();
        }

        inline size_t Image::getByteCount() const
        {
            return _info.getByteCount();
        }

        inline const uint8_t* Image::getData() const
        {
            return _data.data();
        }

        inline uint8_t* Image::getData()
        {
            return _data.data();
        }
    }
}

