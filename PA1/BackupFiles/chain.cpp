/**
 * @file chain.cpp
 * @description Implementation of Chain functions for CPSC 221 PA1.
 *              The Chain is a null-terminated, singly-linked list containing
 *              two-dimensional image data.
 *              This file must be submitted.
 */

#include "chain.h"
#include <cmath>

// PA1 functions
// Complete all of the missing implementation
// and submit this file for grading.

/**
 * Most useful constructor. Constructs a chain from an input image
 * and a specified number of blocks in each row and column.
 * You should leverage your implementations of Block::Build and Chain::InsertAtBack
 * for this.
 *
 * @param imIn     The image providing the blocks
 * @param numRows  How many blocks the list will have in the vertical axis
 * @param numCols  How many blocks the list will have in the horizontal axis
 * @pre The input image's height is exactly divisible by numRows
 * @pre The input image's width is exactly divisible by numCols
 */
Chain::Chain(PNG& imIn, int numRows, int numCols) {
    /* Replace the two lines below with your implementation */
	_front = nullptr;
	_back = nullptr;
}

/**
 * Destroys the current Chain, automatically invoked when this
 * Chain object goes out of scope. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain() {
	/* your code here */

}

/**
 * Inserts a new node at the end of the list and returns a pointer to
 * the newly created node.
 *
 * @param ndata = The data to be inserted.
 */
Node* Chain::InsertAtBack(const Block &ndata) {
	/* Replace the line below with your implementation */
	return nullptr;
}

/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class.
 */
void Chain::Clear() {
	/* your code here */

}

/**
 * Makes the current object into a copy of the parameter:
 * All member variables should have the same value as
 * those of other, but the memory should be completely
 * independent. This function is used in both the copy
 * constructor and the assignment operator for Chains.
 * Note that you have access to the private attributes of other.
 */
void Chain::Copy(Chain const &other) {
	/* your code here */
	
}

/**
 * Takes the current chain and renders it into a
 * correctly sized PNG. The blocks in the chain
 * are placed in the image left to right in order
 * of their occurrence in the chain.
 * 
 * @param numCols The number of blocks to render in each row of the output image.
 *                If there are insufficient blocks to complete the last row,
 *			          the remaining pixels will be black.
 * @param use_avg If false, render each block using each pixel's
 *                    true colour.
 *                Otherwise, render each block using its average colour.
 */
PNG Chain::Render(int numCols, bool use_avg) const {
    /* Replace the line below with your implementation */
    return PNG();
}

/**
 * Modifies the current chain:
 * Rearrange the nodes in the list so that when rendered with numCols
 * blocks per row, the image will appear to be mirrored across a vertical axis.
 * This must be achieved by reassigning pointers along with using Block::FlipHorizontal.
 * You cannot swap any block contents between nodes.
 */
void Chain::FlipHorizontal(int numCols) {
	/* your code here */

}

/**************************************************
* IF YOU HAVE DECLARED PRIVATE FUNCTIONS IN       *
* chain-private.h, COMPLETE THEIR IMPLEMENTATIONS *
* HERE                                            *
**************************************************/

