#include <cs50.h>
#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <string.h>

int main(int argc, string argv[]){
    if(argc!=2){
        printf("Please enter a key as a command line argument\n");
        return 1;
    }
    if(strlen(argv[1])!=26){
        printf("Please enter a key with 26 characters\n");
        return 1;
    }
    string key=argv[1];
    bool valFound[26];
    for(int i=0;i<26;i++){
        int offset;
        if(isalpha(key[i])){
            if(islower(key[i]))
                offset=97; //Offset for lower letters
            else
                offset=65; //Offset for capital letters
            if(valFound[(int)key[i]-offset]){ //Char already found before
                printf("Error: Character repeated twice in key\n");
                return 1;
            }
            else
                valFound[(int)key[i]-offset]=true;
        }
        else{
            printf("Error: Non-alphabetical character in key\n");
            return 1;
        }
    }
    string plain=get_string("plaintext: ");
    char cipher[strlen(plain)+1];
    cipher[strlen(plain)]='\0';
    for(int i=0;i<strlen(plain);i++){
        if(isalpha(plain[i])){
            if(islower(plain[i])){
                int index=(int)plain[i]-97;
                cipher[i]=tolower(key[index]);
            }
            else{
                int index=(int)plain[i]-65;
                cipher[i]=toupper(key[index]);
            }
        }else
            cipher[i]=plain[i];
    }
    printf("ciphertext: %s\n",cipher);
    return 0;
}