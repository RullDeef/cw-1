#ifndef VECT_T_IMP_HPP
#define VECT_T_IMP_HPP

#include "Core/common/containers/vect_t.hpp"


namespace Core
{
    template<typename T>
    vect_t <T> make_vect(size_t capacity)
    {
        vect_t<T> vect;
        vect.size = 0;

        vect.capacity = capacity;
        if (capacity == 0)
            vect.data = nullptr;
        else
        {
            vect.data = static_cast<T *>(std::malloc(capacity * sizeof(T)));
            // error pulling if data == nullptr
        }

        return vect;
    }

    template<typename T>
    void destroy(vect_t <T> &vect)
    {
        if (vect.data != nullptr)
        {
            std::free(vect.data);
            vect.data = nullptr;
        }
        vect.size = 0;
        vect.capacity = 0;
    }

    template<typename T>
    bool is_valid(const vect_t <T> &vect)
    {
        return vect.data != nullptr && vect.capacity > 0;
    }

    template<typename T>
    bool reserve(vect_t <T> &vect, size_t newCapacity)
    {
        if (!is_valid(vect))
            return false;

        if (vect.capacity >= newCapacity)
            return true;

        auto newPtr = std::realloc(vect.data, newCapacity * sizeof(T));
        if (newPtr == nullptr)
            return false;

        vect.data = (T *) newPtr;
        vect.capacity = newCapacity;
        return true;
    }

    template<typename T>
    bool set(vect_t <T> &vect, size_t index, const T &value)
    {
        if (is_valid(vect) && index < vect.size)
        {
            vect.data[index] = value;
            return true;
        }
        return false;
    }

    template<typename T>
    bool get(const vect_t <T> &vect, size_t index, T &value)
    {
        if (is_valid(vect) && index < vect.size)
        {
            value = vect.data[index];
            return true;
        }

        return false;
    }

    template<typename T>
    bool at(vect_t <T> &vect, size_t index, T *&ref)
    {
        if (is_valid(vect) && index < vect.size)
        {
            ref = &vect.data[index];
            return true;
        }

        return false;
    }

    template<typename T>
    bool at(const vect_t <T> &vect, size_t index, const T *&ref)
    {
        if (is_valid(vect) && index < vect.size)
        {
            ref = &vect.data[index];
            return true;
        }

        return false;
    }

    template<typename T>
    bool push_back(vect_t <T> &vect, const T &value)
    {
        if (!is_valid(vect))
            return false;

        if (vect.size == vect.capacity)
            if (!reserve(vect, VECT_CAPACITY_MULTIPLIER * vect.capacity))
                return false;

        vect.data[vect.size] = value;
        vect.size++;
        return true;
    }
}

#endif // VECT_T_IMP_HPP
