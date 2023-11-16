#include <stdio.h>
#include <string.h>

// Function to encrypt a message using the Rail Fence Transposition
void encryptRailFence(char* plaintext, int rails) {
    int len = strlen(plaintext);
    char fence[rails][len];
    int row = 0, col = 0;
    int direction = 1; // Direction: 1 for down, -1 for up

    for (int i = 0; i < len; i++) {
        if (row == 0) {
            direction = 1;
        } else if (row == rails - 1) {
            direction = -1;
        }
        
        fence[row][col] = plaintext[i];
        row += direction;
        col++;
    }

    // Print the encrypted message
    for (int i = 0; i < rails; i++) {
        for (int j = 0; j < len; j++) {
            if (fence[i][j] != 0) {
                printf("%c", fence[i][j]);
            } else {
                printf(" ");
            }
        }
    }
    printf("\n");
}

// Function to decrypt a message encrypted with Rail Fence Transposition
void decryptRailFence(char* ciphertext, int rails) {
    int len = strlen(ciphertext);
    char fence[rails][len];
    int row = 0, col = 0;
    int direction = 1;

    for (int i = 0; i < len; i++) {
        if (row == 0) {
            direction = 1;
        } else if (row == rails - 1) {
            direction = -1;
        }
        
        fence[row][col] = '*'; // Use '*' to mark positions
        row += direction;
        col++;
    }

    int index = 0;

    // Fill the fence with characters from the ciphertext
    for (int i = 0; i < rails; i++) {
        for (int j = 0; j < len; j++) {
            if (fence[i][j] == '*' && index < len) {
                fence[i][j] = ciphertext[index];
                index++;
            }
        }
    }

    // Decrypt and print the message
    row = 0;
    col = 0;
    direction = 1;

    for (int i = 0; i < len; i++) {
        if (row == 0) {
            direction = 1;
        } else if (row == rails - 1) {
            direction = -1;
        }

        printf("%c", fence[row][col]);
        row += direction;
        col++;
    }
    printf("\n");
}

int main() {
    char message[100];
    int rails;

    printf("Enter the message to encrypt: ");
    fgets(message, sizeof(message), stdin);

    printf("Enter the number of rails: ");
    scanf("%d", &rails);

    // Remove newline characters from input string
    message[strcspn(message, "\n")] = '\0';

    printf("Encrypted message: ");
    encryptRailFence(message, rails);

    printf("Enter the message to decrypt: ");
    fflush(stdin); // Clear input buffer
    fgets(message, sizeof(message), stdin);

    // Remove newline characters from input string
    message[strcspn(message, "\n")] = '\0';

    printf("Decrypted message: ");
    decryptRailFence(message, rails);

    return 0;
}

