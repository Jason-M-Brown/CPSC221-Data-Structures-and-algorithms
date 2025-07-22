/**
 * @file        edgeColourPicker.h
 * @description Definition of an edge colour picker.
 *
 */
#ifndef _EDGECOLOURPICKER_H_
#define _EDGECOLOURPICKER_H_

#include "colourPicker.h"

/**
 * EdgeColourPicker: a functor that determines the colour that should be used
 * given a `point`. If the given position is near the edge of
 * the fill region, then it should be coloured with the required colour. Otherwise, its colour
 * should not change.
 *
 * The following criteria should be used to determine if a position p is near
 * an edge: if p is within distance `edgewidth` of any cell that will be outside the
 * fill region, then the pixel at position p should be coloured using the chosen edge colour.
 *
 * You will use Euclidian distance to judge proximity. That means if p is at
 * location (x,y), its distance to a point at location (a,b) is
 * squareRoot([(x-a)^2 + (y-b)^2]). Note that you should not ever have to
 * compute the square root to solve this problem.
 *
 */
class EdgeColourPicker : public ColourPicker {
    public:
        /**
         * Constructs a new EdgeColourPicker.
         *
         * @param width        Number of pixels to colour around edge.
         * @param inputimage   Image for referencing original image colours.
         * @param scolour      Colour of seed point
	     * @param ecolour      Colour to be used for painting the fill edge.
         * @param tol          Tolerance used to determine the edge of the fill.
         */
        EdgeColourPicker(unsigned int width, PNG& inputimage, RGBAPixel scolour, RGBAPixel ecolour, double tol);

        /**
         * Picks the colour for pixel at point p. If the x or y coordinate is
         * at or within an Euclidean radius of edgewidth pixels from the edge of
         * the fill region, it will be coloured with the required edge colour.
         * Otherwise, its colour will not be changed.
         *
         * @param p   The point for which you're picking a colour.
         * @return    The colour chosen for (p).
         */
        virtual RGBAPixel operator()(pair<unsigned int, unsigned int> p);

    private:
        unsigned int edgewidth;   // Number of pixels to use for edge qualification
        PNG img;                  // Original image used in flood fill algorithm
        RGBAPixel seedcolour;     // Colour of seed point, for checking fill region
        RGBAPixel edgecolour;     // Colour used for painting the fill edge
        double tolerance;         // Tolerance used in flood fill algorithm

        /**
         * @todo Define any additional private member variables or helper
         *	functions in edgeColourPicker_private.h as you see fit.
         */
        #include "edgeColourPicker-private.h"
};

#endif
