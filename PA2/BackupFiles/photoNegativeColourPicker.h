/**
 * @file photoNegativeColourPicker.h
 * Definition of a photo negative colour picker.
 *
 */
#ifndef _PHOTONEGATIVECOLOURPICKER_H_
#define _PHOTONEGATIVECOLOURPICKER_H_

#include "colourPicker.h"

 /**
  * PhotoNegativeColourPicker: a functor that determines applies a "photo-negative"
  * effect to the pixel at a given (x, y) image position. If you
  * need more private attributes for local storage, or helper functions,
  * you can define them in photoNegativeColourPicker-private.h.
  * Remember to define a custom destructor if your colour picker needs any
  * dynamically-allocated memory.
  */
class PhotoNegativeColourPicker : public ColourPicker
{
public:
    /**
     * Constructs a new PhotoNegativeColourPicker.
     */
    PhotoNegativeColourPicker(PNG& orig);

    /**
     * Picks the colour for pixel p at coordinates (x, y).
     *
     * A "photo-negative" effect will be applied each R/G/B colour channel of
     * pixel p's original colour. The alpha channel should remain unchanged.
     * 
     * It will be up to you to decide what a suitable "negative" effect should be
     * in the RGB colour space.
     */
    virtual RGBAPixel operator()(pair<unsigned int, unsigned int> p);

private:

    PNG original; // original image for reference

    /**
     * @todo Define any additional private member variables or helper
     *	functions in photoNegativeColourPicker-private.h as you see fit.
     */
#include "photoNegativeColourPicker-private.h"
};

#endif
