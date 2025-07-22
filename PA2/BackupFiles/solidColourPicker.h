/**
 * @file solidColourPicker.h
 * Definition of a solid colour picker.
 *
 */
#ifndef _SOLIDCOLOURPICKER_H_
#define _SOLIDCOLOURPICKER_H_

#include "colourPicker.h"

/**
 * SolidColourPicker: a functor that determines the colour that should be
 * used given an x and y coordinate using a solid pattern.
 */
class SolidColourPicker : public ColourPicker
{
    public:
        /**
         * Constructs a new SolidColourPicker.
         *
         * @param fillColour The colour for this colour picker.
         */
        SolidColourPicker(RGBAPixel fillColour);

        /**
         * Picks the colour for pixel (x, y).
         *
         * Simply returns the same colour (used to construct the picker) all
         * of the time.
         */
        virtual RGBAPixel operator()(pair<unsigned int, unsigned int> p);

    private:
        /**
         * Private attributes that are needed for storing/managing useful information
         * for operator(). Your other ColourPicker implementations will likely need other attributes.
         */
        RGBAPixel colour;
};

#endif
