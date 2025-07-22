#include "solidColourPicker.h"

SolidColourPicker::SolidColourPicker(RGBAPixel fillColour)
{
    /* sample code */
    // constructor initializes all member attributes.
    // Here, the colour attribute is the only one to initialize.
    colour = fillColour;
}

RGBAPixel SolidColourPicker::operator()(pair<unsigned int, unsigned int> p)
{
    /* sample code */
    // This function determines the colour of the pixel in the output image at point p.
    // For SolidColourPicker, this simply uses the fixed colour
    // of the member attribute.
    // Other ColourPickers will need to do some computation to decide what
    // colour to use.

    return colour; // member attribute of SolidColourPicker
}
