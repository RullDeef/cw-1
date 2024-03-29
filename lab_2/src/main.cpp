﻿#include <iostream>
#include "list/list.hpp"

#define TEST_BEGIN                                                          \
    std::cout   << "============= Test: "                                   \
                << __func__                                                 \
                << " =============" << std::endl;                           \
    int failed = 0;

#define TEST_END                                                            \
    if (failed > 0)                                                         \
        std::cout << __func__ << ": FAILED." << std::endl;                  \
    else                                                                    \
        std::cout << __func__ << ": PASSED." << std::endl;                  \
    return failed;

#define SUB_TEST(func) failed += func();

#define ASSERT(expr)                                                        \
    if (!(expr)) {                                                          \
        std::cout   << "ASSERTION FAILED: " << #expr                        \
                    << "\n  " << __LINE__ << std::endl;                     \
        failed++;                                                           \
    }

int test_constructors();
int test_foreach();
int test_clear();
int test_operators();
int test_add_diff_types();
int test_insert();
int test_erase();
int test_sublist();

int main()
{
    TEST_BEGIN;

    SUB_TEST(test_constructors);
    SUB_TEST(test_foreach);
    SUB_TEST(test_clear);
    SUB_TEST(test_operators);
    SUB_TEST(test_add_diff_types);
    SUB_TEST(test_insert);
    SUB_TEST(test_erase);
    SUB_TEST(test_sublist);

    TEST_END;
}

int test_constructors()
{
    TEST_BEGIN;

    list<double> list_double = list<double>(1.4, 1.2, -1.3);
    list<double> list_double_2(list_double);
    list<double> list_double_3 = list_double_2;

    ASSERT(list_double == list_double_2);
    ASSERT(list_double == list_double_3);

    std::cout << list_double << std::endl;
    std::cout << list_double_2 << std::endl;
    std::cout << list_double_3 << std::endl;

    list<float> list_float = list<int>(list_double);
    ASSERT(list_float.size() == list_double.size());

    std::cout << list_float << std::endl;

    list<int> list_init_list = {};
    list<int> list_init_list_2 = { 1, 2, 4, 2, 3 };

    ASSERT(list_init_list.size() == 0);
    ASSERT(list_init_list_2.size() == 5);

    std::cout << list_init_list << std::endl;
    std::cout << list_init_list_2 << std::endl;

    list<const char*> list_str("string 1", "string 2", "string 3");
    ASSERT(list_str.size() == 3);

    std::cout << list_str << std::endl;

    bool* bools = new bool[5] { true, false, false, true, false };
    list<bool> list_bool(bools, 5);

    std::cout << std::boolalpha << list_bool << std::endl;

    TEST_END;
}

int test_foreach()
{
    TEST_BEGIN;

    list<int> int_list = { 3, 5, 2, 0, 4 };

    // test for each loop (non-const)
    for (auto& value : int_list)
        std::cout << "value : " << value << std::endl;
    std::cout << std::endl;

    // test for each loop (const)
    const list<int>& cint_list = int_list;
    for (const auto& value : cint_list)
        std::cout << "const value : " << value << std::endl;
    std::cout << std::endl;

    TEST_END;
}

int test_clear()
{
    TEST_BEGIN;

    list<char> syms = {'c', 'd', 'a'};

    ASSERT(syms.size() == 3);

    std::cout << "syms: " << syms << std::endl;
    std::cout << "size = " << syms.size() << std::endl;

    syms.clear();
    ASSERT(syms.size() == 0);

    std::cout << "syms after clear: " << syms << std::endl;
    std::cout << "size = " << syms.size() << std::endl;

    TEST_END;
}

int test_operators()
{
    TEST_BEGIN;

    list<float> floats = { 1.0f, 2.0f, 3.0f };
    list<float> floats_2 = floats + 4.0f;

    ASSERT(floats.size() == 3);
    ASSERT(floats_2.size() == 4);

    ASSERT((floats_2 + floats).size() == 7);

    floats = floats_2 + 1.2f + floats + 1.3f + 4.5f;
    ASSERT(floats.size() == 10);

    std::cout << floats << std::endl;

    TEST_END;
}

int test_add_diff_types()
{
    TEST_BEGIN;

    list<int> int_list = { 1, 2, 3 };
    list<float> float_list = { 1.5f, 2.5f, 3.2f };

    list<float> res = int_list + float_list;
    std::cout << res << std::endl;

    TEST_END;
}

int test_insert()
{
    TEST_BEGIN;

    list<int> list_int;
    int value = 101;

    /// INSERT IN EMPTY LIST ====================

    list_int.insert(list_int.begin(), value);
    ASSERT(list_int.size() == 1);
    ASSERT(list_int.at(0) == value);

    list_int.clear();
    list_int.insert(list_int.end(), value);
    ASSERT(list_int.size() == 1);
    ASSERT(list_int.at(0) == value);

    /// INSERT IN LIST WITH ONE ELEMENT =========

    list_int = { 2 * value };
    list_int.insert(list_int.begin(), value);
    ASSERT(list_int.size() == 2);
    ASSERT(list_int.front() == value);

    list_int = { 2 * value };
    list_int.insert(list_int.end(), value);
    ASSERT(list_int.size() == 2);
    ASSERT(list_int.back() == value);

    /// INSERT IN ARBITRARY POSITION ============

    {
        list_int = { 1, 2, 3, 4, 5 };
        auto iter = list_int.cbegin();
        ++ ++ ++iter;
        auto res_iter = list_int.insert(iter, value);
        std::cout << list_int << std::endl;
        std::cout << *res_iter << std::endl;
    }

    /// INSERT INITIALIZER LIST =================

    {
        list_int = { 1, 2, 3, 4 };
        auto iter = list_int.cbegin();
        ++ ++iter;
        auto res_iter = list_int.insert(iter, { 5, 6, 7 });
        std::cout << list_int << std::endl;
        std::cout << *res_iter << std::endl;
    }

    TEST_END;
}

int test_erase()
{
    TEST_BEGIN;

    list<int> a = { 1, 2, 3 };
    auto pos = a.begin();
    pos++;
    pos = a.erase(pos);

    std::cout << "erased before: " << *pos << ", list: " << a << std::endl;
    ASSERT(*pos == 3);

    pos = a.erase(pos);
    std::cout << "erased. pos is end: " << std::boolalpha << (pos == a.end()) << std::endl;
    ASSERT(pos == a.end());

    TEST_END;
}

int test_sublist()
{
    TEST_BEGIN;

    list<int> a = { 1, 2, 3, 4, 5, 6, 7 };
    auto b = a.sublist(++a.begin(), 3);

    std::cout << a << ", " << b << std::endl;
    ASSERT(a.size() == 4);
    ASSERT(b.size() == 3);

    TEST_END;
}
