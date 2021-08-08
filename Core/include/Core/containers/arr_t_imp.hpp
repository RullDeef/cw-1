#ifndef ARR_T_IMP_HPP
#define ARR_T_IMP_HPP

#include "arr_t.hpp"


namespace Core
{
    template<typename T, size_t capacity>
    arr_t<T, capacity> make_arr()
    {
        arr_t<T, capacity> arr{};

        arr.size = 0;

        return arr;
    }

    template<typename T, size_t capacity>
    bool is_valid(const arr_t<T, capacity>& arr);

    template<typename T, size_t capacity>
    bool set(arr_t<T, capacity>& arr, size_t index, const T& value);

    template<typename T, size_t capacity>
    bool get(const arr_t<T, capacity>& arr, size_t index, T& value)
    {
        if (index < arr.size)
        {
            value = arr.data[index];
            return true;
        }
        return false;
    }

    template<typename T, size_t capacity>
    bool at(arr_t<T, capacity>& arr, size_t index, T*& ref)
    {
        if (index < arr.size)
        {
            ref = &arr.data[index];
            return true;
        }
        return false;
    }

    template<typename T, size_t capacity>
    bool at(const arr_t<T, capacity>& arr, size_t index, const T*& ref);

    template<typename T, size_t capacity>
    bool push_back(arr_t<T, capacity>& arr, const T& value)
    {
        if (arr.size < capacity)
        {
            arr.data[arr.size] = value;
            arr.size++;
            return true;
        }
        return false;
    }

    template<typename T, size_t capacity>
    bool push_front(arr_t<T, capacity>& arr, const T& value);
}

#endif // ARR_T_IMP_HPP
