#include <cs50.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>

string isValidNum(string cardNum);
int main(){
    int i;
    string cardNum, result;
    bool isNumber=false,tooLong=false;
    while(!isNumber&&!tooLong){
        isNumber=true;
        cardNum=get_string("Number: ");
        for(i=0;cardNum[i]!='\0';i++){
            if(cardNum[i]<'0'||cardNum[i]>'9'){// ASCII for numbers is from 48 to 57
                isNumber=false;
                printf("Please enter a valid number (no hyphens, no text)\n");
                break;
            }
            if(i>15)
                tooLong=true;
        }
    }
    if(!tooLong)
        result=isValidNum(cardNum);
    else
        result="INVALID\n";
    printf("%s",result);
}

string isValidNum(string cardNum){
    string result="INVALID\n";
    if(cardNum[0]=='3' && (cardNum[1]=='7'||cardNum[1]=='4') && strlen(cardNum)==15)
        result="AMEX\n";
    else if(cardNum[0]=='4' && (strlen(cardNum)==13||strlen(cardNum)==16))
        result="VISA\n";
    else if(cardNum[0]=='5' &&strlen(cardNum)==16){
        for(char i='1';i<='5';i++){
            if(cardNum[1]==i){
                result="MASTERCARD\n";
                break;
            }
        }
    }
    else return result;

    int checkSum=0; //There is some integer overflow sometimes but that doesn't affect the performance
    for(int i=0;i<strlen(cardNum);i++){
        int num=(int)cardNum[strlen(cardNum)-1-i]-48;
        //printf("%d\n",num);
        if(i%2!=0){
            int prod=num*2;
            if(prod>=10)
                checkSum+=(prod%10) + 1;
            else
                checkSum+=prod;
        }
        else
            checkSum+=num;
    }
    //printf("Checksum: %d\n",checkSum);
    if(checkSum%10==0)
        return result;
    else
        return "INVALID\n";
}
