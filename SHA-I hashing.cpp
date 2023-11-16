#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

// Circular left shift macro
#define LEFT_ROTATE(x, n) (((x) << (n)) | ((x) >> (32 - (n))))

// SHA-1 Constants
#define SHA1_BLOCK_SIZE 64
#define SHA1_DIGEST_SIZE 20

// SHA-1 initial hash values
uint32_t H[5] = {0x67452301, 0xEFCDAB89, 0x98BADCFE, 0x10325476, 0xC3D2E1F0};

// Function to perform SHA-1 hashing
void sha1(uint8_t *message, uint32_t message_length, uint32_t *digest) {
    uint32_t padded_length = message_length + 9;
    while (padded_length % SHA1_BLOCK_SIZE != 0)
        padded_length++;

    uint8_t *padded_message = (uint8_t *)malloc(padded_length);
    if (!padded_message) {
        printf("Memory allocation failed.\n");
        return;
    }

    memcpy(padded_message, message, message_length);
    padded_message[message_length] = 0x80;

    uint64_t message_bit_length = message_length * 8;
    for (int i = 0; i < 8; ++i) {
        padded_message[padded_length - 8 + i] = (message_bit_length >> ((7 - i) * 8)) & 0xFF;
    }

    for (int offset = 0; offset < padded_length; offset += SHA1_BLOCK_SIZE) {
        uint32_t words[80];
        memcpy(words, padded_message + offset, SHA1_BLOCK_SIZE);

        for (int i = 16; i < 80; ++i) {
            words[i] = LEFT_ROTATE((words[i - 3] ^ words[i - 8] ^ words[i - 14] ^ words[i - 16]), 1);
        }

        uint32_t a = H[0], b = H[1], c = H[2], d = H[3], e = H[4];

        for (int i = 0; i < 80; ++i) {
            uint32_t f, k;
            if (i < 20) {
                f = (b & c) | ((~b) & d);
                k = 0x5A827999;
            } else if (i < 40) {
                f = b ^ c ^ d;
                k = 0x6ED9EBA1;
            } else if (i < 60) {
                f = (b & c) | (b & d) | (c & d);
                k = 0x8F1BBCDC;
            } else {
                f = b ^ c ^ d;
                k = 0xCA62C1D6;
            }

            uint32_t temp = LEFT_ROTATE(a, 5) + f + e + k + words[i];
            e = d;
            d = c;
            c = LEFT_ROTATE(b, 30);
            b = a;
            a = temp;
        }

        H[0] += a;
        H[1] += b;
        H[2] += c;
        H[3] += d;
        H[4] += e;
    }

    free(padded_message);

    for (int i = 0; i < 5; ++i) {
        digest[i] = H[i];
    }
}

// Function to print SHA-1 digest
void printSHA1Digest(uint32_t *digest) {
    printf("SHA-1 Digest: ");
    for (int i = 0; i < SHA1_DIGEST_SIZE / 4; ++i) {
        printf("%08x", digest[i]);
    }
    printf("\n");
}

int main() {
    char message[] = "Hello, SHA-1!";
    uint32_t digest[SHA1_DIGEST_SIZE / 4];

    sha1((uint8_t *)message, strlen(message), digest);
    printSHA1Digest(digest);

    return 0;
}


