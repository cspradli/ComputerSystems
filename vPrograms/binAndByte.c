/*
 * Program to run some conversions and outputs for various homeworks and labs
 * Author: Caleb Spradlin
 * Class: CS 335- Systems II
 * 
 */

#include <stdio.h>
#include <stdlib.h>


int main(int argc, char const *argv[])
{
    unsigned int a = 0xFFFF000cU ;
    printf("1a       a=%u\n", a);
    printf("1b       a=%u\n", a << 2);
    
    int b = 0xFFFF000c;
    printf("2a       b=%u\n", b);
    printf("2b       b=%u\n", b << 15);

    return 0;
}
