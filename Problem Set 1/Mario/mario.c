#include <stdio.h>

int main(){
    int h=0;
    while(h<1 || h>8){
        printf("Height: ");
        scanf("%d",&h);
    }
    int i=1,numOfSpaces=h-i;
    for(i=1;i<=h;i++){
        numOfSpaces=h-i;
        for(int n=0;n<numOfSpaces;n++)
            printf(" ");
        for(int n=0;n<i;n++)
            printf("#");
        printf(" ");
        for(int n=0;n<i;n++)
            printf("#");
        printf("\n");
    }
}