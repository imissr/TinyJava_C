#ifndef BITSET_WRAPPER_H
#define BITSET_WRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct bitset64 bitset64;

bitset64* bitset_create();
void bitset_set(bitset64* bs, int pos);
void bitset_clear(bitset64* bs, int pos);
int bitset_test(bitset64* bs, int pos);
void bitset_destroy(bitset64* bs);

#ifdef __cplusplus
}
#endif

#endif // BITSET_WRAPPER_H
