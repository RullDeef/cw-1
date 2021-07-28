#ifndef LIST_T_IMP_HPP
#define LIST_T_IMP_HPP

#include "Core/common/containers/list_t.hpp"


namespace Core
{
    template<typename T>
    list_t<T> make_list()
    {
        list_t<T> list;
        list.size = 0;
        list.head = nullptr;
        return list;
    }

    template<typename T>
    void destroy(list_t<T>& list)
    {
        for (auto node = list.head; node;)
        {
            auto next = node->next;
            std::free(node);
            node = next;
        }
        list.size = 0;
        list.head = nullptr;
    }

    template<typename T>
    void push_back(list_t<T>& list, const T& value)
    {
        if (list.head == nullptr)
        {
            list.head = static_cast<list_node<T>*>(std::calloc(1, sizeof(list_node<T>)));
            list.head->value = value;
            list.size = 1;
        }
        else
        {
            auto node = list.head;
            while (node->next != nullptr)
                node = node->next;

            node->next = static_cast<list_node<T>*>(std::calloc(1, sizeof(list_node<T>)));
            node->next->value = value;
            list.size++;
        }
    }
}

#endif // LIST_T_IMP_HPP
