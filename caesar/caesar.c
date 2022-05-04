#include <cs50.h>

#include <stdio.h>

#include <ctype.h>

#include <string.h>

#include <stdlib.h>

int main(int argc, string argv[])
{
    // on the off chance that circular segment doesn't has 2 contention prints mistake
    if (argc != 2)
    {
        printf("Usage: ./caesar key\n");
        return 1;
    }
    else
    {
        // if there are 2 arguments checks if all the second argument contains digits
        string k = argv[1];
        for (int i = 0; i < strlen(k); i++)
        {
            if (isdigit(k[i]) == 0)
            {
                printf("Usage: ./caesar key\n");
                return 1;

            }
        }
        // print orders beneath for testing reason
        // printf("Success\n");
        // printf("%s\n",k);
        // switches second contention over completely to int
        int myKey = atoi(k);

        // asks clients for plaintext to be encoded
        string plaintext = get_string("Plaintext: ");

        // For circle to switch over completely to ciphertext
        for (int i = 0; i < strlen(plaintext); i++)
        {
            if (isupper(plaintext[i]))
            {
                // by given recipe need to change base so that An is 0
                // at the point when you short capital An ASCII esteem by 65 it becomes 0
                plaintext[i] = (plaintext[i] - 65);
                plaintext[i] = (plaintext[i] + myKey) % 26;
                plaintext[i] = (plaintext[i] + 65);

            }
            if (islower(plaintext[i]))
            {
                plaintext[i] = (plaintext[i] - 97);
                plaintext[i] = (plaintext[i] + myKey) % 26;
                plaintext[i] = (plaintext[i] + 97);

            }
            if (isalpha(plaintext[i]) == 0)
            {
                plaintext[i] = plaintext[i];

            }
        }
        printf("Ciphertext: %s", plaintext);
        printf("\n");

    }

}