#include "helpers.h"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>

void setRGB(BYTE red, BYTE green, BYTE blue, RGBTRIPLE* pixel)
{
    (*pixel).rgbtRed=red;
    (*pixel).rgbtGreen=green;
    (*pixel).rgbtBlue=blue;
}
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int y=0;y<height;y++)
    {
        for(int x=0;x<width;x++)
        {
            double r=(double)image[y][x].rgbtRed;
            double g=(double)image[y][x].rgbtGreen;
            double b=(double)image[y][x].rgbtBlue;
            double gr=(r+g+b)/3;
            BYTE grey=(BYTE)round(gr);
            image[y][x].rgbtRed=grey;
            image[y][x].rgbtBlue=grey;
            image[y][x].rgbtGreen=grey;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for(int y=0;y<height;y++)
    {
        for(int x=0, center=width/2; x<center; x++)
        {
            RGBTRIPLE tempPixel=image[y][x];
            image[y][x]=image[y][width-x-1];
            image[y][width-x-1]=tempPixel;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE newImg[height][width];
    for(int y=0;y<height;y++)
    {
        for(int x=0;x<width;x++)
        {
            int startX=x-1;
            int startY=y-1;
            int endX=x+1;
            int endY=y+1;
            if(x==0)
                startX=0;
            if(y==0)
                startY=0;
            if(y==height-1)
                endY=height-1;
            if(x==width-1)
                endX=width-1;

            double rAvg=0.0,gAvg=0.0,bAvg=0.0;
            double den=(endX-startX+1)*(endY-startY+1);
            for(int row=startX; row<=endX; row++)
            {
                for(int col=startY; col<=endY; col++)
                {
                    rAvg+=(double)image[col][row].rgbtRed;
                    gAvg+=(double)image[col][row].rgbtGreen;
                    bAvg+=(double)image[col][row].rgbtBlue;
                }
            }
            rAvg/=den;
            gAvg/=den;
            bAvg/=den;
            BYTE r=(BYTE)round(rAvg);
            BYTE g=(BYTE)round(gAvg);
            BYTE b=(BYTE)round(bAvg);
            setRGB(r,g,b,&newImg[y][x]);
        }
    }
    for(int x=0;x<width;x++)
    {
        for(int y=0;y<height;y++)
        {
            image[y][x]=newImg[y][x];
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE newImg[height][width];
    for(int y=0;y<height;y++)
    {
        for(int x=0;x<width;x++)
        {
            int Gx[3]={0,0,0};
            int Gy[3]={0,0,0};
            int Gtot[3]={0,0,0};
            bool atLeft = x==0;
            bool atRight = x==width-1;
            bool atTop = y==0;
            bool atBottom = y==height-1;
            if(!atTop)
            {
                if(!atLeft) //Add top left pixel image[x-1][y-1]
                {
                    Gx[0]-= image[y-1][x-1].rgbtRed;
                    Gy[0]-= image[y-1][x-1].rgbtRed;

                    Gx[1]-= image[y-1][x-1].rgbtGreen;
                    Gy[1]-= image[y-1][x-1].rgbtGreen;

                    Gx[2]-= image[y-1][x-1].rgbtBlue;
                    Gy[2]-= image[y-1][x-1].rgbtBlue;
                }
                 //Add top pixel image[y-1][x]
                Gy[0]-= 2*image[y-1][x].rgbtRed;
                Gy[1]-= 2*image[y-1][x].rgbtGreen;
                Gy[2]-= 2*image[y-1][x].rgbtBlue;

                if(!atRight) //Add top right pixel: image[y-1][x+1]
                {
                    Gx[0]+= image[y-1][x+1].rgbtRed;
                    Gy[0]-= image[y-1][x+1].rgbtRed;

                    Gx[1]+= image[y-1][x+1].rgbtGreen;
                    Gy[1]-= image[y-1][x+1].rgbtGreen;

                    Gx[2]+= image[y-1][x+1].rgbtBlue;
                    Gy[2]-= image[y-1][x+1].rgbtBlue;
                }

            }
            if(!atLeft) //Add left pixel: image[y][x-1]
            {
                Gx[0]-= 2*image[y][x-1].rgbtRed;
                Gx[1]-= 2*image[y][x-1].rgbtGreen;
                Gx[2]-= 2*image[y][x-1].rgbtBlue;
            }
            if(!atRight) //Add right pixel: image[y][x+1]
            {
                Gx[0]+= 2*image[y][x+1].rgbtRed;
                Gx[1]+= 2*image[y][x+1].rgbtGreen;
                Gx[2]+= 2*image[y][x+1].rgbtBlue;
            }
            if(!atBottom)
            {
                if(!atLeft)//Add bottom left pixel: image[y+1][x-1]
                {
                    Gx[0]-= image[y+1][x-1].rgbtRed;
                    Gy[0]+= image[y+1][x-1].rgbtRed;

                    Gx[1]-= image[y+1][x-1].rgbtGreen;
                    Gy[1]+= image[y+1][x-1].rgbtGreen;

                    Gx[2]-= image[y+1][x-1].rgbtBlue;
                    Gy[2]+= image[y+1][x-1].rgbtBlue;
                }

                Gy[0]+= 2*image[y+1][x].rgbtRed; //Add bottom pixel: image[y+1][x]
                Gy[1]+= 2*image[y+1][x].rgbtGreen;
                Gy[2]+= 2*image[y+1][x].rgbtBlue;

                if(!atRight)//Add bottom right pixel: image[y+1][x+1]
                {
                    Gx[0]+= image[y+1][x+1].rgbtRed;
                    Gy[0]+= image[y+1][x+1].rgbtRed;

                    Gx[1]+= image[y+1][x+1].rgbtGreen;
                    Gy[1]+= image[y+1][x+1].rgbtGreen;

                    Gx[2]+= image[y+1][x+1].rgbtBlue;
                    Gy[2]+= image[y+1][x+1].rgbtBlue;
                }
            }
            for(int i=0;i<3;i++)
            {
                Gtot[i]=round(sqrt(Gx[i]*Gx[i]+Gy[i]*Gy[i]));
                if(Gtot[i]>255)
                Gtot[i]=255;
            }
            setRGB((BYTE)Gtot[0],(BYTE)Gtot[1],(BYTE)Gtot[2],&newImg[y][x]);

        }
    }
    for(int x=0;x<width;x++)
    {
        for(int y=0;y<height;y++)
        {
            image[y][x]=newImg[y][x];
        }
    }
    return;
}
