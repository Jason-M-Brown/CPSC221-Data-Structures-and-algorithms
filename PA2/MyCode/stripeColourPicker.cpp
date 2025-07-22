/**
 * @file stripeColourPicker.cpp
 * @description Implements the StripeColourPicker constructor and () function
 *              for CPSC 221 PA2
 *
 *              THIS FILE WILL BE SUBMITTED
 */

#include "stripeColourPicker.h"

/**
 * Constructs a new StripeColourPicker.
 *
 * @param stripe_width The width of each alternating stripe, in pixels
 * @param stripe_colour1 Colour of the main stripe
 * @param stripe_colour2 Colour of the alternate stripe
 */

StripeColourPicker::StripeColourPicker(unsigned int stripe_width, RGBAPixel stripe_colour1, RGBAPixel stripe_colour2) {
    // Complete your implementation below
	stripewidth = stripe_width;
    colour1 = stripe_colour1;
    colour2 = stripe_colour2;

}

/**
 * Picks the colour for pixel (x, y).
 *
 * The stripe pattern to be drawn consists of alternating stripes each of stripewidth pixels,
 * in a 45-degree forward slash orientation.
 * e.g.  / / / / / 
 *        / / / / /
 *       / / / / / 
 *        / / / / /
 *
 * For reference, coordinate (0, 0) will be the left-most pixel of a colour1 stripe.
 */
RGBAPixel StripeColourPicker::operator()(pair<unsigned int, unsigned int> p) {

    // do some math
    unsigned int x = p.first;
    unsigned int y = p.second; 
    x = (x + y) / stripewidth;

    // if I'm colour two, set value to colour2

    if(x % 2 == 0) {
        return colour1;
    } else {
        return colour2;
    }
}

/**
 * Add your private StripeColourPicker function implementations and/or attributes below
 */

