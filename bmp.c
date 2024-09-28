#include "bmp.h"
#include <GL/glut.h>

extern BMPImage *grayImage; 

BMPImage* readBMP(const char *filename) {
  BMPImage *image = malloc(sizeof(BMPImage));
  FILE *file = fopen(filename, "rb");

  if (!file) {
    fprintf(stderr, "No se puede abrir el archivo %s\n", filename);
    free(image);
    return NULL;
  }

  fread(image->header, sizeof(unsigned char), 54, file);
  image->width = *(int*)&image->header[18];
  image->height = *(int*)&image->header[22];

  image->data = malloc(image->width * image->height * 3); // 3 bytes por píxel
  fread(image->data, sizeof(unsigned char), image->width * image->height * 3, file);
  fclose(file);

  return image;
}

void freeBMP(BMPImage *image) {
  free(image->data);
  free(image);
}

BMPImage* convertToGray(BMPImage *original){
  BMPImage *grayImage = malloc(sizeof(BMPImage));
  grayImage->width = original->width;
  grayImage->height = original->height;
  grayImage->data = malloc(grayImage->width * grayImage->height * sizeof(unsigned char));
   
  //para obtener los valores de color considerando el formato RGB
  for(int i = 0; i < original->height; i++){
    for (int j = 0; j < original->width; j++){

      unsigned char b = original->data[(i * original->width + j)* 3 + 0];
      unsigned char g = original->data[(i * original->width + j)* 3 + 1];
      unsigned char r = original->data[(i * original->width + j)* 3 + 2];



      //conversion a Gris 
      unsigned char gray = (unsigned char)(r * 0.3 + g * 0.59 + b * 0.11);
      grayImage->data[i * grayImage->width + j] = gray;

    }

  }
  return grayImage;
}


void drawBMP(BMPImage *image) {
  if(image != NULL && image->data != NULL){
    if(image->height > 0 && image->width > 0){
      if (image == grayImage) {//si la imagen esta en gris
          glDrawPixels(image->width, image->height, GL_LUMINANCE, GL_UNSIGNED_BYTE, image->data);

      }else{//si la imagen es a color
        glDrawPixels(image->width,image->height,GL_RGB,GL_UNSIGNED_BYTE,image->data);
      
      }
    }
  }
}
