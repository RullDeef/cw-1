#ifndef VECT_T_HPP
#define VECT_T_HPP

#include <cstdlib>


namespace Core
{
    template<typename T>
    struct vect_t
    {
        size_t size;
        size_t capacity;

        T* data;
    };

    template<typename T>
    vect_t<T> make_vect(size_t capacity = 0)
    {
        vect_t<T> vect;
        vect.size = 0;

        vect.capacity = capacity;
        if (capacity == 0)
            vect.data = nullptr;
        else
        {
            vect.data = static_cast<T*>(std::malloc(capacity * sizeof(T)));
            // error pulling if data == nullptr
        }

        return vect;
    }

    template<typename T>
    void destroy(vect_t<T>& vect)
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
    bool set(vect_t<T>& vect, size_t index, const T& value)
    {
        if (index < vect.size)
        {
            vect.data[index] = value;
            return true;
        }
        return false;
    }

    template<typename T>
    bool get(const vect_t<T>& vect, size_t index, T& value)
    {
        if (index < vect.size)
        {
            value = vect.data[index];
            return true;
        }

        return false;
    }

    template<typename T>
    bool at(vect_t<T>& vect, size_t index, T*& ref)
    {
        if (index < vect.size)
        {
            ref = &vect.data[index];
            return true;
        }

        return false;
    }

    template<typename T>
    bool at(const vect_t<T>& vect, size_t index, const T*& ref)
    {
        if (index < vect.size)
        {
            ref = &vect.data[index];
            return true;
        }

        return false;
    }
}

#endif // VECT_T_HPP
