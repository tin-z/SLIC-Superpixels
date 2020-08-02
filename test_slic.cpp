/*
 * test_slic.cpp.
 *
 * Written by: Pascal Mettes.
 *
 * This file creates an over-segmentation of a provided image based on the SLIC
 * superpixel algorithm, as implemented in slic.h and slic.cpp.
 */
 
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <stdio.h>
#include <math.h>
#include <vector>
#include <float.h>
using namespace std;

#include "slic.h"

int main(int argc, char *argv[]) {

    if( argc != 5) {
      fprintf(stderr, "Wrong, usage: %s <filename> <K-size> <M-size> <outfilename>\n", argv[0]);
      return -1;
    }

    /* Load the image and convert to Lab colour space. */
    IplImage *image = cvLoadImage(argv[1], 1);
    IplImage *lab_image = cvCloneImage(image);
    cvCvtColor(image, lab_image, CV_BGR2Lab);
    
    /* Yield the number of superpixels and weight-factors from the user. */
    int w = image->width, h = image->height;
    int nr_superpixels = atoi(argv[2]);
    int nc = atoi(argv[3]);

    double step = sqrt((w * h) / (double) nr_superpixels);
    
    /* Perform the SLIC superpixel algorithm. */
    clock_t tStart = clock();
    Slic slic;
    slic.generate_superpixels(lab_image, step, nc);
    slic.create_connectivity(lab_image);
    double time_took = ((double)(clock() - tStart)/CLOCKS_PER_SEC) * 1000;
  
    printf("Time took:%f\n", time_took);

    /* Display the contours and show the result. */
    //slic.display_contours(image, CV_RGB(255,0,0));
    //cvShowImage("result", image);
    //cvWaitKey(0);
    //cvSaveImage(argv[4], image);
}
