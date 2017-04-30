#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <sys/time.h>         
#include "bitmap.h"
#include "plotHis.h"

struct timeval t1, t2;
double elapsedTime;

// packed as [rgb]
char *src_image;

int height_image;
int width_image;
long size_image;
int his[255];
ME_ImageBMP bmp;

void loadBitMap(char *img_name)
{
  meImageBMP_Init(&bmp, img_name);
  src_image = (char*)bmp.imgData;
  height_image = bmp.imgHeight;
  width_image = bmp.imgWidth;
  size_image = height_image * width_image;
}

int main(int argc, char **argv)
{
  if(argc < 2)
  {
    printf("Usage ./HIS <file name>\n");
    return -1;
  }

  loadBitMap(argv[1]);
  for(int i=0; i < 255; i++)
    his[i] = 0;
   
  // start timer
  gettimeofday(&t1, NULL);
  for(int i = 0; i < size_image * 3; i = i+3)
  {
    unsigned char r = src_image[i];
    unsigned char g = src_image[i+1];
    unsigned char b = src_image[i+2];
    unsigned char gray = (r+g+b)/3; 
    
    if(gray < 0) gray = 0;
    if(gray > 255) gray = 255; 
    his[gray]++;
  }
  // stop timer
  gettimeofday(&t2, NULL);
  
  // compute and print the elapsed time in millisec
  elapsedTime = (t2.tv_sec - t1.tv_sec) * 1000.0;      // sec to ms
  elapsedTime += (t2.tv_usec - t1.tv_usec) / 1000.0;   // us to ms
  printf("%f ms.\n", elapsedTime);
  
  plot(his); 
}
