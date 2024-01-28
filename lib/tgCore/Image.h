// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/Memory.h>
#include <tgCore/Range.h>
#include <tgCore/Util.h>
#include <tgCore/Vector.h>

#include <iostream>
#include <cstdint>
#include <map>
#include <memory>
#include <string>
#include <vector>

namespace tg
{
    namespace core
    {
        //! \name Images
        ///@{

        //! Pixel types.
        enum class PixelType
        {
            None,

            L_U8,
            L_U16,
            L_U32,
            L_F16,
            L_F32,

            LA_U8,
            LA_U16,
            LA_U32,
            LA_F16,
            LA_F32,

            RGB_U8,
            RGB_U10,
            RGB_U16,
            RGB_U32,
            RGB_F16,
            RGB_F32,

            RGBA_U8,
            RGBA_U16,
            RGBA_U32,
            RGBA_F16,
            RGBA_F32,

            YUV_420P_U8,
            YUV_422P_U8,
            YUV_444P_U8,

            YUV_420P_U16,
            YUV_422P_U16,
            YUV_444P_U16,

            ARGB_4444_Premult,

            Count,
            First = None
        };
        TG_ENUM(PixelType);

        //! Get the number of channels for the given pixel type.
        int getChannelCount(PixelType);

        //! Get the bit-depth for the given pixel type.
        int getBitDepth(PixelType);

        //! Video levels.
        enum class VideoLevels
        {
            FullRange,
            LegalRange,

            Count,
            First = FullRange
        };
        TG_ENUM(VideoLevels);

        //! YUV coefficients.
        enum class YUVCoefficients
        {
            REC709,
            BT2020,

            Count,
            First = REC709
        };
        TG_ENUM(YUVCoefficients);

        //! Get YUV coefficients.
        V4F getYUVCoefficients(YUVCoefficients);

        //! Image mirroring.
        class ImageMirror
        {
        public:
            ImageMirror() = default;
            constexpr ImageMirror(bool x, bool y);

            bool x = false;
            bool y = false;

            constexpr bool operator == (const ImageMirror&) const;
            constexpr bool operator != (const ImageMirror&) const;
        };

        //! Image data layout.
        class ImageLayout
        {
        public:
            ImageLayout() = default;
            ImageLayout(
                const ImageMirror& mirror,
                int                alignment = 1,
                Endian             endian    = getEndian());

            ImageMirror mirror;
            int         alignment = 1;
            Endian      endian    = getEndian();

            constexpr bool operator == (const ImageLayout&) const;
            constexpr bool operator != (const ImageLayout&) const;
        };

        //! Image information.
        struct ImageInfo
        {
            ImageInfo() = default;
            ImageInfo(const Size2I&, PixelType);
            ImageInfo(int w, int h, PixelType);

            Size2I          size;
            PixelType       pixelType        = PixelType::None;
            float           pixelAspectRatio = 1.F;
            VideoLevels     videoLevels      = VideoLevels::FullRange;
            YUVCoefficients yuvCoefficients  = YUVCoefficients::REC709;
            ImageLayout     layout;

            //! Is the information valid?
            bool isValid() const;
                
            //! Get the aspect ratio.
            float getAspect() const;

            //! Get the number of bytes used to store an image.
            size_t getByteCount() const;

            bool operator == (const ImageInfo&) const;
            bool operator != (const ImageInfo&) const;
        };

        //! Image tags.
        typedef std::map<std::string, std::string> ImageTags;

        //! Image.
        class Image : public std::enable_shared_from_this<Image>
        {
            TG_NON_COPYABLE(Image);

        protected:
            Image(const ImageInfo&);

        public:
            ~Image();

            //! Create a new image.
            static std::shared_ptr<Image> create(const ImageInfo&);

            //! Create a new image.
            static std::shared_ptr<Image> create(const Size2I&, PixelType);

            //! Create a new image.
            static std::shared_ptr<Image> create(int w, int h, PixelType);

            //! Get the image information.
            const ImageInfo& getInfo() const;
            
            //! Get the image size.
            const Size2I& getSize() const;

            //! Get the image width.
            int getWidth() const;

            //! Get the image height.
            int getHeight() const;

            //! Get the aspect ratio.
            float getAspect() const;

            //! Get the image pixel type.
            PixelType getPixelType() const;

            //! Is the image valid?
            bool isValid() const;

            //! Get the image tags.
            const ImageTags& getTags() const;

            //! Set the image tags.
            void setTags(const ImageTags&);

            //! Get the number of bytes used to store the image data.
            size_t getByteCount() const;

            //! Get the image data.
            const uint8_t* getData() const;

            //! Get the image data.
            uint8_t* getData();

            //! Zero the image data.
            void zero();

        private:
            ImageInfo _info;
            ImageTags _tags;
            size_t _byteCount = 0;
            std::vector<uint8_t> _data;
        };

        ///@}
    }
}

#include <tgCore/ImageInline.h>

