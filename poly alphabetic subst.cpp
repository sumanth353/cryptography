#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to perform Vigenere encryption
void vigenereEncrypt(char* plaintext, char* key) {
    int plaintextLen = strlen(plaintext);
    int keyLen = strlen(key);

    for (int i = 0; i < plaintextLen; i++) {
        if (isalpha(plaintext[i])) {
            int keyIndex = i % keyLen;
            char base = isupper(plaintext[i]) ? 'A' : 'a';
            plaintext[i] = ((plaintext[i] - base + key[keyIndex] - 'a') % 26) + base;
        }
    }
}

// Function to perform Vigenere decryption
void vigenereDecrypt(char* ciphertext, char* key) {
    int ciphertextLen = strlen(ciphertext);
    int keyLen = strlen(key);

    for (int i = 0; i < ciphertextLen; i++) {
        if (isalpha(ciphertext[i])) {
            int keyIndex = i % keyLen;
            char base = isupper(ciphertext[i]) ? 'A' : 'a';
            int shift = (ciphertext[i] - base - key[keyIndex] + 'a');
            if (shift < 0) {
                shift += 26;
            }
            ciphertext[i] = shift + base;
        }
    }
}

int main() {
    char plaintext[100];
    char key[100];
    char ciphertext[100];

    printf("Enter the plaintext: ");
    fgets(plaintext, sizeof(plaintext), stdin);

    printf("Enter the Vigenere key: ");
    fgets(key, sizeof(key), stdin);

    // Remove newline characters from input strings
    plaintext[strcspn(plaintext, "\n")] = '\0';
    key[strcspn(key, "\n")] = '\0';

    // Encrypt the plaintext using the Vigenere Cipher
    strcpy(ciphertext, plaintext);
    vigenereEncrypt(ciphertext, key);
    printf("Encrypted text: %s\n", ciphertext);

    // Decrypt the ciphertext using the Vigenere Cipher
    vigenereDecrypt(ciphertext, key);
    printf("Decrypted text: %s\n", ciphertext);

    return 0;
}

