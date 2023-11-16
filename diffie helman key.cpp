#include <stdio.h>
#include <math.h>

// Function to calculate (base^exponent)%modulus
int power(int base, int exponent, int modulus) {
    if (exponent == 0)
        return 1;
    int result = 1;
    base = base % modulus;
    while (exponent > 0) {
        if (exponent % 2 == 1)
            result = (result * base) % modulus;
        exponent = exponent >> 1;
        base = (base * base) % modulus;
    }
    return result;
}

int main() {
    int base, modulus; // Publicly shared values
    int private_a, private_b; // Private keys of both parties
    int public_a, public_b; // Public keys generated by both parties
    int secret_key_a, secret_key_b; // Shared secret keys

    printf("Enter the shared base value: ");
    scanf("%d", &base);

    printf("Enter the shared modulus value: ");
    scanf("%d", &modulus);

    printf("Enter private key for party A: ");
    scanf("%d", &private_a);

    printf("Enter private key for party B: ");
    scanf("%d", &private_b);

    // Calculate public keys for both parties
    public_a = power(base, private_a, modulus);
    public_b = power(base, private_b, modulus);

    // Exchange public keys (in a real scenario, this exchange would happen over an insecure channel)
    printf("\nPublic key generated by party A and sent to party B: %d\n", public_a);
    printf("Public key generated by party B and sent to party A: %d\n\n", public_b);

    // Calculate shared secret keys
    secret_key_a = power(public_b, private_a, modulus);
    secret_key_b = power(public_a, private_b, modulus);

    printf("Shared secret key computed by party A: %d\n", secret_key_a);
    printf("Shared secret key computed by party B: %d\n", secret_key_b);

    return 0;
}

