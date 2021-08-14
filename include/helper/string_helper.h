//
// Created by Ows on 14/08/2021.
//

#ifndef NES_CLOUD_STRING_HELPER_H
#define NES_CLOUD_STRING_HELPER_H

#include <string>

//COLORING FOR PRINTF
#define RED   "\x1B[31m"
#define GRN   "\x1B[32m"
#define YEL   "\x1B[33m"
#define BLU   "\x1B[34m"
#define MAG   "\x1B[35m"
#define CYN   "\x1B[36m"
#define WHT   "\x1B[37m"
#define RESET "\x1B[0m"

static std::string hex2str(uint32_t n, uint8_t d){
    std::string s(d, '0');
    for(int i = d - 1; i >= 0; i--, n >>= 4){
        s[i] = "0123456789ABCDEF"[n & 0xF];
    }

    return s;
}

#endif //NES_CLOUD_STRING_HELPER_H
