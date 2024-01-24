// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

namespace tg
{
    namespace core
    {
        constexpr ImageSize::ImageSize(
            int w,
            int h,
            float pixelAspectRatio) :
            w(w),
            h(h),
            pixelAspectRatio(pixelAspectRatio)
        {}

        constexpr bool ImageSize::isValid() const
        {
            return w > 0 && h > 0;
        }

        constexpr float ImageSize::getAspect() const
        {
            return h > 0 ? (w / static_cast<float>(h) * pixelAspectRatio) : 0;
        }

        constexpr bool ImageSize::operator == (const ImageSize& other) const
        {
            return
                w == other.w &&
                h == other.h &&
                pixelAspectRatio == other.pixelAspectRatio;
        }

        constexpr bool ImageSize::operator != (const ImageSize& other) const
        {
            return !(*this == other);
        }

        inline bool ImageSize::operator < (const ImageSize& other) const
        {
            const int widthScaled = static_cast<int>(w * pixelAspectRatio);
            const int otherWidthScaled = static_cast<int>(other.w * other.pixelAspectRatio);
            return
                std::tie(widthScaled, h) <
                std::tie(otherWidthScaled, other.h);
        }

        constexpr Mirror::Mirror(bool x, bool y) :
            x(x),
            y(y)
        {}

        constexpr bool Mirror::operator == (const Mirror& other) const
        {
            return other.x == x && other.y == y;
        }

        constexpr bool Mirror::operator != (const Mirror& other) const
        {
            return !(other == *this);
        }

        inline Layout::Layout(const Mirror& mirror, int alignment, Endian endian) :
            mirror(mirror),
            alignment(alignment),
            endian(endian)
        {}

        constexpr bool Layout::operator == (const Layout & other) const
        {
            return
                other.mirror == mirror &&
                other.alignment == alignment &&
                other.endian == endian;
        }

        constexpr bool Layout::operator != (const Layout & other) const
        {
            return !(other == *this);
        }

        inline ImageInfo::ImageInfo(const ImageSize& size, PixelType pixelType) :
            size(size),
            pixelType(pixelType)
        {}
        
        inline ImageInfo::ImageInfo(int w, int h, PixelType pixelType) :
            size(w, h),
            pixelType(pixelType)
        {}

        inline bool ImageInfo::isValid() const
        {
            return size.isValid() > 0 && pixelType != PixelType::None;
        }

        inline bool ImageInfo::operator == (const ImageInfo& other) const
        {
            return
                size == other.size &&
                pixelType == other.pixelType &&
                videoLevels == other.videoLevels &&
                yuvCoefficients == other.yuvCoefficients &&
                layout == other.layout;
        }
        
        inline bool ImageInfo::operator != (const ImageInfo& other) const
        {
            return !(*this == other);
        }

        inline const ImageInfo& Image::getInfo() const
        {
            return _info;
        }

        inline const ImageSize& Image::getSize() const
        {
            return _info.size;
        }

        inline int Image::getWidth() const
        {
            return _info.size.w;
        }

        inline int Image::getHeight() const
        {
            return _info.size.h;
        }

        inline float Image::getAspect() const
        {
            return _info.size.getAspect();
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

