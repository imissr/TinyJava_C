#include <bitset>
#include "bitset_wrapper.h"

struct bitset64 {
    std::bitset<64> bits;
};

extern "C" {

bitset64* bitset_create() {
    return new bitset64();
}

void bitset_set(bitset64* bs, int pos) {
    bs->bits.set(pos);
}

void bitset_clear(bitset64* bs, int pos) {
    bs->bits.reset(pos);
}

int bitset_test(bitset64* bs, int pos) {
    return bs->bits.test(pos);
}

void bitset_destroy(bitset64* bs) {
    delete bs;
}

}
