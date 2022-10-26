#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

int main(void)
{
    string text = get_string("Text: ");
    float sent = 0;
    float spaces = 0;
    float let = 0;
    float numb = 0;

    for(int i = 0; i < strlen(text); i++)
    {
        numb = text[i];
        if((numb > 64 && numb < 91) || (numb > 96 && numb < 123))
        {
            let +=1;
        }
        if(numb == 32)
        {
            spaces +=1;
        }
        if(numb == 63 || numb == 46 || numb == 33)
        {
            sent += 1;
        }
    }
    spaces +=1;
    float index = 0.0588 * ((let / spaces) * 100) - 0.296 * ((sent / spaces)* 100) - 15.8;

    int result = round(index);
    if(index > 15.49)
    {
        printf("Grade 16+\n");
    }
    else if(index > 0.99)
    {
        printf("Grade %i\n", result);
    }
    else
    {
        printf("Before Grade 1\n");
    }
}