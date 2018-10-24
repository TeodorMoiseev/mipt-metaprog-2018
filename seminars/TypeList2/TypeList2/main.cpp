//
//  main.cpp
//  TypeList2
//
//  Created by Teodor Moiseev on 17/10/2018.
//  Copyright © 2018 Teodor Moiseev. All rights reserved.
//

#include <iostream>

struct NullType {};


template <typename ...Args>
struct TypeList {
    using head = NullType;
    using tail = NullType;
};

typedef TypeList<> EmptyList;

template <typename H, typename ...T>
struct TypeList<H, T...> {
    using Head = H;
    using Tail = TypeList<T...>;
};


template <typename TList> struct Length;

template <>
struct Length<EmptyList> {
    static const unsigned value = 0;
};

template <typename H, typename ...T>
struct Length<TypeList<H, T...>> {
    static const unsigned value = 1 + Length<TypeList<T...>>::value;
};

template <typename TList, typename T> struct Add;

template <typename ...Tail, typename T>
struct Add<TypeList<Tail...>, T> {
    using Result = TypeList<T, Tail...>;
};


template <typename TList, typename T> struct EraseFirst;

template <typename T>
struct EraseFirst<EmptyList, T> {
    using Result = EmptyList;
};

template <typename ...Tail, typename T>
struct EraseFirst<TypeList<T, Tail...>, T> {
    using Result = TypeList<Tail...>;
};

template <typename Head, typename ...Tail, typename T>
struct EraseFirst<TypeList<Head, Tail...>, T> {
    using Result = TypeList<Head, EraseFirst<TypeList<Tail...>, T>>;
};


template <typename TList, int i> struct GetAt;

template <int i>
struct GetAt<EmptyList, i> {
    using Result = NullType;
};

template <typename Head, typename ...Tail>
struct GetAt<TypeList<Head, Tail...>, 0> {
    using Result = Head;
};

template <typename Head, typename ...Tail, int i>
struct GetAt<TypeList<Head, Tail...>, i> {
    using Result = typename GetAt<TypeList<Tail...>, i-1>::Result;
};


template <typename TList, typename T, int i> struct GetIndexWithPrefix;

template <typename T, int i>
struct GetIndexWithPrefix<EmptyList, T, i> {
    static const int value = -1;
};

template <typename T, typename ...Tail, int i>
struct GetIndexWithPrefix<TypeList<T, Tail...>, T, i> {
    static const int value = i;
};

template <typename Head, typename ...Tail, typename T, int i>
struct GetIndexWithPrefix<TypeList<Head, Tail...>, T, i> {
    static const int value = GetIndexWithPrefix<TypeList<Tail...>, T, i+1>::value;
};


template <typename TList, typename T>
struct GetIndex {
    static const int value = GetIndexWithPrefix<TList, T, 0>::value;
};


int main(int argc, const char * argv[]) {
    typedef TypeList<int, char, float, int> collection;
    unsigned x = Length<collection>::value;
    std::cout << x << std::endl;
    
    typedef EraseFirst<collection, int>::Result collection2;
    
    x = Length<collection2>::value;
    std::cout << x << std::endl;
    
    typedef Add<collection2, int*>::Result collection3;
    
    x = Length<collection3>::value;
    std::cout << x << std::endl;
    
    typedef GetAt<collection, 2>::Result shouldBeFloat;
    
    shouldBeFloat y = 0.1;
    std::cout << y << std::endl;
    
    int z = GetIndex<collection, float>::value;
    std::cout << z << std::endl;
    
    return 0;
}
