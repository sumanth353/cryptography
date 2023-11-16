#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to perform the monoalphabetic substitution
void monoalphabeticSubstitution(char plainText[], char key[]) {
    int i;
    int length = strlen(plainText);

    for (i = 0; i < length; i++) {
        if (isalpha(plainText[i])) {
            char current = tolower(plainText[i]);

            // If the character is an alphabet
            if (isalpha(current)) {
                int index = current - 'a';
                if (isupper(plainText[i])) {
                    plainText[i] = toupper(key[index]);
                } else {
                    plainText[i] = key[index];
                }
            }
        }
    }
}

int main() {
    char plainAlphabet[] = "abcdefghijklmnopqrstuvwxyz";
    char cipherAlphabet[] = "xpmutwqadczfnjgblhrovkesiy";

    char plainText[100];

    printf("Enter the plaintext: ");
    fgets(plainText, sizeof(plainText), stdin);

    // Call the function for substitution
    monoalphabeticSubstitution(plainText, cipherAlphabet);

    printf("Ciphertext: %s\n", plainText);

    return 0;
}

