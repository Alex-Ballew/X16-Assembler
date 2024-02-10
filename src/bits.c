#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include "bits.h"


// Assert that the argument is a bit of either 0 or 1
#define assert_bit(a) if ((a) != 0 && (a) != 1) { assert(false); }


// Get the nth bit
uint16_t getbit(uint16_t number, int n) {
    // TODO: Your code here
    if (number >> n & 0x8000 >> 15){
        return 1;
    } else {
        return 0;
    }
}


// Get bits that are the given number of bits wide
uint16_t getbits(uint16_t number, int n, int wide) {
    // TODO: Your code here
    unsigned int x = 0x0000;
    unsigned int y = 0x0001;
    unsigned int z = 0x0000;


    for (int i = 0; i < wide; i++){
        if (getbit(number, n + i) == 1){
            z |= y << n + i;
        } else {
            z |= x << n + i;
        }
    }


    return z >> n;
}


// Set the nth bit to the given bit value and return the result
uint16_t setbit(uint16_t number, int n) {
    // TODO: Your code here
    unsigned int y = 0x0001 << n;
    return number |= y;
}


// Clear the nth bit
uint16_t clearbit(uint16_t number, int n) {
    // TODO: Your code here
    unsigned int y = 0x0001 << n;
    return number ^ y;
}


// Sign extend a number of the given bits to 16 bits
uint16_t sign_extend(uint16_t x, int bit_count) {
    // TODO: Your code here
    if (getbit(x, bit_count - 1) == 1){
        for (int i = 0; i < 16 - bit_count; i++){
            x |= (0x0001 << bit_count + i);
        }
    }
        return x;
}


bool is_positive(uint16_t number) {
    return getbit(number, 15) == 0;
}


bool is_negative(uint16_t number) {
    return getbit(number, 15) == 1;
}


