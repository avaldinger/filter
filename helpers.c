#include "helpers.h"
#include <ctype.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE blue;
    BYTE green;
    BYTE red;
    BYTE avg;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            blue = image[i][j].rgbtBlue;
            green = image[i][j].rgbtGreen;
            red = image[i][j].rgbtRed;

            avg = (blue + green + red)/3;

            // printf("Before: %i\n", image[i][j].rgbtBlue);

            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtRed = avg;

            // printf("After: %i\n", image[i][j].rgbtBlue);

            // printf("B: %i G: %i R: %i, avg:%i \n", *blue, *green, *red, avg );



        }
    }

    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    BYTE originalBlue;
    BYTE originalGreen;
    BYTE originalRed;

    BYTE sepiaBlue;
    BYTE sepiaGreen;
    BYTE sepiaRed;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            originalBlue = image[i][j].rgbtBlue;
            originalGreen = image[i][j].rgbtGreen;
            originalRed = image[i][j].rgbtRed;

            if( (round(.393 * originalRed) + round(.769 * originalGreen) + round(.189 * originalBlue)) > 255) {
                sepiaRed = 255;
            } else {
                sepiaRed = round(.393 * originalRed) + round(.769 * originalGreen) + round(.189 * originalBlue);
            }
            if( (round(.349 * originalRed) + round(.686 * originalGreen) + round(.168 * originalBlue)) > 255) {
                sepiaGreen = 255;
             } else {
                sepiaGreen = round(.349 * originalRed) + round(.686 * originalGreen) + round(.168 * originalBlue);
            }
            if( (round(.272 * originalRed) + round(.534 * originalGreen) + round(.131 * originalBlue)) > 255) {
                sepiaBlue = 255;
            } else {
                sepiaBlue = round(.272 * originalRed) + round(.534 * originalGreen) + round(.131 * originalBlue);
            }

            image[i][j].rgbtBlue =sepiaBlue;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtRed = sepiaRed;

        }
    }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{

    RGBTRIPLE reflectedImage[height][width];
    int reverseWidth;

    // adding the reflected pixels to the temp array
    for (int i = 0; i < height; i++) {
        reverseWidth = width;

        for (int j = 0; j < width; j++) {
            reflectedImage[i][reverseWidth-1] = image[i][j];
            if(reverseWidth > 0) {
                reverseWidth--;
            }
        }
    }

    // updating the image[][] with the reflected pixels
    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            image[i][j] = reflectedImage[i][j];
        }
    }



    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int red;
    int blue;
    int green;

    int avgBlue;
    int avgGreen;
    int avgRed;

    // number of elements involved in the computing of the average
    int elements;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {

            // printf("Before: %i\n", image[i][j].rgbtBlue);

            if (i == 0) {
                if (j == 0) {
                    blue = image[i][j].rgbtBlue + image[i][j+1].rgbtBlue +
                        image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue;

                    green = image[i][j].rgbtGreen + image[i][j+1].rgbtGreen +
                        image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen;

                    red = image[i][j].rgbtRed + image[i][j+1].rgbtRed +
                        image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed;

                    elements = 4;

                } else if (j == width-1) {
                    blue = image[i][j-1].rgbtBlue + image[i][j].rgbtBlue +
                        image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue ;

                    green = image[i][j-1].rgbtGreen + image[i][j].rgbtGreen +
                        image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen ;

                    red = image[i][j-1].rgbtRed + image[i][j].rgbtRed +
                        image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed ;

                    elements = 4;

                } else {
                    blue = image[i][j-1].rgbtBlue + image[i][j].rgbtBlue + image[i][j+1].rgbtBlue +
                        image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue;

                    green = image[i][j-1].rgbtGreen + image[i][j].rgbtGreen + image[i][j+1].rgbtGreen +
                        image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen;

                    red = image[i][j-1].rgbtRed + image[i][j].rgbtRed + image[i][j+1].rgbtRed +
                        image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed;

                    elements = 6;
                }
            } else if ( i == height -1) {
                if(j == 0) {
                    blue = image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue +
                        image[i][j].rgbtBlue + image[i][j+1].rgbtBlue;

                    green = image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen +
                        image[i][j].rgbtGreen + image[i][j+1].rgbtGreen;

                    red = image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed +
                        image[i][j].rgbtRed + image[i][j+1].rgbtRed;

                    elements = 4;

                } else if (j == width-1) {
                    blue = image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue +
                        image[i][j-1].rgbtBlue + image[i][j].rgbtBlue ;

                    green = image[i-1][j].rgbtGreen + image[i-1][j].rgbtGreen +
                        image[i][j-1].rgbtGreen + image[i][j].rgbtGreen ;

                    red = image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed +
                        image[i][j-1].rgbtRed + image[i][j].rgbtRed ;

                    elements = 4;

                } else {
                    blue = image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue +
                        image[i][j-1].rgbtBlue + image[i][j].rgbtBlue + image[i][j+1].rgbtBlue;

                    green = image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen +
                        image[i][j-1].rgbtGreen + image[i][j].rgbtGreen + image[i][j+1].rgbtGreen;

                    red = image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed +
                        image[i][j-1].rgbtRed + image[i][j].rgbtRed + image[i][j+1].rgbtRed;

                    elements = 6;

                }

            } else {

                if (j == 0) {
                    blue = image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue +
                        image[i][j].rgbtBlue + image[i][j+1].rgbtBlue +
                        image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue;

                    green = image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen +
                        image[i][j].rgbtGreen + image[i][j+1].rgbtGreen +
                        image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen;

                    red = image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed +
                        image[i][j].rgbtRed + image[i][j+1].rgbtRed +
                        image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed;

                    elements = 6;

                } else if (j == width-1) {
                    blue = image[i][j-1].rgbtBlue + image[i][j].rgbtBlue +
                        image[i][j-1].rgbtBlue + image[i][j].rgbtBlue +
                        image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue;

                    green = image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen +
                        image[i][j-1].rgbtGreen + image[i][j].rgbtGreen +
                        image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen;

                    red = image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed +
                        image[i][j-1].rgbtRed + image[i][j].rgbtRed +
                        image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed;

                    elements = 6;

                } else {
                    // best case here

                     blue = image[i-1][j-1].rgbtBlue + image[i-1][j].rgbtBlue + image[i-1][j+1].rgbtBlue +
                        image[i][j-1].rgbtBlue + image[i][j].rgbtBlue + image[i][j+1].rgbtBlue +
                        image[i+1][j-1].rgbtBlue + image[i+1][j].rgbtBlue + image[i+1][j+1].rgbtBlue;

                    green = image[i-1][j-1].rgbtGreen + image[i-1][j].rgbtGreen + image[i-1][j+1].rgbtGreen +
                        image[i][j-1].rgbtGreen + image[i][j].rgbtGreen + image[i][j+1].rgbtGreen +
                        image[i+1][j-1].rgbtGreen + image[i+1][j].rgbtGreen + image[i+1][j+1].rgbtGreen;

                    red = image[i-1][j-1].rgbtRed + image[i-1][j].rgbtRed + image[i-1][j+1].rgbtRed +
                        image[i][j-1].rgbtRed + image[i][j].rgbtRed + image[i][j+1].rgbtRed +
                        image[i+1][j-1].rgbtRed + image[i+1][j].rgbtRed + image[i+1][j+1].rgbtRed;

                    elements = 9;
                }
            }

            avgBlue = blue/elements;
            avgGreen = green/elements;
            avgRed = red/elements;

            if (avgBlue > 255 ) {
                avgBlue = 255;
            }
            if (avgGreen > 255 ) {
                avgGreen = 255;
            }
            if (avgRed > 255 ) {
                avgRed = 255;
            }

            image[i][j].rgbtBlue = avgBlue;
            image[i][j].rgbtGreen = avgGreen;
            image[i][j].rgbtRed = avgRed;

           //  printf("After: %i\n", image[i][j].rgbtBlue);
         }
    }



    return;
}

