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
PhotoNegativeColourPicker::PhotoNegativeColourPicker(PNG& orig)
{
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
RGBAPixel PhotoNegativeColourPicker::operator()(pair<unsigned int, unsigned int> p)
{
    // Replace the line below with your implementation
    return RGBAPixel();
}

/**
 * Add your private PhotoNegativeColourPicker function implementations and/or attributes below
 */
