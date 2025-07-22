/**
 * @file chain.h
 * @description Declaration of Chain functions for CPSC 221 PA1.
 *              The Chain is a null-terminated, singly-linked list containing
 *              two-dimensional image data.
 *              This file will NOT be submitted.
 */

#ifndef _CHAIN_H_
#define _CHAIN_H_

#include <string>
#include <iostream>
#include "block.h"
using namespace std;

/**
 * The Node class is typically made private to the Chain (list) class
 * following the principle of encapsulation -- the end user does not need
 * to know our node-based implementation details.
 * 
 * However, here we make this a public class for testing purposes.
 */
class Node {
    public:
        // default constructor
        Node() : next(NULL), data(Block()) {};
        // data provided constructor
        Node(const Block& ndata) : next(NULL), data(ndata) {};

        Node* next; // ptr to next node in chain
        Block data; // data held by Node
};

/**
 * Chain: This is a container class for blocks. It is implemented
 * as a singly-linked list of nodes, each of which contains a block.
 *
 * You should not remove anything from this class definition, but
 * you may find it helpful to add your own private helper functions to it.
 */
class Chain {
    public:
        Chain();
        Chain(const Chain &other);

        Chain &operator=(const Chain &rhs);

        bool Empty() const;

        /* =============== end of given functions ====================*/

        /* =============== public PA1 FUNCTIONS =========================*/

        Chain(PNG& imIn, int numRows, int numCols);

        ~Chain();
   
        PNG Render(int numCols, bool use_avg) const;

        void FlipHorizontal(int numCols);

        /* =============== end of public PA1 FUNCTIONS =========================*/

    private:
        /*
         * Private member variables.
         *
         * You must use these as specified in the spec and may not rename them.
         * You may add more into chain-private.h if you need them.
         */

        Node* _front; // ptr to first node in chain or NULL if chain is empty
        Node* _back;  // ptr to last node in chain or NULL if chain is empty

        /* =================== private PA1 functions ============== */

        /**
         * Destroys all dynamically allocated memory associated with the
         * current Chain class (including sentinels). clear() is called
         * by destructor and op=.
         */
        void Clear();

        /**
         * Copies the parameter other Chain into the current Chain.
         * Does not free any memory. Called by copy constructor and op=.
         * @param other = The Chain to be copied.
         */
        void Copy(const Chain &other);

        /**
         * Inserts a node at the end of this list.
         * Returns a pointer to the inserted node.
         */
        Node* InsertAtBack(const Block &ndata);

        /**
         * If you wish to define any private functions or attributes for the Chain class,
         * write your definitions into "chain-private.h"
         */
        #include "chain-private.h"

        /* =================== end of private PA1 functions ============== */
};

#endif
