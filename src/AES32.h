/*
 * ESP32 AES Hardware Encryption
 * Enable the use of built-in AES hardware capabilities
 *
 * Author: Fábio Silva
 */

#pragma once

#include <Arduino.h>
#include <hwcrypto/aes.h>

class AES32
{
    public:
        /**
         * \brief          Create AES cipher instance
         */
        AES32();

        /**
         * \brief          Clear AES context
         */
        void free();

        /**
         * \brief          AES set key schedule (encryption or decryption)
         *
         * \param key      encryption key
         * \param keybits  must be 128, 192 or 256
         *
         * \return         0 if successful, or ERR_AES_INVALID_KEY_LENGTH
         */
        int setKey( const unsigned char *key, unsigned int keybits );

        /**
         * \brief          AES-ECB block encryption
         *
         * \param input    16-byte input block
         * \param output   16-byte output block
         *
         * \return         0 if successful
         */
    	int encryptECB( const unsigned char input[16], unsigned char output[16] );

        /**
         * \brief          AES-ECB block decryption
         *
         * \param input    16-byte input block
         * \param output   16-byte output block
         *
         * \return         0 if successful
         */
    	int decryptECB( const unsigned char input[16], unsigned char output[16] );

        /**
         * \brief          AES-CBC buffer encryption
         *                 Length should be a multiple of the block
         *                 size (16 bytes)
         *
         * \note           Upon exit, the content of the IV is updated so that you can
         *                 call the function same function again on the following
         *                 block(s) of data and get the same result as if it was
         *                 encrypted in one call. This allows a "streaming" usage.
         *                 If on the other hand you need to retain the contents of the
         *                 IV, you should either save it manually or use the cipher
         *                 module instead.
         *
         * \param length   length of the input data
         * \param iv       initialization vector (updated after use)
         * \param input    buffer holding the input data
         * \param output   buffer holding the output data
         *
         * \return         0 if successful, or ERR_AES_INVALID_INPUT_LENGTH
         */
        int encryptCBC( size_t length, unsigned char iv[16], const unsigned char *input, unsigned char *output );

        /**
         * \brief          AES-CBC buffer decryption
         *                 Length should be a multiple of the block
         *                 size (16 bytes)
         *
         * \note           Upon exit, the content of the IV is updated so that you can
         *                 call the function same function again on the following
         *                 block(s) of data and get the same result as if it was
         *                 encrypted in one call. This allows a "streaming" usage.
         *                 If on the other hand you need to retain the contents of the
         *                 IV, you should either save it manually or use the cipher
         *                 module instead.
         *
         * \param length   length of the input data
         * \param iv       initialization vector (updated after use)
         * \param input    buffer holding the input data
         * \param output   buffer holding the output data
         *
         * \return         0 if successful, or ERR_AES_INVALID_INPUT_LENGTH
         */
        int decryptCBC( size_t length, unsigned char iv[16], const unsigned char *input, unsigned char *output );

        /**
         * \brief          AES-CFB128 buffer encryption.
         *
         * Note: Due to the nature of CFB you should use the same key schedule for
         * both encryption and decryption. So a context initialized with
         * esp_aes_setkey_enc() for both AES_ENCRYPT and AES_DECRYPT.
         *
         * \note           Upon exit, the content of the IV is updated so that you can
         *                 call the function same function again on the following
         *                 block(s) of data and get the same result as if it was
         *                 encrypted in one call. This allows a "streaming" usage.
         *                 If on the other hand you need to retain the contents of the
         *                 IV, you should either save it manually or use the cipher
         *                 module instead.
         *
         * \param length   length of the input data
         * \param iv_off   offset in IV (updated after use)
         * \param iv       initialization vector (updated after use)
         * \param input    buffer holding the input data
         * \param output   buffer holding the output data
         *
         * \return         0 if successful
         */
        int encryptCFB128( size_t length, size_t *iv_off, unsigned char iv[16], const unsigned char *input, unsigned char *output );

