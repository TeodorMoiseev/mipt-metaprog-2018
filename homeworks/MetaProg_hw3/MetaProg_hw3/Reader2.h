//
//  Reader2.h
//  MetaProg_hw3
//
//  Created by Teodor Moiseev on 18/12/2018.
//  Copyright © 2018 Teodor Moiseev. All rights reserved.
//

#ifndef Reader2_h
#define Reader2_h

#include <fstream>
#include "typelist.h"

struct NoDecompressor {};

template <typename TList, typename CompressedTList, typename DecompressorTList>
class Reader2Inner {};

template
<typename Head, typename ...Tail,
typename HeadC, typename ...TailC,
typename ...TailD>
struct Reader2Inner<TypeList<Head, Tail...>, TypeList<HeadC, TailC...>, TypeList<NoDecompressor, TailD...>> {
    static void readNextLine(char* result, std::ifstream& input) {
        HeadC comp_value;
        input >> comp_value;
        Head value = comp_value.decompress();
        *((Head*)result) = value;
        result += sizeof(Head);
        Reader2Inner<TypeList<Tail...>, TypeList<TailC...>, TypeList<TailD...>>::readNextLine(result, input);
    }
};

template
<typename Head, typename ...Tail,
typename ...TailC,
typename HeadD, typename ...TailD>
struct Reader2Inner<TypeList<Head, Tail...>, TypeList<NullType, TailC...>, TypeList<HeadD, TailD...>> {
    static void readNextLine(char* result, std::ifstream& input) {
        std::string comp_value;
        input >> comp_value;
        Head value = HeadD::decompress(comp_value);
        *((Head*)result) = value;
        result += sizeof(Head);
        Reader2Inner<TypeList<Tail...>, TypeList<TailC...>, TypeList<TailD...>>::readNextLine(result, input);
    }
};

template <>
struct Reader2Inner<EmptyList, EmptyList, EmptyList> {
    static void readNextLine(char* result, std::ifstream& input) {}
};

template <typename TList, typename CompressedTList, typename DecompressorTList>
class Reader2 {
public:
    Reader2(std::string filename) : input(filename) {}
    
    ~Reader2() {
        input.close();
    }
    
    void* readNextLine() {
        if (input.eof() or !input.is_open()) {
            return nullptr;
        }
        
        void* result = std::malloc(SizeOf<TList>::value);
        
        Reader2Inner<TList, CompressedTList, DecompressorTList>::readNextLine((char*)result, input);
        
        return result;
    }
private:
    std::ifstream input;
};

#endif /* Reader2_h */
