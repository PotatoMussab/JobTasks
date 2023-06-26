#include <cs50.h>
#include <stdio.h>
#include <math.h>

int count_letters(char* text);
int count_words(char* text);
int count_sentences(char* text);
int main()
{
    printf("Text: ");
    char text[1000];
    scanf("%[^\n]s",text);
    /*printf("%d letters\n",count_letters(text));
    printf("%d words\n",count_words(text));
    printf("%d sentences\n",count_sentences(text));*/
    double L=(double)count_letters(text)/((double)count_words(text))*100;
    double S=(double)count_sentences(text)/((double)count_words(text))*100;
    double dIndex= 0.0588 * L - 0.296 * S - 15.8;
    int index=(int)round(dIndex);
    if(index<1)
        printf("Before Grade 1\n");
    else if(index>=16)
        printf("Grade 16+\n");
    else
        printf("Grade %d\n",index);
}

bool isLetter(char a)
{
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
int count_words(char* text)
{
    int numOfWords=0;
    bool firstWordFound=false;
    for(char* temp=text;*temp!='\0';temp++){
        if(!firstWordFound&&isLetter(*temp)){
            firstWordFound=true;
            numOfWords++;
        }
        else if(*temp==' '&& *(temp-1)!=' ' && *(temp+1)!=' ')
            numOfWords++;
    }
    return numOfWords;
}
int count_sentences(char* text)
{
    int numOfSent=0;
    for(char* temp=text;*temp!='\0';temp++){
        if(*temp=='.'||*temp=='!'||*temp=='?')
            numOfSent++;
    }
    return numOfSent;
}