        /**
         * \brief          AES-CFB128 buffer decryption.
         *
         * Note: Due to the nature of CFB you should use the same key schedule for
         * both encryption and decryption. So a context initialized with
         * esp_aes_setkey_enc() for both AES_ENCRYPT and AES_DECRYPT.
         *
         * \note           Upon exit, the content of the IV is updated so that you can
         *                 call the function same function again on the following
         *                 block(s) of data and get the same result as if it was
         *                 encrypted in one call. This allows a "streaming" usage.
         *                 If on the other hand you need to retain the contents of the
         *                 IV, you should either save it manually or use the cipher
         *                 module instead.
         *
         * \param length   length of the input data
         * \param iv_off   offset in IV (updated after use)
         * \param iv       initialization vector (updated after use)
         * \param input    buffer holding the input data
         * \param output   buffer holding the output data
         *
         * \return         0 if successful
         */
        int decryptCFB128( size_t length, size_t *iv_off, unsigned char iv[16], const unsigned char *input, unsigned char *output );

        /**
         * \brief          AES-CFB8 buffer encryption.
         *
         * Note: Due to the nature of CFB you should use the same key schedule for
         * both encryption and decryption. So a context initialized with
         * esp_aes_setkey_enc() for both AES_ENCRYPT and AES_DECRYPT.
         *
         * \note           Upon exit, the content of the IV is updated so that you can
         *                 call the function same function again on the following
         *                 block(s) of data and get the same result as if it was
         *                 encrypted in one call. This allows a "streaming" usage.
         *                 If on the other hand you need to retain the contents of the
         *                 IV, you should either save it manually or use the cipher
         *                 module instead.
         *
         * \param length   length of the input data
         * \param iv       initialization vector (updated after use)
         * \param input    buffer holding the input data
         * \param output   buffer holding the output data
         *
         * \return         0 if successful
         */
        int encryptCFB8( size_t length, unsigned char iv[16], const unsigned char *input, unsigned char *output );
        
        /**
         * \brief          AES-CFB8 buffer decryption.
         *
         * Note: Due to the nature of CFB you should use the same key schedule for
         * both encryption and decryption. So a context initialized with
         * esp_aes_setkey_enc() for both AES_ENCRYPT and AES_DECRYPT.
         *
         * \note           Upon exit, the content of the IV is updated so that you can
         *                 call the function same function again on the following
         *                 block(s) of data and get the same result as if it was
         *                 encrypted in one call. This allows a "streaming" usage.
         *                 If on the other hand you need to retain the contents of the
         *                 IV, you should either save it manually or use the cipher
         *                 module instead.
         *
         * \param length   length of the input data
         * \param iv       initialization vector (updated after use)
         * \param input    buffer holding the input data
         * \param output   buffer holding the output data
         *
         * \return         0 if successful
         */
        int decryptCFB8( size_t length, unsigned char iv[16], const unsigned char *input, unsigned char *output );

        /**
         * \brief               AES-CTR buffer encryption/decryption
         *
         * Warning: You have to keep the maximum use of your counter in mind!
         *
         * Note: Due to the nature of CTR you should use the same key schedule for
         * both encryption and decryption. So a context initialized with
         * esp_aes_setkey_enc() for both AES_ENCRYPT and AES_DECRYPT.
         *
         * \param length        The length of the data
         * \param nc_off        The offset in the current stream_block (for resuming
         *                      within current cipher stream). The offset pointer to
         *                      should be 0 at the start of a stream.
         * \param nonce_counter The 128-bit nonce and counter.
         * \param stream_block  The saved stream-block for resuming. Is overwritten
         *                      by the function.
         * \param input         The input data stream
         * \param output        The output data stream
         *
         * \return         0 if successful
         */
        int cryptCTR( size_t length, size_t *nc_off, unsigned char nonce_counter[16], unsigned char stream_block[16], const unsigned char *input, unsigned char *output );
    private:
        esp_aes_context context;
};
