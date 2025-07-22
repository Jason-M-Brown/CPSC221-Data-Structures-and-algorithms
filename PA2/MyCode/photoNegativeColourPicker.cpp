/**
 * @file photoNegativeColourPicker.cpp
 * @description Implements the PhotoNegativeColourPicker constructor and () function
 *              for CPSC 221 PA2
 *
 *              THIS FILE WILL BE SUBMITTED
 */

#include "photoNegativeColourPicker.h"

 /**
  * Constructs a new PhotoNegativeColourPicker.
  */
PhotoNegativeColourPicker::PhotoNegativeColourPicker(PNG& orig) {
    original = orig;
    // Complete your implementation below

}

/**
 * Picks the colour for pixel p at coordinates (x, y).
 *
 * A "photo-negative" effect will be applied each R/G/B colour channel of
 * pixel p's original colour. The alpha channel should remain unchanged.
 * 
 * It will be up to you to decide what a suitable "negative" effect should be
 * in the RGB colour space.
 */
RGBAPixel PhotoNegativeColourPicker::operator()(pair<unsigned int, unsigned int> p) {
    RGBAPixel* nextPixel = original.getPixel(p.first, p.second);
    unsigned char r = 255 - nextPixel->r;
    unsigned char g = 255 - nextPixel->g;
    unsigned char b = 255 - nextPixel->b;

    return RGBAPixel(r, g, b);
}

/**
 * Add your private PhotoNegativeColourPicker function implementations and/or attributes below
 */
