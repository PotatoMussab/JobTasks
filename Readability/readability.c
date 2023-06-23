#include <stdio.h>
#include <stdbool.h>
#include <string.h>

int count_letters(char* text);
int count_words(char* text);
int count_sentences(char* text);
int round(float x);

int main(){
    printf("Text: ");
    char text[1000];
    scanf("%[^\n]s",text);
    /*printf("%d letters\n",count_letters(text));
    printf("%d words\n",count_words(text));
    printf("%d sentences\n",count_sentences(text));*/
    float L=(float)count_letters(text)/((float)count_words(text))*100;
    float S=(float)count_sentences(text)/((float)count_words(text))*100;
    float fIndex= 0.0588 * L - 0.296 * S - 15.8;
    printf("Grade: %d",round(fIndex));
}

int round(float x){
    float y= (float)((int)x);
    if(x-y<0.5)
        return (int) x;
    else
        return (int)x+1;
}
bool isLetter(char a){
    return (a<='z'&& a>='a') || (a<='Z'&&a>='A');
}
int count_letters(char* text){
    int len=0;
    for(char* temp=text;*temp!='\0';temp++){
        if(isLetter(*temp))
            len++;
    }
    return len;
}
int count_words(char* text){
    int numOfWords=0;
    bool firstWordFound=false;
    for(char* temp=text;*temp!='\0';temp++){
        if(!firstWordFound&&isLetter(*temp)){
            firstWordFound=true;
            numOfWords++;
        }
        else if(*temp==' '&& *(temp-1)!=' ' && isLetter(*(temp+1)))
            numOfWords++;
    }
    return numOfWords;
}
int count_sentences(char* text){
    int numOfSent=0;
    for(char* temp=text;*temp!='\0';temp++){
        if(*temp=='.'||*temp=='!'||*temp=='?')
            numOfSent++;
    }
    return numOfSent;
}