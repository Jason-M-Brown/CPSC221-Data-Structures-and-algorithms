/**
 * @file stripeColourPicker.h
 * Definition of a stripe colour picker.
 *
 */
#ifndef _STRIPECOLOURPICKER_H_
#define _STRIPECOLOURPICKER_H_

#include "colourPicker.h"

 /**
  * StripeColourPicker: a functor that determines the colour that should be
  * used given an x and y coordinate using a diagonal stripe pattern. If you
  * need more private attributes for local storage, or helper functions,
  * you can define them in stripeColourPicker-private.h.
  * Remember to define a custom destructor if your colour picker needs any
  * dynamically-allocated memory.
  */
class StripeColourPicker : public ColourPicker
{
public:
    /**
     * Constructs a new StripeColourPicker.
     *
	 * @param stripe_width The width of each alternating stripe, in pixels
	 * @param stripe_colour1 Colour of the main stripe
	 * @param stripe_colour2 Colour of the alternate stripe
     */
    StripeColourPicker(unsigned int stripe_width, RGBAPixel stripe_colour1, RGBAPixel stripe_colour2);

    /**
     * Picks the colour for pixel p at coordinates (x, y).
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
    virtual RGBAPixel operator()(pair<unsigned int, unsigned int> p);

private:

    unsigned int stripewidth;
	RGBAPixel colour1;
	RGBAPixel colour2;

    /**
     * @todo Define any additional private member variables or helper
     *	functions in stripeColourPicker-private.h as you see fit.
     */
    #include "stripeColourPicker-private.h"
};

#endif
