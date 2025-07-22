/**
 * @file chain-given.cpp
 * @description Instructor-provided implementation of Chain functions for CPSC 221 PA1.
 *              The Chain is a null-terminated, singly-linked list containing
 *              two-dimensional image data.
 *              This file will not be submitted.
 */

#include "chain.h"

/**
 * Given functions for the Chain class.
 *
 * ****WARNING****
 *
 * You should not modify this file.  It is not one of the files
 * you will submit.  We will grade your submission using the
 * original version of this file.
 */

/**
 * Default (no-argument) constructor
 */
Chain::Chain() {
    _front = nullptr;
    _back = nullptr;
}

/**
 * Copy constructor
 */
Chain::Chain(Chain const& other) {
    _front = nullptr;
    _back = nullptr;
    Copy(other);
}

/**
 * Assignment operator
 */
Chain& Chain::operator=(Chain const& rhs) {
    if (this != &rhs) {
        Clear(); // you will implement clear
        Copy(rhs); // and copy
    }
    return *this;
}

/**
 * Checks for empty list
 */
bool Chain::Empty() const {
    return _front == nullptr && _back == nullptr;
}
