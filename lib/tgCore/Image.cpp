// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

#include <tgCore/Image.h>

#include <cstring>

namespace tg
{
    namespace image
    {
        size_t getByteCount(Format format, Type type)
        {
            size_t out = 0;
            switch (format)
            {
            case Format::RGBA:
                switch (type)
                {
                case Type::Float: out = 4 * sizeof(float); break;
                }
                break;
            }
            return out;
        }

        size_t Info::getByteCount() const
        {
            return size.x * size.y * image::getByteCount(format, type);
        }

        Info::Info()
        {}

        Info::Info(const math::Vector2i & size, Format format, Type type) :
            size(size),
            format(format),
            type(type)
        {}

        Info::Info(int width, int height, Format format, Type type) :
            size(width, height),
            format(format),
            type(type)
        {}

        bool Info::isValid() const
        {
            return
                size.x > 0 &&
                size.y > 0 &&
                format != Format::None &&
                type != Type::None;
        }

        void Image::_init(const Info& info)
        {
            _info = info;
            _byteCount = _info.getByteCount();
            if (_byteCount > 0)
            {
                _data = new uint8_t[_byteCount];
            }
        }

        Image::Image()
        {}

        Image::~Image()
        {
            delete[] _data;
        }

        std::shared_ptr<Image> Image::create(const Info& info)
        {
            auto out = std::shared_ptr<Image>(new Image);
            out->_init(info);
            return out;
        }

        const Info& Image::getInfo() const
        {
            return _info;
        }

        const size_t Image::getByteCount() const
        {
            return _byteCount;
        }

        const uint8_t* Image::getData() const
        {
            return _data;
        }

        uint8_t* Image::getData()
        {
            return _data;
        }

        void Image::zero()
        {
            std::memset(_data, 0, _byteCount);
        }
    }
}