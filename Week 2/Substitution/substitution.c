#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }

    string cipher = argv[1];
    int cipherLength = strlen(cipher);
    if (cipherLength != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    char exist[26] = "";
    for (int i = 0; i < cipherLength; i++)
    {
        exist[toupper(cipher[i]) - 'A']++;
    }

    for (int i = 0; i < cipherLength; i++)
    {
        if (exist[i] != 1)
        {
            printf("Key must not contain repeated characters.\n");
            return 1;
        }
    }

    string text = get_string("plaintext: ");
    printf("ciphertext: ");
    for (int i = 0; text[i] != '\0'; i++)
    {
        char charachter = text[i];
        if (isalpha(charachter))
        {
            if (islower(charachter))
            {
                char cipherChar = cipher[charachter - 97];
                printf("%c", tolower(cipherChar));
            }
            else
            {
                char cipherChar = cipher[charachter - 65];
                printf("%c", toupper(cipherChar));
            }
        }
        else
        {
            printf("%c", charachter);
        }
    }

    printf("\n");
    return 0;
}