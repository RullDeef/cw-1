#ifndef LIST_T_HPP
#define LIST_T_HPP

#include <cstdlib>


namespace Core
{
    template<typename T>
    struct list_node
    {
        list_node<T>* next;
        T value;
    };

    template<typename T>
    struct list_t
    {
        list_node<T>* head;
        size_t size;
    };

    template<typename T>
    list_t<T> make_list();

    template<typename T>
    void destroy(list_t<T>& list);

    template<typename T>
    void push_back(list_t<T>& list, const T& value);
}

#include "list_t_imp.hpp"

#endif // LIST_T_HPP
