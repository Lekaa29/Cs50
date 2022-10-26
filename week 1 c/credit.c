#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    long number;
    number = get_long("Number: ");
    long sumx = 0;
    long sum = 0;
    long x = 0;
    long test;
    string type;
    if(number > 999999999999 && number < 10000000000000) //12-14
    {
        test = number /100000000000; //11
    }
    if(number > 99999999999999 && number < 1000000000000000) //14-16
    {
        test = number /10000000000000; //13
    }
    if(number > 999999999999999 && number < 10000000000000000) //15-17
    {
        test = number /100000000000000;
    }
    if(test == 34 || test == 37)
    {
        type = "AMEX\n";
    }
    else if(test == 51 || test == 52 || test == 53 || test == 54 || test == 55)
    {
        type = "MASTERCARD\n";
    }
    else if((test /10) == 4)
    {
        type = "VISA\n";
    }
    else
    {
        type = "INVALID\n";
    }
    if(strcmp(type,"INVALID") != 0)
    {
            while(number > 9)
        {
        x = number % 10;
        sum = sum + x;

        number = number / 10;

        x = number % 10;
        if((x*2) < 10)
        {
            sumx = sumx + (x*2);
        }
        else
        {
            x = (x*2)%10;
            sumx = sumx + 1 + x;
        }
        number = number / 10;
        }
    }
    sum = sum + number;
    if(((sumx+sum)%10)==0)
    {
        printf("%s", type);
    }
    else
    {
        printf("INVALID\n");
    }
}