#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        printf("Invalid number of command line arguments");
        return 1;
    }
    FILE *rawFile=fopen(argv[1],"r");
    if(rawFile==NULL)
    {
        printf("Could not open file");
        return 1;
    }
    BYTE* FAT=malloc(512);
    int fileNum=0;
    char outFileName[8]="000.jpg";
    FILE* outFile=fopen(outFileName,"w");
    while(fread(FAT,1,512,rawFile)==512)
    {
        if(FAT[0]==0xff && FAT[1]==0xd8 && FAT[2]==0xff && FAT[3]>=0xe0 && FAT[3]<=0xef)
        {
            fclose(outFile);
            sprintf(outFileName,"%03d.jpg",fileNum);
            outFile=fopen(outFileName,"w");
            fileNum++;
        }
        fwrite(FAT,sizeof(BYTE),512,outFile);
    }
    fclose(outFile);
    fclose(rawFile);
    free(FAT);
    return 0;

}