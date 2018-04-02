/*
 * ESP32 AES Hardware Encryption
 * Enable the use of built-in AES hardware capabilities
 *
 * Author: Fábio Silva
 */

#include <AES32.h>

AES32::AES32() {
    esp_aes_init(&this->context);
}

void AES32::free() {
    esp_aes_free(&this->context);
}

int AES32::setKey( const unsigned char *key, unsigned int keybits ) {
    return esp_aes_setkey(&this->context, key, keybits);
}

int AES32::encryptECB( const unsigned char input[16], unsigned char output[16] ) {
    return esp_aes_crypt_ecb (&this->context, ESP_AES_ENCRYPT, input, output);
}

int AES32::decryptECB( const unsigned char input[16], unsigned char output[16] ) {
    return esp_aes_crypt_ecb (&this->context, ESP_AES_DECRYPT, input, output);
}

int AES32::encryptCBC( size_t length, unsigned char iv[16], const unsigned char *input, unsigned char *output ) {
    return esp_aes_crypt_cbc(&this->context, ESP_AES_ENCRYPT, length, iv, input, output);
}

int AES32::decryptCBC( size_t length, unsigned char iv[16], const unsigned char *input, unsigned char *output ) {
    return esp_aes_crypt_cbc(&this->context, ESP_AES_DECRYPT, length, iv, input, output);
}

int AES32::encryptCFB128( size_t length, size_t *iv_off, unsigned char iv[16], const unsigned char *input, unsigned char *output ) {
    return esp_aes_crypt_cfb128(&this->context, ESP_AES_ENCRYPT, length, iv_off, iv, input, output);
}

int AES32::decryptCFB128( size_t length, size_t *iv_off, unsigned char iv[16], const unsigned char *input, unsigned char *output ) {
    return esp_aes_crypt_cfb128(&this->context, ESP_AES_DECRYPT, length, iv_off, iv, input, output);
}

int AES32::encryptCFB8( size_t length, unsigned char iv[16], const unsigned char *input, unsigned char *output ) {
    return esp_aes_crypt_cfb8(&this->context, ESP_AES_ENCRYPT, length, iv, input, output);
}

int AES32::decryptCFB8( size_t length, unsigned char iv[16], const unsigned char *input, unsigned char *output ) {
    return esp_aes_crypt_cfb8(&this->context, ESP_AES_DECRYPT, length, iv, input, output);
}

int AES32::cryptCTR( size_t length, size_t *nc_off, unsigned char nonce_counter[16], unsigned char stream_block[16], const unsigned char *input, unsigned char *output ) {
    return esp_aes_crypt_ctr(&this->context, length, nc_off, nonce_counter, stream_block, input, output);
}