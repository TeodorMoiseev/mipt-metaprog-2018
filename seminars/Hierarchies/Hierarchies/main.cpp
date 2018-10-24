//
//  main.cpp
//  Hierarchies
//
//  Created by Teodor Moiseev on 24/10/2018.
//  Copyright © 2018 Teodor Moiseev. All rights reserved.
//

#include <iostream>
#include "TypeList.h"

template <typename T>
struct UnitGSH {
    T& value;
};

template <typename TList, template <typename> class Unit> struct GSH;

// TODO GSH (from class)

template <typename T, class Derive> struct UnitGLH;

template <typename T, class Derive>
struct UnitGLH : public Derive {
    T* value;
};

template <typename TList, template <typename Base, typename Derive> class Unit> struct GLH;

template <typename Head, typename ...Tail, template <typename Base, typename Derive> class Unit>
struct GLH<TypeList<Head, Tail...>, Unit> : public Unit<Head, GLH<TypeList<Tail...>, Unit>> {};


template <template <typename Base, typename Derive> class Unit>
struct GLH<EmptyList, Unit> : public Unit<NullType, NullType> {};


int main(int argc, const char * argv[]) {
    // insert code here...
    GLH<TypeList<int, double>, UnitGLH> hierarchy;
    
    return 0;
}
