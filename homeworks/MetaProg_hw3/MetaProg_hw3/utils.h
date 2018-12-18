//
//  utils.h
//  MetaProg_hw3
//
//  Created by Teodor Moiseev on 18/12/2018.
//  Copyright © 2018 Teodor Moiseev. All rights reserved.
//

#ifndef utils_h
#define utils_h

#include <string>
#include <fstream>

class CompressedInt {
public:
    void set_value(std::string s) {
        comp_value = s;
    }
    
    int decompress() {
        return (int) comp_value.size();
    }
private:
    std::string comp_value;
};

std::istream& operator>> (std::istream& in, CompressedInt& value) {
    std::string s;
    in >> s;
    value.set_value(s);
    
    return in;
}

class StringDecompressor {
public:
    static std::string decompress(std::string comp_value) {
        return comp_value + comp_value + comp_value;
    }
};

#endif /* utils_h */
