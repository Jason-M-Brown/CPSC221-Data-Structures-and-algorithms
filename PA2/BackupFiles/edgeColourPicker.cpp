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
EdgeColourPicker::EdgeColourPicker(unsigned int width, PNG& inputimage, RGBAPixel scolour, RGBAPixel ecolour, double tol)
{
    // Complete your implementation below
	
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
RGBAPixel EdgeColourPicker::operator()(pair<unsigned int, unsigned int> p)
{
    // Replace the line below with your implementation
    return RGBAPixel();
}

/**
 * Add your private EdgeColourPicker function implementations and/or attributes below
 */
