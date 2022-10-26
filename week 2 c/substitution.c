#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, string argv[])
{
    int keyint;
    string key = argv[1];
    if(argv[1] == false || argv[2] != false)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    if(strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }

    for(int i = 0;i < strlen(key);i++)
    {
        keyint = key[i];
        if(keyint < 65 || keyint > 122 || (keyint > 90 && keyint < 97))
        {
            return 1;
        }
    }
    int count = 0;


    for(int i = 0;i < 24;i++)
    {
        for(int j = 0;j < 24;j++)
        {
            if(tolower(key[j]) == tolower(key[i]))
            {
                count += 1;
                if(count > 1)
                {
                    return 1;
                }
            }

            if(count > 1)
            {
                return 1;
            }
        }
        count = 0;
    }
    string text = get_string("plaintext: ");
    int letint;
    char letchar;
    char keychar;

    for(int i = 0;i < strlen(text);i++)
    {
        letint = text[i];
        if(letint < 123 && letint > 96)    //lowercase prvo slovo
        {
            keyint = key[letint - 97];
            if(keyint > 64 && keyint < 91)
            {
                keyint += 32;
                letchar = keyint;
                text[i] = letchar;
            }
            else
            {
                letchar = keyint;
                text[i] = letchar;
            }
        }

        if(letint < 91 && letint > 64)      //uppercase prvo slovo
        {
            keychar = key[letint - 65];
            keyint = keychar;
            if(keyint > 64 && keyint < 91)
            {
                letchar = keyint;
                text[i] = letchar;
            }
            else
            {
                keyint -= 32;
                letchar = keyint;
                text[i] = letchar;
            }
        }
    }
    printf("ciphertext: %s\n", text);

}