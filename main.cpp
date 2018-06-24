#include <iostream>
#include <vector>
#include <algorithm>
#include "circularbuffer.h"

template<typename C, typename T>
void mass_push_back(C &c, std::initializer_list<T> elems) {
    for (T const &e : elems)
        c.push_back(e);
}

bool test_simple1() {
    size_t counts = 1000;
    buffer<int> cb(1);
    std::vector<int> ans;
    for (size_t i = 0; i < counts; i++) {
        cb.push_front(i);
        ans.push_back(i);

    }
    std::reverse(ans.begin(), ans.end());
    for (size_t i = 0; i < counts; i++) {
        if (ans[i] != cb[i])
            return false;
//        std::cout << cb[i] << " ";
    }
//    std::cout << std::endl;
    return true;
}

bool test_simple2() {
    size_t counts = 1000;

    buffer<int> cb(1);
    std::vector<int> ans;
    for (size_t i = 0; i < counts; i++) {
        cb.push_back(i);
        ans.push_back(i);
    }
    for (size_t i = 0; i < counts; i++) {
        if (ans[i] != cb[i])
            return false;
//        std::cout << cb[i] << " ";
    }
//    std::cout << std::endl;
    return true;

}

bool test_simple3() {
    size_t counts = 1000;

    buffer<int> cb(1);
    std::vector<int> ans;
    for (size_t i = 0; i < counts; i++) {
        cb.push_back(i);
        ans.push_back(i);
    }
    for (size_t i = 0; i < counts; i++) {
        if (ans[i] != cb.front())
            return false;
        cb.pop_front();
//        std::cout << cb[i] << " ";
    }
//    std::cout << std::endl;
    return true;

}


bool test_simple4() {
    size_t counts = 1000;
    buffer<int> cb(1);
    std::vector<int> ans;
    for (size_t i = 0; i < counts; i++) {
        cb.push_front(i);
        ans.push_back(i);
    }
    for (size_t i = 0; i < counts; i++) {
//        std::cout << cb.back() << " ";
        if (ans[i] != cb.back())
            return false;
        cb.pop_back();
    }
//    std::cout << std::endl;
    return true;
}

bool test_simple5() {
    size_t counts = 1000;
    buffer<int> cb(1);
    std::vector<int> ans;
    for (size_t i = 0; i < counts; i++) {
        cb.push_front(i);
        ans.push_back(i);
    }
    for (size_t i = 0; i < counts; i++) {
        cb.pop_back();
    }
    for (size_t i = 0; i < counts; i++) {
        cb.push_front(i);
        ans.push_back(i);
    }
    for (size_t i = 0; i < counts; i++) {
        cb.pop_back();
    }
    for (size_t i = 0; i < counts; i++) {
        cb.push_front(i);
        ans.push_back(i);
    }
    for (size_t i = 0; i < counts; i++) {
        cb.pop_back();
    }
    if (!cb.empty())
        return false;
//    std::cout << std::endl;
    return true;
}


bool test_simple6() {
    size_t counts = 10;
    buffer<int> cb(1);
    std::vector<int> ans;
    for (size_t i = 0; i < counts; ++i) {
        cb.insert(cb.end(), i);
        ans.push_back(i);
    }
    for (size_t i = 0; i < counts; i++) {
//        std::cout << cb[i] << " ";
        if (ans[i] != cb[i])
            return false;
    }
//    std::cout << std::endl;
    return true;
}

bool test_simple7() {
    size_t counts = 1000;
    buffer<int> cb(1);
    std::vector<int> ans;
    for (size_t i = 0; i < counts; ++i) {
        cb.insert(cb.begin(), i);
        ans.push_back(i);
    }


    reverse(ans.begin(), ans.end());
    for (size_t i = 0; i < counts; i++) {
//        std::cout << cb[i] << " ";
        if (ans[i] != cb[i])
            return false;
    }
//    std::cout << std::endl;
    return true;
}

bool test_simple8() {
    size_t counts = 1000;
    buffer<int> cb(1);
    std::vector<int> ans;
    for (size_t i = 0; i < counts; ++i) {
        if (i % 2 == 0) {
            cb.insert(cb.end(), i);
            ans.push_back(i);
        } else {
            cb.insert(cb.begin(), i);
            ans.insert(ans.begin(), i);
        }
    }

//    for (size_t i = 0; i < counts; ++i) {
//        std::cout << cb[i] << " ";
//    }
//    std::cout << std::endl;
    for (size_t i = 0; i < counts; i++) {
//        std::cout << cb[i] << " ";
        if (ans[i] != cb[i])
            return false;
    }
//    std::cout << std::endl;
    return true;
}


