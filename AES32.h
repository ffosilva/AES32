/*
 * ESP32 AES Encryption
	 * Enable the use of built-in AES hardware capabilities
 *
 * Author: Fábio Silva
 */

#ifndef AES32_h
#define AES32_h

#include <Arduino.h>
#include <hwcrypto/aes.h>

#if defined ESP32
class AES32
{
    public:
	AES32();
	void free();
	int setKey( const unsigned char *key, unsigned int keybits );
	int encryptCBC( size_t length, unsigned char iv[16], const unsigned char *input, unsigned char *output );
	int encryptCFB128( size_t length, size_t *iv_off, unsigned char iv[16], const unsigned char *input, unsigned char *output );
	int encryptCTR( size_t length, size_t *nc_off, unsigned char nonce_counter[16], unsigned char stream_block[16], const unsigned char *input, unsigned char *output );
    private:
	esp_aes_context context;
};
#endif

#endif
