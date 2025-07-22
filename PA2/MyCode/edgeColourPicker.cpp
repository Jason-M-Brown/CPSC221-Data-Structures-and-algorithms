/**
 * @file edgeColourPicker.cpp
 * @description Implements the EdgeColourPicker constructor and () function
 *              for CPSC 221 PA2
 *
 *              THIS FILE WILL BE SUBMITTED
 */

#include "edgeColourPicker.h"

/**
 * Constructs a new EdgeColourPicker.
 *
 * @param width        Number of pixels to colour around edge.
 * @param inputimage   Image for referencing original image colours.
 * @param scolour      Colour of seed point
 * @param ecolour      Colour to be used for painting the fill edge.
 * @param tol          Tolerance used to determine the edge of the fill.
 */
EdgeColourPicker::EdgeColourPicker(unsigned int width, PNG& inputimage, RGBAPixel scolour, RGBAPixel ecolour, double tol) {
    edgewidth = width;
    img = inputimage;
    seedcolour = scolour;
    edgecolour = ecolour;
    tolerance = tol;
	
}

/**
 * Picks the colour for pixel at point p. If the x or y coordinate is
 * at or within an Euclidean radius of edgewidth pixels from the edge of
 * the fill region, it will be coloured with the required edge color.
 * Otherwise, its colour will not be changed.
 *
 * @param p   The point for which you're picking a colour.
 * @return    The colour chosen for (p).
 */
RGBAPixel EdgeColourPicker::operator()(pair<unsigned int, unsigned int> p) {
    unsigned int x = p.first;
    unsigned int y = p.second; 

    RGBAPixel* basePixel = img.getPixel(x,y);

    double colorDistance = getColourDistance(*basePixel, seedcolour);

    if(colorDistance > tolerance) {
        return *basePixel;
    }

    unsigned int xMin = (x > edgewidth) ? x - edgewidth : 0;
    unsigned int xMax = (x + edgewidth < img.width()) ? x + edgewidth : img.width() - 1;
    unsigned int yMin = (y > edgewidth) ? y - edgewidth : 0;
    unsigned int yMax = (y + edgewidth < img.height()) ? y + edgewidth : img.height() - 1;

    for (unsigned int yStart = yMin; yStart <= yMax; yStart++) {
        for (unsigned int xStart = xMin; xStart <= xMax; xStart++) {
            if (xStart == x && yStart == y) {
                continue;
            }

            unsigned int distance = getEuclideanDistance(x, y, xStart, yStart);
            if(distance <= edgewidth * edgewidth) {
                RGBAPixel* neighborPixel = img.getPixel(xStart, yStart);
                double neighborDistance = getColourDistance(*neighborPixel, seedcolour);
                if (neighborDistance > tolerance) {
                    return edgecolour;
                }
            }
        }
    }

    bool nearImageEdge = (x < edgewidth) || (x >= img.width() - edgewidth) || 
        (y < edgewidth) || (y >= img.height() - edgewidth);

        if(nearImageEdge) {
            return edgecolour;
        }
        return *basePixel;
    }
    /*
    unsigned int x = p.first;
    unsigned int y = p.second;
    RGBAPixel* basePixel = img.getPixel(x, y);

    //first check to see if my current pixel is even within tol
    double isValidPixel = getColourDistance(*basePixel, seedcolour);

    if(isValidPixel > tolerance) {
        return *basePixel;
    }

    // I know my pixel is within the tolerance

    unsigned int xMin = 0;
    unsigned int xMax = x + edgewidth;

    unsigned int yMin = 0;
    unsigned int yMax = y + edgewidth;

    // Sets xMin starting position, 0 otherwise
    if( x > edgewidth) {
        xMin = x - edgewidth;
    }

    // Sets yMin starting position, 0 otherwise
    if(y > edgewidth) {
        yMin = y - edgewidth;
    }

    // Deals with xMax edge Case
    if(xMax >= img.width()) {
        xMax = (unsigned int) (img.width() - 1);
    }

    // Deals with yMax edge Case
    if(yMax >= img.height()) {
        yMax = (unsigned int) (img.height() - 1);
    }

    // If any pixel within my local area is an edge pixel, then do nothing

    // Assuming I dealt with the edge cases correctly, next I need grab each pixel
    for(unsigned int yStart = yMin; yStart <= yMax; yStart++) {
        for(unsigned int xStart = xMin; xStart <= xMax; xStart++) {
            unsigned int distance = getEuclideanDistance(x, y, xStart, yStart);
            if(distance <= edgewidth * edgewidth) {
                RGBAPixel* nextPixel = img.getPixel(xStart, yStart);
                double colorDistance = getColourDistance(*nextPixel, seedcolour);
                if(colorDistance > tolerance) {
                    return edgecolour;
                }
            }
        }
    }
    
    bool xBoundry = (x < edgewidth || x >= (img.width() - edgewidth));
    bool yBoundry = (y < edgewidth || y >= (img.height() - edgewidth));

    if(xBoundry || yBoundry) {
        return edgecolour;
    }

    return *basePixel;
    */
    

/**
 * Add your private EdgeColourPicker function implementations and/or attributes below
 */

unsigned int EdgeColourPicker::getEuclideanDistance(unsigned int x, unsigned int y, unsigned int a, unsigned int b) {
    int xSq = ((int) x - (int) a) * ((int) x - (int) a);
    int ySq = ((int) y - (int) b) * ((int) y - (int) b);
    unsigned int result = (unsigned int) xSq + (unsigned int) ySq;
    return result;
 }

 double EdgeColourPicker::getColourDistance(RGBAPixel& nextPixel, RGBAPixel& seedcolour) {

    
    double r = (double) nextPixel.r - (double) seedcolour.r;
    double g = (double) nextPixel.g - (double) seedcolour.g;
    double b = (double) nextPixel.b - (double) seedcolour.b;
    /*
    double r = (double) seedcolour.r - (double) nextPixel.r;
    double g = (double) seedcolour.g - (double) nextPixel.g;
    double b = (double) seedcolour.b - (double) nextPixel.b;
    */
    double result = (r * r + g * g + b * b);
    return result;
 }