bool test_simple9() {
    size_t counts = 1000;
    buffer<int> cb(1);
    std::vector<int> ans;
    for (size_t i = 0; i < counts; ++i) {
        if (i % 2 == 0) {
            cb.insert(cb.end(), i);
            ans.push_back(i);
        } else {
            cb.insert(cb.begin(), i);
            ans.insert(ans.begin(), i);
        }
    }

    size_t i = 0;
    for (auto t = cb.begin(); t != cb.end(); ++t) {
        if (ans[i++] != *t)
            return false;
    }
//    std::cout << std::endl;
    return true;
}

bool test_simple10() {
    size_t counts = 1000;
    buffer<int> cb(1);
    std::vector<int> ans;
    for (size_t i = 0; i < counts; ++i) {
        cb.insert(cb.end(), i);
        ans.push_back(i);
    }
    size_t i = 0;
    for (auto t = cb.rbegin(); t != cb.rend(); ++t) {
//        std::cout << *t << " ";
        if (ans[counts - i++ - 1] != *t)
            return false;
    }
//    std::cout << std::endl;
    return true;
}

bool test_simple11() {
    size_t counts = 1000;
    buffer<int> cb(1);
    std::vector<int> ans;
    for (size_t i = 0; i < counts; ++i) {
        cb.insert(cb.end(), i);
        ans.push_back(i);
    }
    for (size_t i = 0; i < counts; ++i) {
        cb.erase(cb.begin());
    }
    if (!cb.empty()) return false;

    return true;
}

bool test_simple12() {
    size_t counts = 1000;
    buffer<int> cb(1);
    std::vector<int> ans;
    for (size_t i = 0; i < counts; ++i) {
        cb.insert(cb.end(), i);
        ans.push_back(i);
    }
    for (size_t i = 0; i < counts / 2; ++i) {
        cb.erase(cb.begin());
        ans.erase(ans.begin());
    }
    for (size_t i = 0; i < counts / 2; ++i) {
        if (ans[i] != cb[i])
            return false;
    }

    return true;
}

int main() {
    if (!test_simple1()) {
        throw std::runtime_error("test1 - push_front");
    } else {
        std::cout << "test1 passed" << std::endl;
    }
    if (!test_simple2()) {
        throw std::runtime_error("test2 - push_back");
    } else {
        std::cout << "test2 passed" << std::endl;
    }
    if (!test_simple3()) {
        throw std::runtime_error("test3 - pop_front");
    } else {
        std::cout << "test3 passed" << std::endl;
    }
    if (!test_simple4()) {
        throw std::runtime_error("test4 - pop_ back");
    } else {
        std::cout << "test4 passed" << std::endl;
    }
    if (!test_simple5()) {
        throw std::runtime_error("test5 - push_pop");
    } else {
        std::cout << "test5 passed" << std::endl;
    }

    if (!test_simple6()) {
        throw std::runtime_error("test6 - insert end");
    } else {
        std::cout << "test6 passed" << std::endl;
    }
    if (!test_simple7()) {
        throw std::runtime_error("test7 - insert begin");
    } else {
        std::cout << "test7 passed" << std::endl;
    }
    if (!test_simple8()) {
        throw std::runtime_error("test8 - insert begin -end");
    } else {
        std::cout << "test8 passed" << std::endl;
    }

    if (!test_simple9()) {
        throw std::runtime_error("test9 - iterator test");
    } else {
        std::cout << "test9 passed" << std::endl;
    }
    if (!test_simple10()) {
        throw std::runtime_error("test10 - reverse iterator test");
    } else {
        std::cout << "test10 passed" << std::endl;
    }
    if (!test_simple11()) {
        throw std::runtime_error("test11 - erase test");
    } else {
        std::cout << "test11 passed" << std::endl;
    }
    if (!test_simple12()) {
        throw std::runtime_error("test12 - erase2 test");
    } else {
        std::cout << "test12 passed" << std::endl;
    }

//    buffer<int> cb;
//    buffer<int>::const_iterator it = cb.end();
//    std::cout << (cb.end() == it);
//    std::cout << (cb.begin() == cb.end());
    using container = buffer<int>;
    container c;
    mass_push_back(c, {1, 2, 3, 4});
    container c2(c);
    c[0] = 100;
    std::vector<std::string> temp = {"123","456"};
    for (auto t : temp) std::cout << t;
}