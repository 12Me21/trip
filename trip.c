#include <openssl/sha.h>

char *trip(char *input, size_t len) {
	static const char b64[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
		"abcdefghijklmnopqrstuvwxyz0123456789+/";
	static char trip[11];
	static unsigned char hash[SHA512_DIGEST_LENGTH];
	
	SHA512((unsigned char *)input, len, hash);
	// get first 10 chars of base64
	trip[0]=b64[                  hash[0]>>2];
	trip[1]=b64[(hash[0]& 3)<<4 | hash[1]>>4];
	trip[2]=b64[(hash[1]&15)<<2 | hash[2]>>6];
	trip[3]=b64[ hash[2]&63                 ];
	trip[4]=b64[                  hash[3]>>2];
	trip[5]=b64[(hash[3]& 3)<<4 | hash[4]>>4];
	trip[6]=b64[(hash[4]&15)<<2 | hash[5]>>6];
	trip[7]=b64[ hash[5]&63                 ];
	trip[8]=b64[                  hash[6]>>2];
	trip[9]=b64[(hash[6]& 3)<<4 | hash[7]>>4];
	trip[10]=0;
	
	return trip;
}
