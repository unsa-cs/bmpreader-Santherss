#include "bmp.h"
#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>

BMPImage *image; 
BMPImage *grayImage;

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    if (grayImage) { // Cambio para mostrar la imagen en escala de grises
        drawBMP(grayImage);
    }
    glFlush();
}

int main() {
    char filename[256];

    // Pedir al usuario el nombre del archivo BMP
    printf("Ingrese el nombre del archivo BMP (con extensión): ");
    scanf("%255s", filename);

    image = readBMP(filename);
    if (!image) return 1;

    // Convertir la imagen a escala de grises
    grayImage = convertToGray(image);
    
    freeBMP(image);

    // Inicializar GLUT
    int argc = 1; // Necesario para evitar problemas con glutInit
    char *argv[1] = { "" }; // Argumento vacío para GLUT
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
