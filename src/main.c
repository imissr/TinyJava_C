#include <stdio.h>
#include "bitset_wrapper.h"

// Declare the C++ functions
typedef struct bitset64 bitset64;

extern bitset64* bitset_create();
extern void bitset_set(bitset64* bs, int pos);
extern void bitset_clear(bitset64* bs, int pos);
extern int bitset_test(bitset64* bs, int pos);
extern void bitset_destroy(bitset64* bs);

int main() {
    bitset64* bs = bitset_create();

    bitset_set(bs, 1);
    bitset_set(bs, 63);

    printf("Bit 1: %d\n", bitset_test(bs, 1));
    printf("Bit 63: %d\n", bitset_test(bs, 63));

    bitset_clear(bs, 1);
    printf("Bit 1 after clear: %d\n", bitset_test(bs, 1));

    bitset_destroy(bs);
    return 0;
}
