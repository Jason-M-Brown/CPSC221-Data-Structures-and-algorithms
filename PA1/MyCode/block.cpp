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
    // Build the vector rows
    data.resize(height);

    // Iterate over each vector row and add the height
    // STUDY NOTES: It's faster to allocate the memory first if I know how much I need
    for(int row = 0; row < height; row++) {
        data[row].resize(width);
    }

    // Place the data in the 2D vector
    for(int row = 0; row < height; row++) {
        for(int col = 0; col < width; col++) {
           data[row][col] = *img.getPixel(x + col, y + row);
        }
    }
}

/**
 * Renders the given block's pixel data onto img with its upper
 * left corner at (x, y). Assumes block fits on the
 * image.
 * @param use_avg If false, render each pixel using its true colour.
 *                Otherwise, render each pixel using the block's average colour.
 */
void Block::Render(PNG& img, unsigned int x, unsigned int y, bool use_avg) const {
    // ALPHA CHECK HERE
    RGBAPixel avgColour;
    RGBAPixel* nextPixel;
    unsigned int height = Height();
    unsigned int width = Width();

    // Only do the work, if the work is needed.
    if (use_avg) {
        avgColour = AvgColour();
    }

    // RGBAPixel * getPixel(unsigned int x, unsigned int y) const;


    for(unsigned int row = 0; row < height; row++) {
        unsigned int nextRow = row + y;                  // offsets y
        for(unsigned int col = 0; col < width; col++) {
            unsigned int nextCol = col + x;              // offsets x
            // Grab the next pixel pointer
            nextPixel = img.getPixel(nextCol, nextRow);

            if(nextPixel == nullptr) {
                continue;
            }

            // if I am taking the average color, run this code
            if(use_avg) {
                nextPixel->r = avgColour.r;
                nextPixel->g = avgColour.g;
                nextPixel->b = avgColour.b;
                // might be a bug, no alpha
                continue;
            }
            // else just use the default colours
            nextPixel->r = data[row][col].r;
            nextPixel->g = data[row][col].g;
            nextPixel->b = data[row][col].b;
            // might be a bug, no alpha
        }
    }
}

/**
 * Return the height of the block.
 */
// DONE 1/6
unsigned int Block::Height() const {
    if (data.empty()) {
        return 0;
    }
    return data.size();
}

/**
 * Return the width of the block.
 */
 // DONE 2/6
unsigned int Block::Width() const {
    if (data.empty()) {
        return 0;
    }
    // edge case, what if the first row is empty? if bug fixed 
	return data[0].size();
}

/**
 * Returns the average colour of all pixels contained in the block.
 */
 // DONE 3/6
RGBAPixel Block::AvgColour() const {
    // I didn't use alpha in this, could be a bug
    // also colours are of type char, not unsigned, so that might cause issues.
    // perms are of type int though? 
    unsigned int numberOfPixels = 0;
    unsigned int redCount   = 0;
    unsigned int blueCount  = 0;
    unsigned int greenCount = 0;

    for(unsigned int y = 0; y < data.size(); y++) {
        for(unsigned int x = 0; x < data[y].size(); x++) {
            RGBAPixel nextPixel = data[y][x];
            redCount   += nextPixel.r;
            blueCount  += nextPixel.b;
            greenCount += nextPixel.g;
            numberOfPixels += 1;
        }
    }

    if (numberOfPixels == 0) {
        return RGBAPixel(0, 0, 0);
    }
    redCount = redCount / numberOfPixels; 
    blueCount = blueCount / numberOfPixels;
    greenCount = greenCount / numberOfPixels;
	/* replace the line below with your implementation */
	return RGBAPixel(redCount, greenCount, blueCount);
}

/**
 * Flips the contents of the block's pixel data horizontally (over a vertical axis)
 * so that when rendered, the contents appear to be mirrored left-to-right.
 */
void Block::FlipHorizontal() {
    
    if (data.empty()) {
        return;
    }

    RGBAPixel tempPixel;

    for(unsigned int yPos = 0; yPos < Height(); yPos++) {
        unsigned int decrementor = Width() - 1;         // my end pointer
        unsigned int stop = Width() / 2;            // middle index of array

        // edge cases: 
        // - if I have one pixel  1/2 = 0, so loop isn't ran (working)
        // - if I have even pixels 2/2 = 1  0<1 we swap the first and last pixel, then exit
        // - if odd 3/2 = 1 0<1 we swap first and last pixel, but don't care about the center

        // NOTE TO TA: if your reading this I didn't use the SWAP function because I read
        //             the final doesn't allow for std library. 

        for(unsigned int xPos = 0; xPos < stop; xPos++) {          // xPos moves front pointer
            tempPixel = data[yPos][xPos];                // store first pixel
            data[yPos][xPos] = data[yPos][decrementor];  // replace first pixel with last
            data[yPos][decrementor] = tempPixel;         // replace last pixel with first

            decrementor--;                               // move end pointer in by one
            }
    }
}