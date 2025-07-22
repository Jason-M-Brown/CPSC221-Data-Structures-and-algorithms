/**
 * @file block.h
 * @description Declaration of Block functions for CPSC 221 PA1
 *              This file will NOT be submitted.
 */

#ifndef _BLOCK_H_
#define _BLOCK_H_

#include <vector>
#include <iostream>
#include "cs221util/PNG.h"
#include "cs221util/RGBAPixel.h"
using namespace std;
using namespace cs221util;

class Block {

	public:
		/** 
		 * Creates a block that is width X height pixels in size
		 * by copying the pixels from (x, y) to (x+width-1, y+height-1)
		 * in img. Assumes img is large enough to supply these pixels.
		 */
		void Build(PNG &img, unsigned int x, unsigned int y, int width, int height);

		/**
		 * Renders the given block's pixel data onto img with its upper
		 * left corner at (x, y). Assumes block fits on the 
		 * image.
		 * @param use_avg If false, render each pixel using its true colour.
		 *                Otherwise, render each pixel using the block's average colour.
		 */
		void Render(PNG &img, unsigned int x, unsigned int y, bool use_avg) const;

		/**
		 * Return the width and height of the block.
		 */
		unsigned int Width() const;
		unsigned int Height() const;

		/**
		 * Returns the average colour of all pixels contained in the block.
		 */
		RGBAPixel AvgColour() const;

		/**
		 * Flips the contents of the block's pixel data horizontally (over a vertical axis)
		 * so that when rendered, the contents appear to be mirrored left-to-right.
		 */
		void FlipHorizontal();

   
	private:
		vector<vector<RGBAPixel>> data;
};

#endif
