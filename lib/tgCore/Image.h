// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2024 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/Range.h>
#include <tgCore/Size.h>
#include <tgCore/Util.h>

#include <iostream>
#include <cstdint>
#include <memory>
#include <string>
#include <vector>

namespace tg
{
    namespace core
    {
        //! \name Pixel Types
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
            RGB_U16,
            RGB_U32,
            RGB_F16,
            RGB_F32,

            RGBA_U8,
            RGBA_U16,
            RGBA_U32,
            RGBA_F16,
            RGBA_F32,

            Count,
            First = None
        };
        TG_ENUM(PixelType);
        
        //! Get the number of bytes used to store a pixel.
        size_t getByteCount(PixelType);

        ///@}

        //! Image information.
        struct ImageInfo
        {
            ImageInfo() = default;
            ImageInfo(const Size2I&, PixelType);
            ImageInfo(int w, int h, PixelType);

            Size2I size;
            PixelType pixelType = PixelType::None;

            //! Is the information valid?
            bool isValid() const;
        
            //! Get the number of bytes used to store an image.
            size_t getByteCount() const;

            bool operator == (const ImageInfo&) const;
            bool operator != (const ImageInfo&) const;
        };

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
            std::vector<uint8_t> _data;
        };
    }
}

#include <tgCore/ImageInline.h>

