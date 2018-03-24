#include <AES32.h>

/*
 * ESP32 AES Encryption
	 * Enable the use of built-in AES hardware capabilities
 *
 * Author: Fábio Silva
 */

#if defined ESP32

AES32::AES32() {
    esp_aes_init(&this->context);
}

void AES32::free() {
    esp_aes_free(&this->context);
}

int AES32::setKey( const unsigned char *key, unsigned int keybits ) {
    return esp_aes_setkey(&this->context, key, keybits);
}

int AES32::encryptCBC( size_t length, unsigned char iv[16], const unsigned char *input, unsigned char *output ) {
    return esp_aes_crypt_cbc(&this->context, ESP_AES_ENCRYPT, length, iv, input, output);
}

int AES32::encryptCFB128( size_t length, size_t *iv_off, unsigned char iv[16], const unsigned char *input, unsigned char *output ) {
    return esp_aes_crypt_cfb128(&this->context, ESP_AES_ENCRYPT, length, iv_off, iv, input, output);
}

#endif
