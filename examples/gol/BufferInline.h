// SPDX-License-Identifier: BSD-3-Clause
// Copyright (c) 2022 Darby Johnston
// All rights reserved.

namespace tg
{
    template<typename T>
    inline Buffer<T>::Buffer()
    {}

    template<typename T>
    inline Buffer<T>::Buffer(const math::Vector2i& size) :
        _size(size)
    {
        _data.resize(_size.x * _size.y);
    }

    template<typename T>
    inline const math::Vector2i& Buffer<T>::getSize() const
    {
        return _size;
    }

    template<typename T>
    inline const T& Buffer<T>::get(const math::Vector2i& pos) const
    {
        return _data[pos.y * _size.x + pos.x];
    }

    template<typename T>
    inline void Buffer<T>::set(const T& value, const math::Vector2i& pos)
    {
        _data[pos.y * _size.x + pos.x] = value;
    }

    template<typename T>
    inline const std::vector<T>& Buffer<T>::getData() const
    {
        return _data;
    }

    template<typename T>
    inline DoubleBuffer<T>::DoubleBuffer()
    {}

    template<typename T>
    inline DoubleBuffer<T>::DoubleBuffer(const math::Vector2i& size)
    {
        _buffer[0] = Buffer<T>(size);
        _buffer[1] = Buffer<T>(size);
    }

    template<typename T>
    inline const math::Vector2i& DoubleBuffer<T>::getSize() const
    {
        return _buffer[_current].getSize();
    }

    template<typename T>
    inline const T& DoubleBuffer<T>::get(const math::Vector2i& pos) const
    {
        return _buffer[_current].get(pos);
    }

    template<typename T>
    inline void DoubleBuffer<T>::set(const T& value, const math::Vector2i& pos)
    {
        _buffer[0 == _current ? 1 : 0].set(value, pos);
    }

    template<typename T>
    inline void DoubleBuffer<T>::swap()
    {
        _current = 0 == _current ? 1 : 0;
    }

    template<typename T>
    inline const Buffer<T>& DoubleBuffer<T>::getBuffer() const
    {
        return _buffer[_current];
    }
}
