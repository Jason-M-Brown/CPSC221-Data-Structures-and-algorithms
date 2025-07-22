/**
 * @file block.cpp
 * @description Implementation of Block functions for CPSC 221 PA1
 *              This file must be submitted.
 */

#include "block.h"
#include <cmath>

/**
 * Creates a block that is width X height pixels in size
 * by copying the pixels from (x, y) to (x+width-1, y+height-1)
 * in img. Assumes img is large enough to supply these pixels.
 */
void Block::Build(PNG& img, unsigned int x, unsigned int y, int width, int height) {
	/* your code here */

}

/**
 * Renders the given block's pixel data onto img with its upper
 * left corner at (x, y). Assumes block fits on the
 * image.
 * @param use_avg If false, render each pixel using its true colour.
 *                Otherwise, render each pixel using the block's average colour.
 */
void Block::Render(PNG& img, unsigned int x, unsigned int y, bool use_avg) const {
	/* your code here */

}

/**
 * Return the height of the block.
 */
unsigned int Block::Height() const {
	/* replace the line below with your implementation */
	return 0;
}

/**
 * Return the width of the block.
 */
unsigned int Block::Width() const {
	/* replace the line below with your implementation */
	return 0;
}

/**
 * Returns the average colour of all pixels contained in the block.
 */
RGBAPixel Block::AvgColour() const {
	/* replace the line below with your implementation */
	return RGBAPixel();
}

/**
 * Flips the contents of the block's pixel data horizontally (over a vertical axis)
 * so that when rendered, the contents appear to be mirrored left-to-right.
 */
void Block::FlipHorizontal() {
	/* your code here */

}