// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#pragma once

#include <tgCore/Vector.h>

#include <cstdint>
#include <memory>

namespace tg
{
    namespace image
    {
        //! Image formats.
        enum class Format
        {
            None,
            RGBA,

            Count,
            First = None
        };

        //! Image types.
        enum class Type
        {
            None,
            Float,

            Count,
            First = None
        };

        //! Get the number of bytes used for the given format and type.
        size_t getByteCount(Format, Type);

        //! Image information.
        class Info
        {
        public:
            Info();
            Info(const math::Vector2i& size, Format, Type);

            math::Vector2i size = math::Vector2i(0, 0);
            Format format = Format::None;
            Type type = Type::None;

            //! Get the byte count.
            size_t getByteCount() const;

            //! Is the information valid?
            bool isValid() const;
        };

        //! Image.
        class Image
        {
            void _init(const Info&);

            Image();

        public:
            ~Image();

            //! Create a new image.
            static std::shared_ptr<Image> create(const Info&);

            //! Get the information.
            const Info& getInfo() const;

            //! Get the byte count.
            const size_t getByteCount() const;

            //! Get the data.
            const uint8_t* getData() const;

            //! Get the data.
            uint8_t* getData();

        private:
            Info _info;
            size_t _byteCount = 0;
            uint8_t* _data = nullptr;
        };
    }
}
