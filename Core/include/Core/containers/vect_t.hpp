#ifndef VECT_T_HPP
#define VECT_T_HPP

#include <cstdlib>


namespace Core
{
    constexpr auto VECT_CAPACITY_MULTIPLIER = 1.5;

    template<typename T>
    struct vect_t
    {
        size_t size;
        size_t capacity;

        T* data;
    };

    template<typename T>
    vect_t<T> make_vect(size_t capacity = 0);

    template<typename T>
    void destroy(vect_t<T>& vect);

    template<typename T>
    bool is_valid(const vect_t<T>& vect);

    template<typename T>
    bool reserve(vect_t<T>& vect, size_t newCapacity);

    template<typename T>
    bool set(vect_t<T>& vect, size_t index, const T& value);

    template<typename T>
    bool get(const vect_t<T>& vect, size_t index, T& value);

    template<typename T>
    bool at(vect_t<T>& vect, size_t index, T*& ref);

    template<typename T>
    bool at(const vect_t<T>& vect, size_t index, const T*& ref);

    template<typename T>
    bool push_back(vect_t<T>& vect, const T& value);

    template<typename T>
    bool push_front(vect_t<T>& vect, const T& value);
}

#include "vect_t_imp.hpp"

#endif // VECT_T_HPP
