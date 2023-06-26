#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int h=0;
    while(h<1 || h>8){
        h=get_int("Height:");
    }
    int i=1,numOfSpaces=h-i;
    for(i=1;i<=h;i++){
        numOfSpaces=h-i;
        for(int n=0;n<numOfSpaces;n++)
            printf(" ");
        for(int n=0;n<i;n++)
            printf("#");
        printf("  ");
        for(int n=0;n<i;n++)
            printf("#");
        printf("\n");
    }
}