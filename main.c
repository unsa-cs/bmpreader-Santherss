#include "bmp.h"
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

BMPImage *image; 
BMPImage *grayImage;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    if (grayImage) { // Cambio para mostrar la imagen en escala de grises
        drawBMP(grayImage);
    }
    glFlush();
}

int main(int argc, char *argv[]) {
    
    if(argc < 2){
    fprintf(stderr, "Uso: %s <Lenna.bmp>\n",argv[0]);
    return 1;
  }
char *filename = argv[1];//nombre de archivo desde argumento
int grayscale = 0;
    
for(int i = 1; i < argc; i++){
    if(strcmp(argv[i], "gris")==0 || strcmp(argv[i],"grayscale") == 0){
      grayscale = 1; //activar modo blanco y negro
    }
}
image = readBMP(filename);
if (!image) return 1;

if(grayscale){
    grayImage = convertToGray(image);// Convertir la imagen a escala de grises

    freeBMP(image);
    image = grayImage;
}else{
    grayImage = image; //uso de imagen original
}
    

    // Inicializar GLUT
    //int argc = 1; // Necesario para evitar problemas con glutInit
    //char *argv[1] = { "" }; // Argumento vacío para GLUT
glutInit(&argc, argv);

// Establecer el modo de visualización
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize(grayImage->width, grayImage->height); // Usar el tamaño de la imagen en escala de grises
glutCreateWindow("Visualizador de BMP en Escala de Grises");

glLoadIdentity();
glOrtho(0, grayImage->width, grayImage->height, 0, -1, 1);

glutDisplayFunc(display);
glutMainLoop();

freeBMP(grayImage); 
return 0;


}
