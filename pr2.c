/*
Raisa Meneses
Program II
This program processes images
and provides the option to make changes
to the images.
Note: pixels for rotated image and scale up repeat are blue. 
*/


#include <stdio.h> 
#include <string.h>
#include <math.h>
#define HEADER_SIZE 54
#define CONTRAST_RATIO 2.9695
int main () {
 //output files names 
    FILE *outfile1 = fopen("copy1.bmp", "wb");  //brightening
    FILE *outfile2 = fopen("copy2.bmp", "wb");  //contrast
    FILE *outfile3 = fopen("copy3.bmp", "wb");  //rotate 180
    FILE *outfile4 = fopen("copy4.bmp", "wb");  //scale down
    //FILE *outfile5 = fopen("copy5.bmp", "wb"); //scale up - gray scale   


    char header[HEADER_SIZE]; 

    //Will be used to store the file name. 
    char fileName[100];
    char fileExtension[5] = ".bmp";
  
    //file height and width. r and c are use to iterate. 
    int height, width, r, c, r2, c2, bright, contrast, row, column, midPoint;
    double sinma, cosma;
    
    //File that will be modified 
    printf("Enter the filename: "); 
    scanf("%s", fileName);
    strcat(fileName, fileExtension);    
    FILE *infile = fopen(fileName, "rb"); 
    //checking for user input
    if (infile == NULL) {
       printf("Error opening file.. Please try again\n");
     }

    //geting the height and width
    printf("Enter the height and width: ");
    scanf("%d %d", &height, &width); 

    //Variable to hold the width characters
    unsigned char pixels[height][width * 3];
    //array for rotation  
    unsigned char pixelsTemp[height][width * 3]; 
    unsigned char scaleDownTemp[height][width * 3]; 
    unsigned char scaleDownFinal[height][width * 3]; 


    fread( header, 1 , HEADER_SIZE , infile);
    fread( pixels, 1 , height * width * 3 , infile);

   //Brightening:     

    for( r = 0; r < height; r++) {
	for ( c = 0; c < width * 3; c ++) {
         bright = pixels[r][c] + 50;
         if (bright > 255) {
            bright = 255;
          }
         pixels[r][c] = bright;    
        }  	      
    }

    fwrite( header, sizeof(char), HEADER_SIZE  ,  outfile1);
    fwrite( pixels, sizeof(char), height * width * 3,  outfile1);

  //End of brightening

    



//Contrast   
    for(r = 0; r < height; r++) {
       for( c = 0; c < width * 3; c++) {
         contrast = CONTRAST_RATIO * (pixels[r][c]-128) + 128;
         if (contrast > 255) {
	     contrast = 255;
         } if (contrast < 0) {
	     contrast = 0; 
         }
         pixels[r][c] = contrast;
       }
    }
    fwrite( header, sizeof(char), HEADER_SIZE  ,  outfile2);
    fwrite( pixels, sizeof(char), height * width * 3,  outfile2);


//END OF CONTRAST

//180 Rotation   
   
 r2 = height - 1, c2 = width * 3 - 3;

 for(r = 0; r < height; r++) {
	c2 = width * 3 - 1;
       for( c = 0; c < width * 3; c += 3) {
		pixelsTemp[r][c] = pixels[r2][c2];
		pixelsTemp[r][c + 1] = pixels[r2][c2 + 1];
		pixelsTemp[r][c + 2] = pixels[r2][c2 + 2];
		c2 -= 3;
	}
	r2--;
}
 
  fwrite( header, sizeof(char), HEADER_SIZE  ,  outfile3);
  fwrite(pixelsTemp, sizeof(char), height * width * 3,  outfile3);

//End of 180 rotation

  
//Scale down repeat

//Scale down the image
  r2 = 0, c2 = 0;
  for(r = 0; r < height; r++) {
       for( c = 0; c < width * 3; c++){
       scaleDownTemp[r2][c2] = pixels[r][c];
       r2 = r / 2;
       c2 = c / 2;
       scaleDownTemp[r2][c2] = pixels[r2][c2];
      }
    }


//Copy the image 3 more times
   for (r = 0; r < height / 2; r++) {
      for(c = 0; c <  (width * 3) / 2; c++) {
     scaleDownTemp[r][c + (width * 3) / 2] = scaleDownTemp[r][c];
     scaleDownTemp[r + height / 2][c] = scaleDownTemp[r][c];
     scaleDownTemp[r + height / 2][c + (width * 3) / 2] = scaleDownTemp[r][c];
   
    }
  }
 fwrite( header, sizeof(char), HEADER_SIZE  ,  outfile4);
 fwrite(scaleDownTemp, sizeof(char), height * width * 3,  outfile4);




    fclose(infile);
    fclose(outfile1);
    fclose(outfile2);
    fclose(outfile3);
    fclose(outfile4);
    return 0;
}




