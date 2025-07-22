/**
 * @file chain.cpp
 * @description Implementation of Chain functions for CPSC 221 PA1.
 *              The Chain is a null-terminated, singly-linked list containing
 *              two-dimensional image data.
 *              This file must be submitted.
 */

#include "chain.h"
#include <cmath>
#include <iostream>

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
    _front = nullptr;
    _back = nullptr;
    if (numRows == 0 || numCols == 0) {
        return;
    }
    unsigned int blockWidth = imIn.width() / numCols;
    unsigned int blockHeight = imIn.height() / numRows;

    unsigned int numOfBlocks = numRows * numCols;
    unsigned int startX = 0;
    unsigned int startY = 0;

    // Temporary storage for a block
    Block nextBlock;

    // Iterates over each block chunk
    for(unsigned int blockNumber = 0; blockNumber < numOfBlocks; blockNumber++) {
        nextBlock.Build(imIn, startX, startY, blockWidth, blockHeight); // Build the block
        InsertAtBack(nextBlock); // Put object at the back of the List
        // Update loop Invariant 
        startX += blockWidth;
        // Check to see if I am at the edge of my image, if so reset
        // xStart pointer and update yStart pointer to correct coordinates
        if(startX >= imIn.width()) {  //CHANGE >
            startX = 0;
            startY += blockHeight;
        }
    }
}

/**
 * Destroys the current Chain, automatically invoked when this
 * Chain object goes out of scope. This function should ensure that
 * memory does not leak on destruction of a chain.
 */
Chain::~Chain() {
    Clear();
}

/**
 * Inserts a new node at the end of the list and returns a pointer to
 * the newly created node.
 *
 * @param ndata = The data to be inserted.
 */
Node* Chain::InsertAtBack(const Block &ndata) {
    // if this is true, then I know I am at the first value
    if(_front == nullptr) {
        Node* nextNode = new Node(ndata);
        _front = nextNode;
        _back = nextNode; 
        return nextNode;
    }
    // I know I have already started the list.. so I need to add to the end of it
    Node* nextNode = new Node(ndata);
    _back->next = nextNode;
    _back = _back->next;
	/* Replace the line below with your implementation */
	return nextNode;
}

/**
 * Destroys all dynamically allocated memory associated with the
 * current Chain class.
 */
void Chain::Clear() {
    // I have a seg fault in here. (fixed)
    Node* currentNode = _front;

	while(currentNode != nullptr) {
        Node* nextNode = currentNode->next;
        delete currentNode;
        currentNode = nextNode;
    }
    _front = nullptr;
    _back = nullptr;
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
    // Clears my current Chain
	Clear();

    // Deal with the edge case where other chain is empty
    // because I Clear() _front, I know _front is null. 
    if(other._front == nullptr) {
        return;
    }

    // Keep track of of pointers
    Node* copyingNode = other._front;

    Node* thisFront = nullptr;
    Node* thisBack = nullptr;

    while(copyingNode != nullptr) {

        Node* tempNode = new Node(copyingNode->data);

        if(thisFront == nullptr) {
            thisFront = tempNode;
            thisBack  = tempNode; 
            copyingNode = copyingNode->next;
            continue;
        }
        
        thisBack->next = tempNode;
        thisBack = thisBack->next;
        copyingNode = copyingNode->next;
    }
    _front = thisFront;
    _back = thisBack;
    _back->next = nullptr;
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
    // If I have time, splitup into helper functions

    if(_front == nullptr) {
        return PNG();
    }
    
    Node* nextNode = _front;
    unsigned int nodeCount   = 0;
    unsigned int blockWidth  = _front->data.Width();
    unsigned int blockHeight = _front->data.Height();

    // Count how many Nodes I have
    while(nextNode != nullptr) {
        nodeCount += 1;
        nextNode = nextNode->next;
    }
    // Reset nextNode Pointer to Start, because I iterated down it
    nextNode = _front;
    
    // Get Image Dimensions
    unsigned int imgHeight = nodeCount / numCols * blockHeight;
    unsigned int imgWidth = numCols * blockWidth;

    // Check for the extra row Edge Case and add it in if it's needed
    if(nodeCount % numCols) {
        imgHeight += blockHeight;
    }

    // Build the Image
    PNG renderPNG = PNG(imgWidth, imgHeight);

    // Start Rendering the image to background PNG
    unsigned int xPos = 0;
    unsigned int yPos = 0;

    while(nextNode != nullptr) {
        nextNode->data.Render(renderPNG, xPos, yPos, use_avg);
        
        xPos += blockWidth;

        if(xPos == imgWidth) {
            xPos = 0;
            yPos += blockHeight;
        }
        nextNode = nextNode->next;
    }
    return renderPNG;
}

/*
Modifies the current chain:,
Rearrange the nodes in the list so that when rendered with numCols,
blocks per row, the image will appear to be mirrored across a vertical axis.,
This must be achieved by reassigning pointers along with using Block::FlipHorizontal.,
You cannot swap any block contents between nodes.
*/
void Chain::FlipHorizontal(int numCols) {
    if(_front == nullptr) {
        return;
    }

    // Grabs 1001 pointers
    Node* current = _front;
    Node* prev = nullptr;
    Node* next = nullptr;
    Node* tail = nullptr;
    Node* head = nullptr;     
    Node* newFront = nullptr;       
    Node* newBack = nullptr;      
    bool  isFirstRow = true;

    // If current is null I am done
    /////aaaa
    while (current != nullptr) {
        tail = current;
        current->data.FlipHorizontal();
        prev = current;
        current = current->next;
        if (current != nullptr) {
            next = current->next;
        } else {
            next = nullptr;
        }

        for (int x = 1; x < numCols && current != nullptr; x++) {
            current->data.FlipHorizontal();
            current->next = prev;
            prev = current;
            current = next;
            if (current != nullptr) {
                next = current->next;
            } else {
                next = nullptr;
            }
        }

        if (isFirstRow) {
            newFront = prev;   
            isFirstRow = false;
        } else {
            head->next = prev;   
        }

        head = tail;         

        if (current == nullptr) {
            newBack = tail;
            tail->next = nullptr;
            break;
        }
    }
    _front = newFront;
    _back  = newBack;
}

/**************************************************
* IF YOU HAVE DECLARED PRIVATE FUNCTIONS IN       *
* chain-private.h, COMPLETE THEIR IMPLEMENTATIONS *
* HERE                                            *
**************************************************/

