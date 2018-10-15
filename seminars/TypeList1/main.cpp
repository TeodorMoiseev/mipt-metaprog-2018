#include <iostream>

class NullType {};

template <class U, class V>
struct TypeList {
    typedef U head;
    typedef V tail;
};

template <class TList> struct Length;

template <>
struct Length<NullType> {
    static const unsigned value = 0;
};

template <class U, class V>
struct Length<TypeList<U, V>> {
    static const unsigned value = 1 + Length<V>::value;
};

int main() {
    typedef TypeList<char, TypeList<int, TypeList<double, TypeList<int, NullType>>>> collection;
    unsigned x = Length<collection>::value;
    std::cout << x << std::endl;

    return 0;
}