#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Function to prepare the key and generate the Playfair matrix
void prepareKey(char *key, char playfairMatrix[5][5]) {
    int i, j;
    int keyLen = strlen(key);
    int used[26] = {0};

    int row = 0, col = 0;

    for (i = 0; i < keyLen; i++) {
        char ch = toupper(key[i]);
        if (ch == 'J') ch = 'I';

        if (!used[ch - 'A']) {
            playfairMatrix[row][col] = ch;
            used[ch - 'A'] = 1;
            col++;
            if (col == 5) {
                col = 0;
                row++;
            }
        }
    }

    for (i = 0; i < 26; i++) {
        if (i != ('J' - 'A') && !used[i]) {
            playfairMatrix[row][col] = 'A' + i;
            col++;
            if (col == 5) {
                col = 0;
                row++;
            }
        }
    }
}

// Function to find the positions of two characters in the Playfair matrix
void findPositions(char playfairMatrix[5][5], char a, char b, int *rowA, int *colA, int *rowB, int *colB) {
    int i, j;
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            if (playfairMatrix[i][j] == a) {
                *rowA = i;
                *colA = j;
            }
            if (playfairMatrix[i][j] == b) {
                *rowB = i;
                *colB = j;
            }
        }
    }
}

// Function to encrypt a message using the Playfair cipher
void encryptPlayfair(char playfairMatrix[5][5], char *message, char *cipher) {
    int len = strlen(message);
    int i, j;
    int rowA, colA, rowB, colB;
    int index = 0;

    for (i = 0; i < len; i += 2) {
        char a = toupper(message[i]);
        char b = i + 1 < len ? toupper(message[i + 1]) : 'X';

        if (a == 'J') a = 'I';
        if (b == 'J') b = 'I';

        if (a == b) b = 'X';

        findPositions(playfairMatrix, a, b, &rowA, &colA, &rowB, &colB);

        if (rowA == rowB) {
            cipher[index++] = playfairMatrix[rowA][(colA + 1) % 5];
            cipher[index++] = playfairMatrix[rowB][(colB + 1) % 5];
        } else if (colA == colB) {
            cipher[index++] = playfairMatrix[(rowA + 1) % 5][colA];
            cipher[index++] = playfairMatrix[(rowB + 1) % 5][colB];
        } else {
            cipher[index++] = playfairMatrix[rowA][colB];
            cipher[index++] = playfairMatrix[rowB][colA];
        }
    }

    cipher[index] = '\0';
}

int main() {
    char key[50];
    char message[1000];
    char cipher[1000];
    char playfairMatrix[5][5];

    printf("Enter the key: ");
    scanf("%s", key);

    printf("Enter the message: ");
    scanf(" %[^\n]s", message);

    prepareKey(key, playfairMatrix);
    encryptPlayfair(playfairMatrix, message, cipher);

    printf("Encrypted message: %s\n", cipher);

    return 0;
}

