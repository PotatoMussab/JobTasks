#include <stdio.h>
#include <stdbool.h>

char* isValidNum(char* cardNum){
    char* result="INVALID\n";
    if(cardNum[0]=='3' && (cardNum[1]=='7'||cardNum[1]=='4'))
        result="AMEX\n";
    else if(cardNum[0]=='4')
        result="VISA\n";
    else if(cardNum[0]=='5'){
        for(char i='1';i<='5';i++){
            if(cardNum[1]==i){
                result="MASTERCARD\n";
                break;
            }
        }
    }
    else return result;

    int checkSum=0; //There is some integer overflow sometimes but that doesn't affect the performance
    for(int i=0;i<16;i++){
        int num=(int)cardNum[i]-48;
        if(i%2==0){
            int prod=num*2;
            if(prod>=10)
                checkSum+=prod%10 + 1;
            else
                checkSum+=prod;
        }
        else
            checkSum+=num;
    }
    if(checkSum%10==0)
        return result;
    else
        return "INVALID\n";
}

int main(){
    int i;
    char cardNum[50];
    char* result;
    bool isNumber=false,tooLong=false;
    while(!isNumber&&!tooLong){
        isNumber=true;
        printf("Card Number: ");
        scanf("%s",cardNum);
        for(i=0;cardNum[i]!='\0';i++){
            if(cardNum[i]<'0'||cardNum[i]>'9'){// ASCII for numbers is from 48 to 57
                isNumber=false;
                printf("Please enter a valid number (no hyphens, no text)\n");
                break;
            }
            if(i>15){ //Checking the length of the string in this loop is more efficient than looping again (two birds one stone)
                tooLong=true;
                break;
            }
        }
    }
    if(tooLong||i<15)
        result="INVALID\n";
    else
        result=isValidNum(cardNum);
    printf(result);
}