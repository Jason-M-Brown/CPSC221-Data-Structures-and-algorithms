/*
 * @file        colourPicker.h
 * @description Definition of a colour picker abstract base class.
 *
 */
#ifndef _COLOURPICKER_H_
#define _COLOURPICKER_H_

#include "cs221util/RGBAPixel.h"
#include "cs221util/PNG.h"

using namespace cs221util;

/*
 * ColourPicker: a functor that determines the colour that should be used
 * given an x and y coordinate.
 *
 */
class ColourPicker
{
	public:
		/*
		 * Destructor: does nothing, but as it is virtual, you may overload it in
		 * derived classes if needed.
		 */
		virtual ~ColourPicker(){};

		/*
		 * Picks the colour for pixel (x, y).
		 *
		 * This function **must** be defined in the subclass! It chooses a colour for
		 * the given point and returns it.
		 *
		 * For example, the NegativeColourPicker::operator()() function is defined so as
		 * to return the negative colour of the pixel at the specified location of the original image.
		 *
		 * For the other patterns, you will have to figure out how to "pick" the
		 * colors.
		 *
		 * @param p The point for which you're picking a colour.
		 * @return The colour chosen for (p).
		 */
		virtual RGBAPixel operator()(pair<unsigned int, unsigned int> p) = 0;
};

#endif
