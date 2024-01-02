#ifndef _HASH_H_
#define _HASH_H_ 1

#include <stdint.h>
#include <stdlib.h>

/*
 * murmurhash3
 * from github
 */
uint32_t byte_hash_code(const char *key, uint32_t len, uint32_t seed);

/*
 * Thomas Wang's 32 bit Mix Function
 * from redis
 */
uint32_t integer_hash_code(const uint32_t key);

#endif /* _HASH_H_ */