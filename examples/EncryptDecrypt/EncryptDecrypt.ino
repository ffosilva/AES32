/*
 * ESP32 AES Hardware Encryption
 * Enable the use of built-in AES hardware capabilities
 * 
 * AES-CBC usage example
 *
 * Author: Fábio Silva
 */

#include <AES32.h>

#define BLOCK_SIZE 16

// Secret key
uint8_t aes_key[BLOCK_SIZE] = {0x0f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x07, 0x00,
                               0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x09};

// Note: generate a random IV using a cryptographically secure random generator of course
uint8_t aes_iv[BLOCK_SIZE] = {0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                              0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

uint8_t *encrypted, *decrypted;
int encrypted_len, decrypted_len;

char *to_encrypt = "Hello, World!";

AES32 aes32;

void encrypt(uint8_t* data, int data_length, uint8_t** output, int *output_length)
{
  int data_length_padded = data_length % 16 == 0 ? data_length : (data_length - (data_length % 16)) + 16;

  uint8_t* enciphered = (uint8_t*) malloc((BLOCK_SIZE + data_length_padded) * sizeof(uint8_t));
  
  uint8_t* data_to_encrypt = (uint8_t*) calloc(data_length_padded, sizeof(uint8_t));
  memcpy(data_to_encrypt, data, data_length);
  memcpy(&enciphered[0], aes_iv, BLOCK_SIZE);

  size_t offset = 0;
  
  aes32.encryptCBC(data_length_padded, aes_iv, data_to_encrypt, &enciphered[BLOCK_SIZE]);

  *output = enciphered;
  *output_length = (BLOCK_SIZE + data_length_padded);

  free(data_to_encrypt);
}

void decrypt(uint8_t* enciphered, int enciphered_length, uint8_t** output, int *output_length)
{
  uint8_t *deciphered = (uint8_t *) calloc(enciphered_length - BLOCK_SIZE, sizeof(uint8_t)); 
  memcpy(aes_iv, enciphered, BLOCK_SIZE);
  aes32.decryptCBC(enciphered_length - BLOCK_SIZE, aes_iv, &enciphered[BLOCK_SIZE], deciphered);

  *output = deciphered;
  *output_length = enciphered_length - BLOCK_SIZE;
}

void print_key(uint8_t *key, int key_length) {
  for(int i = 0; i < key_length; i++)
  {
    if (key[i] < 16) {
      Serial.print('0');
    }
    
    Serial.print(key[i], HEX);
  }
}

void setup() {
  Serial.begin(115200);
  aes32.setKey(aes_key, 128);
}

void loop() {

  encrypt((uint8_t *) to_encrypt, strlen(to_encrypt), &encrypted, &encrypted_len);

  Serial.println();
  Serial.print("Encrypted message: ");
  print_key(encrypted, encrypted_len);
  Serial.println();
  
  Serial.print("Encrypted length (iv + message + padding): ");
  Serial.println(encrypted_len);

  decrypt(encrypted, encrypted_len, &decrypted, &decrypted_len);

  Serial.print("Decrypted message: ");
  Serial.println((char *) decrypted);
  Serial.print("Decrypted length (message + padding): ");
  Serial.println(decrypted_len);

  free(encrypted);
  free(decrypted);
  
  delay(1000);
}
