#include <openssl/sha.h>
#include <stdio.h>
#include <stdint.h>
#include <byteswap.h>

char *trip(char *input, size_t len) {
	static const char b64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz0123456789+/";
	static char trip[11];
	static uint64_t hash[SHA512_DIGEST_LENGTH/sizeof(uint64_t)];
	static SHA512_CTX c;
	SHA512_Init(&c);
	SHA512_Update(&c, input, len);
	SHA512_Final((unsigned char *)hash, &c);
#ifdef _CPU_BIG_ENDIAN
	uint64_t hash64 = *hash;
#else
	uint64_t hash64 = bswap_64(*hash);
#endif
	int i;
	for(i=0;i<10;i++)
		trip[i]=b64[hash64>>(58-i*6) & 63];
	trip[10]=0;
	return trip;
}

// Identical to `trip`, except outputs in all lowercase
char *trip_lower(char *input, size_t len) {
	static const char b64[] = "abcdefghijklmnopqrstuvwxyz"
		"abcdefghijklmnopqrstuvwxyz0123456789+/";
	static char trip[11];
	static uint64_t hash[SHA512_DIGEST_LENGTH/sizeof(uint64_t)];
	static SHA512_CTX c;
	SHA512_Init(&c);
	SHA512_Update(&c, input, len);
	SHA512_Final((unsigned char *)hash, &c);
#ifdef _CPU_BIG_ENDIAN
	uint64_t hash64 = *hash;
#else
	uint64_t hash64 = bswap_64(*hash);
#endif
	int i;
	for(i=0;i<10;i++)
		trip[i]=b64[hash64>>(58-i*6) & 63];
	trip[10]=0;
	return trip;
}
