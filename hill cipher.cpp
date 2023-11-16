#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Function to encrypt the message using Hill cipher
void encrypt(char *message, int keyMatrix[3][3]) {
    int len = strlen(message);
    int encrypted[len];

    for (int i = 0; i < len; i += 3) {
        for (int j = 0; j < 3; j++) {
            encrypted[i + j] = 0;
            for (int k = 0; k < 3; k++) {
                encrypted[i + j] += (message[i + k] - 'A') * keyMatrix[j][k];
            }
            encrypted[i + j] %= 26;
        }
    }

    printf("Encrypted message: ");
    for (int i = 0; i < len; i++) {
        printf("%c", encrypted[i] + 'A');
    }
    printf("\n");
}

int main() {
    char message[100];
    int keyMatrix[3][3];

    printf("Enter the message to encrypt (in uppercase letters): ");
    scanf("%s", message);

    printf("Enter the 3x3 key matrix:\n");
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            scanf("%d", &keyMatrix[i][j]);
        }
    }

    encrypt(message, keyMatrix);

    return 0;
}

