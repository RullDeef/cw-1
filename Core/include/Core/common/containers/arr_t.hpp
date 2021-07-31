#ifndef ARR_T_HPP
#define ARR_T_HPP

#include <cstddef>


namespace Core
{
    template<typename T, size_t capacity>
    struct arr_t
    {
        size_t size;
        T data[capacity];
    };

    template<typename T, size_t capacity>
    arr_t<T, capacity> make_arr();

    template<typename T, size_t capacity>
    bool is_valid(const arr_t<T, capacity>& arr);

    template<typename T, size_t capacity>
    bool set(arr_t<T, capacity>& arr, size_t index, const T& value);

    template<typename T, size_t capacity>
    bool get(const arr_t<T, capacity>& arr, size_t index, T& value);

    template<typename T, size_t capacity>
    bool at(arr_t<T, capacity>& arr, size_t index, T*& ref);

    template<typename T, size_t capacity>
    bool at(const arr_t<T, capacity>& arr, size_t index, const T*& ref);

    template<typename T, size_t capacity>
    bool push_back(arr_t<T, capacity>& arr, const T& value);

    template<typename T, size_t capacity>
    bool push_front(arr_t<T, capacity>& arr, const T& value);
}

#include "Core/common/containers/arr_t_imp.hpp"

#endif // ARR_T_HPP
