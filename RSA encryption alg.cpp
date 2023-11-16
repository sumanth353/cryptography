#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to calculate the greatest common divisor (GCD) of two numbers
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to check if a number is prime
int is_prime(int num) {
    if (num <= 1)
        return 0;
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0)
            return 0;
    }
    return 1;
}

// Function to find the public key (e) such that 1 < e < phi(n) and GCD(e, phi(n)) = 1
int find_public_key(int phi) {
    int e = 2;
    while (e < phi) {
        if (gcd(e, phi) == 1)
            return e;
        e++;
    }
    return -1; // No public key found
}

// Function to calculate the modular multiplicative inverse
int mod_inverse(int e, int phi) {
    int d;
    for (d = 2; d < phi; d++) {
        if ((e * d) % phi == 1)
            return d;
    }
    return -1; // No modular multiplicative inverse found
}

int main() {
    int p, q, n, phi, e, d;
    printf("Enter two prime numbers (p and q): ");
    scanf("%d %d", &p, &q);

    if (!is_prime(p) || !is_prime(q)) {
        printf("Both numbers must be prime.\n");
        return 1;
    }

    n = p * q;
    phi = (p - 1) * (q - 1);

    e = find_public_key(phi);
    if (e == -1) {
        printf("No public key found.\n");
        return 1;
    }

    d = mod_inverse(e, phi);
    if (d == -1) {
        printf("No modular multiplicative inverse found.\n");
        return 1;
    }

    printf("Public key (e, n): (%d, %d)\n", e, n);
    printf("Private key (d, n): (%d, %d)\n", d, n);

    int plaintext;
    printf("Enter the plaintext message: ");
    scanf("%d", &plaintext);

    int ciphertext = (int)pow(plaintext, e) % n;
    printf("Ciphertext: %d\n", ciphertext);

    int decrypted_message = (int)pow(ciphertext, d) % n;
    printf("Decrypted message: %d\n", decrypted_message);

    return 0;
}


