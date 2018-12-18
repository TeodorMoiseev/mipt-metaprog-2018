//
//  main.cpp
//  MetaProg_hw3
//
//  Created by Teodor Moiseev on 18/12/2018.
//  Copyright © 2018 Teodor Moiseev. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include "typelist.h"
#include "Reader.h"
#include "Reader2.h"
#include "utils.h"

template <typename TList>
void print(char* result) {
    typedef typename TList::Head Type;
    std::cout << *((Type*)result) << " ";
    result += sizeof(Type);
    print<typename TList::Tail>(result);
}

template <>
void print<EmptyList>(char* result) {
    std::cout << std::endl;
}

int main(int argc, const char * argv[]) {
    typedef TypeList<int, double, std::string> TList;
    Reader<TList> reader("input.txt");
    
    void* result = reader.readNextLine();
    while (result != nullptr) {
        print<TList>((char*)result);
        result = reader.readNextLine();
    }
    
    std::free(result);
    
    std::cout << std::endl;
    
    typedef TypeList<int, int, std::string> TList2;
    typedef TypeList<CompressedInt, CompressedInt, NullType> CompressedTList2;
    typedef TypeList<NoDecompressor, NoDecompressor, StringDecompressor> DecompressorTList2;
    Reader2<TList2, CompressedTList2, DecompressorTList2> reader2("input2.txt");
    
    void* result2 = reader2.readNextLine();
    while (result2 != nullptr) {
        print<TList2>((char*)result2);
        result2 = reader2.readNextLine();
    }
    
    std::free(result2);
    
    return 0;
}
