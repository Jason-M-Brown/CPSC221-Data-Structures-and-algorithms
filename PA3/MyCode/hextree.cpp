/**
 * @file hextree.cpp
 * @description student implementation of HexTree class used for storing image data
 *              CPSC 221 PA3
 *
 *              SUBMIT THIS FILE
 */

#include "hextree.h"

/**
 * Constructor that builds a HexTree out of the given PNG.
 * Every leaf in the tree corresponds to a pixel in the PNG.
 * Every non-leaf node corresponds to a rectangle of pixels
 * in the original PNG, represented by an (x,y) pair for the
 * upper left corner of the rectangle and an (x,y) pair for
 * lower right corner of the rectangle. In addition, the Node
 * stores a RGBAPixel representing the average colour over the
 * rectangle.
 *
 * The average colour for each node in your implementation MUST
 * be determined in constant time. HINT: this will lead to nodes
 * at shallower levels of the tree accumulating some error in their
 * average colour value, but we will accept this consequence in
 * exchange for faster tree construction.
 * Note that we will be looking for specific colour values in our
 * autograder, so if you instead perform a slow but accurate
 * average colour computation, you will likely fail the test cases!
 *
 * Every node's children correspond to a partition of the
 * node's rectangle into (up to) six smaller rectangles. The node's
 * rectangle is split evenly (or as close to evenly as possible)
 * along both horizontal and vertical axes. If an even split along
 * the vertical axis is not possible, the extra line(s) will be included
 * in either the middle section, or distributed to the left and right sections;
 * If an even split along the horizontal axis is not
 * possible, the extra line will be included in the upper side.
 * If a single-pixel-wide rectangle needs to be split, the left and right children
 * will be null.
 * If a single-pixel-tall rectangle needs to be split,
 * the lower children will be null.
 *
 * In this way, each of the children's rectangles together will have coordinates
 * that when combined, completely cover the original rectangle's image
 * region and do not overlap.
 */
HexTree::HexTree(const PNG& imIn) {
    pair<unsigned int, unsigned int> ul, lr;
    ul = make_pair(0,0);
    lr = make_pair(imIn.width() - 1, imIn.height() -1);
    root = BuildNode(imIn, ul, lr);

}

/**
 * Overloaded assignment operator for HexTree.
 * Part of the Big Three that we must define because the class
 * allocates dynamic memory. This depends on your implementation
 * of the copy and clear funtions.
 * You may refer to the assignment operator defined and given in PA1.
 * Make sure you understand what its implementation means.
 *
 * @param rhs The right hand side of the assignment statement.
 */
HexTree& HexTree::operator=(const HexTree& rhs) {
	// Replace the line below with your implementation 
    if(this != &rhs) {
        Clear();
        Copy(rhs);
    }
	return *this;
}

/**
 * Render returns a PNG image consisting of the pixels
 * stored in the tree. May be used on pruned trees. Draws
 * every leaf node's rectangle onto a PNG canvas using the
 * average colour stored in the node.
 *
 * @param fulldepth whether to render each path fully to a leaf node,
 *                  or to only render down to maxlevel
 * @param maxlevel the maximum depth to render in the tree (ignored if fulldepth == true)
 *                 Beware that maxlevel might be larger than
 *                 the length of some paths in pruned trees
 */
PNG HexTree::Render(bool fulldepth, unsigned int maxlevel) const { 
    unsigned int level = 0;
    auto size = getImageSize(root, fulldepth, maxlevel);
    PNG imageCanvas = PNG(size.first + 1, size.second + 1);
    buildImage(imageCanvas, fulldepth, maxlevel, root, level);
    //buildImage(imageCanvas, root, fulldepth, maxlevel);
	return imageCanvas;
    
}

/**
 *  Prune function trims subtrees as high as possible in the tree.
 *  A subtree is pruned (cleared) if all of the subtree's leaves are within
 *  tolerance of the average colour stored in the root of the subtree.
 *  NOTE - you may use the distanceTo function found in RGBAPixel.h
 *  Pruning criteria should be evaluated on the original tree, not
 *  on any pruned subtree. (we only expect that trees would be pruned once.)
 *
 * You may want at least one recursive helper function for this one.
 *
 * @param tolerance maximum RGBA distance to qualify for pruning
 * @pre this tree has not previously been pruned, nor is copied from a previously pruned tree.
 */
void HexTree::Prune(double tolerance) {
	pruneTolerantChildren(root, tolerance);
}

/**
 *  FlipHorizontal rearranges the contents of the tree, so that
 *  its rendered image will appear mirrored across a vertical axis.
 *  This may be called on a previously pruned/flipped/rotated tree.
 *
 *  After flipping, the A/B/C/D/E/F pointers must map to what will be
 *  physically rendered in the respective NW/NE/SW/SE regions.
 *
 *  You may want a recursive helper function for this one.
 */
void HexTree::FlipHorizontal() {
    unsigned int x1 = root->upLeft.first;
    unsigned int x2 = root->lowRight.first;
    x1 = x2 - x1;

	flipper(root, x1);

}

/**
 * Destroys all dynamically allocated memory associated with the
 * current HexTree object. Complete for PA3.
 * You may want a recursive helper function for this one.
 */
void HexTree::Clear() {
    if(root == nullptr) {
        return;
    }
    clearAllData(root);
    root = nullptr;
}

/**
 * Copies the parameter other HexTree into the current HexTree.
 * Does not free any memory. Called by copy constructor and operator=.
 * You may want a recursive helper function for this one.
 * @param other The HexTree to be copied.
 */
void HexTree::Copy(const HexTree& other) {
	root = copyHelper(other.root);
}


/**
 * Private helper function for the constructor. Recursively builds
 * the tree according to the specification of the constructor.
 * @param img reference to the original input image.
 * @param ul upper left point of current node's rectangle.
 * @param lr lower right point of current node's rectangle.
 */
Node* HexTree::BuildNode(const PNG& img, pair<unsigned int, unsigned int> ul, pair<unsigned int, unsigned int> lr) {
	Node* tree = new Node(ul, lr, RGBAPixel());

    unsigned int width  = lr.first - ul.first + 1;
    unsigned int height = lr.second - ul.second + 1;

    if(width == 1 && height == 1) {
        tree->avg = *img.getPixel(ul.first, ul.second);
    } else {
        unsigned int widthEdge   = width  / 3;
        unsigned int widthMiddle = width  / 3;
        unsigned int heightTop   = height / 2;
        unsigned int heightBot   = height / 2;

        //Deal with edge cases
        if(width % 3 == 1)  {
            widthMiddle += 1;
        } else if (width % 3 == 2) {
            widthEdge   += 1;
        }

        if(height % 2 == 1) {
            heightTop += 1;
        }

        unsigned int sumR = 0;
        unsigned int sumG = 0;
        unsigned int sumB = 0;
        double     accSum = 0;

        //A
        if(widthEdge > 0 && heightTop > 0) {
            auto lowR = make_pair(ul.first + widthEdge -1, ul.second + heightTop - 1);
            unsigned int area = widthEdge * heightTop;
            tree->A = BuildNode(img, ul, lowR);
            sumR   += tree->A->avg.r * area;
            sumG   += tree->A->avg.g * area;
            sumB   += tree->A->avg.b * area;
            accSum += tree->A->avg.a * area;
        }

        //B
        if (widthMiddle > 0 && heightTop > 0) {
            auto upLeft = make_pair(ul.first + widthEdge, ul.second);
            auto lowR   = make_pair(upLeft.first + widthMiddle - 1, upLeft.second + heightTop - 1);
            tree->B = BuildNode(img, upLeft, lowR);
            unsigned int area = widthMiddle * heightTop;
            sumR   += tree->B->avg.r * area;
            sumG   += tree->B->avg.g * area;
            sumB   += tree->B->avg.b * area;
            accSum += tree->B->avg.a * area;
        }

        //C
        if (widthEdge > 0 && heightTop > 0) {
            auto upLeft = make_pair(ul.first + widthEdge + widthMiddle, ul.second); 
            auto lowR   = make_pair(upLeft.first + widthEdge - 1, ul.second + heightTop - 1);
            unsigned int area = widthEdge * heightTop;
            tree->C = BuildNode(img, upLeft, lowR);
            sumR   += tree->C->avg.r * area;
            sumG   += tree->C->avg.g * area;
            sumB   += tree->C->avg.b * area;
            accSum += tree->C->avg.a * area;
        }

        //D 
        if(widthEdge > 0 && heightBot > 0) {
            auto upLeft = make_pair(ul.first, ul.second + heightTop);
            auto lowR   = make_pair(upLeft.first + widthEdge - 1, lr.second);
            unsigned int area = widthEdge * heightBot;
            tree->D = BuildNode(img, upLeft, lowR);
            sumR   += tree->D->avg.r * area;
            sumG   += tree->D->avg.g * area;
            sumB   += tree->D->avg.b * area;
            accSum += tree->D->avg.a * area;
        }

        //E
        if(widthMiddle > 0 && heightBot > 0) {
            auto upLeft = make_pair(ul.first + widthEdge, ul.second + heightTop);
            auto lowR   = make_pair(upLeft.first + widthMiddle - 1, lr.second);
            unsigned int area = widthMiddle * heightBot;
            tree->E = BuildNode(img, upLeft, lowR);
            sumR   += tree->E->avg.r * area;
            sumG   += tree->E->avg.g * area;
            sumB   += tree->E->avg.b * area;
            accSum += tree->E->avg.a * area;
        }

        //F
        if(widthEdge > 0 && heightBot > 0) {
            auto upLeft = make_pair(ul.first + widthEdge + widthMiddle, ul.second + heightTop);
            unsigned int area = widthEdge * heightBot;
            tree->F = BuildNode(img, upLeft, lr);
            sumR   += tree->F->avg.r * area;
            sumG   += tree->F->avg.g * area;
            sumB   += tree->F->avg.b * area;
            accSum += tree->F->avg.a * area;
        }

        unsigned int treeArea = width * height;
        tree->avg.r =   sumR / treeArea;
        tree->avg.g =   sumG / treeArea;
        tree->avg.b =   sumB / treeArea;
        tree->avg.a = accSum / treeArea;
    }
	return tree;
}

/*********************************************************/
/*** IMPLEMENT YOUR OWN PRIVATE MEMBER FUNCTIONS BELOW ***/
/*********************************************************/


// Helper methods for Building PNG file
pair<unsigned int, unsigned int> HexTree::getImageSize(const Node* child, bool fulldepth, unsigned int maxlevel) const {
    // Keep calling my recursion until child->F is null
    // OR I reached my maxlevel
    if(child->F != nullptr && (maxlevel > 0 || fulldepth)) {
        return getImageSize(child->F, fulldepth, (maxlevel - 1));
    }

    //Deals with the case where I hit my max depth
    if(maxlevel == 0 && !fulldepth) {
        return child->lowRight;
    }

    //Child->F == nullptr, so if all my pointers are nullptrs, then I know I reached the leaf Node
    if(child->A == nullptr && child->B == nullptr && child->C == nullptr &&
       child->D == nullptr && child->E == nullptr && child->F == nullptr) {
        return child->lowRight;
    }
    
    if(child->C != nullptr && (fulldepth || maxlevel > 0)) {
        return getImageSize(child->C, fulldepth, (maxlevel -1));
    }

    if(child->D != nullptr && (fulldepth || maxlevel > 0)) {
        return getImageSize(child->D, fulldepth, (maxlevel -1));
    }
    // Probably should never reach here, but who knows. maybe bug
    return child->lowRight;
}

void HexTree::buildImage(PNG& imageCanvas, bool fulldepth, unsigned int maxlevel, Node* child, unsigned int level) const {
    if (child == nullptr) {
        return;
    }

    bool isLeaf = (child->A == nullptr && child->B == nullptr && child->C == nullptr &&
                   child->D == nullptr && child->E == nullptr && child->F == nullptr);

    // Decide whether to color this node
    if (isLeaf || (!fulldepth && level >= maxlevel)) {
        for (unsigned int y = child->upLeft.second; y <= child->lowRight.second; y++) {
            for (unsigned int x = child->upLeft.first; x <= child->lowRight.first; x++) {
                RGBAPixel* nextPixel = imageCanvas.getPixel(x, y);
                *nextPixel = child->avg;
            }
        }
    } else {
        // Only recurse if fulldepth is true OR level < maxlevel
        if (child->A) buildImage(imageCanvas, fulldepth, maxlevel, child->A, level + 1);
        if (child->B) buildImage(imageCanvas, fulldepth, maxlevel, child->B, level + 1);
        if (child->C) buildImage(imageCanvas, fulldepth, maxlevel, child->C, level + 1);
        if (child->D) buildImage(imageCanvas, fulldepth, maxlevel, child->D, level + 1);
        if (child->E) buildImage(imageCanvas, fulldepth, maxlevel, child->E, level + 1);
        if (child->F) buildImage(imageCanvas, fulldepth, maxlevel, child->F, level + 1);
    }
}
    
    
    
    
    
    /*
    if(child == nullptr) {
        return;
    }

    // if a doesn't exist then nothing exists
    bool children = child->A != nullptr;

    if(children && (maxlevel > 0 || fulldepth)) {
        if(child->A != nullptr) buildImage(imageCanvas, child->A, fulldepth, (maxlevel - 1));
        if(child->B != nullptr) buildImage(imageCanvas, child->B, fulldepth, (maxlevel - 1));
        if(child->C != nullptr) buildImage(imageCanvas, child->C, fulldepth, (maxlevel - 1));
        if(child->D != nullptr) buildImage(imageCanvas, child->D, fulldepth, (maxlevel - 1));
        if(child->E != nullptr) buildImage(imageCanvas, child->E, fulldepth, (maxlevel - 1));
        if(child->F != nullptr) buildImage(imageCanvas, child->F, fulldepth, (maxlevel - 1));

    } 

    if(!children || (!fulldepth && maxlevel == 0)) {
        colourImage(imageCanvas, child);
    }
        */

/*
void HexTree::colourImage(PNG& imageCanvas, const Node* child) const {
    unsigned int xStart = child->upLeft.first;
    unsigned int yStart = child->upLeft.second;
    unsigned int xEnd   = child->lowRight.first;
    unsigned int yEnd   = child->lowRight.second;
    
    //Have the edge case where yStart == yEnd and xStart == yEnd.. Single pixel
    if(xStart == xEnd && yStart == yEnd) {
        updatePixel(imageCanvas, child, xStart, yStart);
        return;     
    }

    // One Row case
    if(xStart == xEnd) {
        for(unsigned int y = yStart; y <= yEnd; y++) {
            updatePixel(imageCanvas, child, xStart, y);
        }
        return;
    }

    // One Col
    if(yStart == yEnd) {
        for(unsigned int x = xStart; x <= xEnd; x++) {
            updatePixel(imageCanvas, child, x, yStart);
        }
        return;
    }

    //I am Filling a area from ul, to lr pixels in my child Node
    for(unsigned int y = yStart; y <= yEnd; y++) {
        for(unsigned int x = xStart; x <= xEnd; x++) {
            updatePixel(imageCanvas, child, x, y);
        }
    }
}
    */

void HexTree::updatePixel(PNG& imageCanvas, const Node* child, unsigned int x, unsigned int y) const {
        RGBAPixel* nextPixel = imageCanvas.getPixel(x, y);
        nextPixel->r = child->avg.r;
        nextPixel->g = child->avg.g;
        nextPixel->b = child->avg.b;
}


void HexTree::clearAllData(Node* child) {
    if(child == nullptr) {
        return;
    }
    
    clearAllData(child->A);
    clearAllData(child->B);
    clearAllData(child->C);
    clearAllData(child->D);
    clearAllData(child->E);
    clearAllData(child->F);
    
    delete child;
}

void HexTree::pruneTolerantChildren(Node* child, double tolerance) {
    
    if(child == nullptr) {
        return;
    }

    // I am not at the leaf, so I could check all my nodes
    bool shouldPrune = checkPrune(child, child->avg, tolerance);
    if(shouldPrune) {
        clearAllData(child->A);
        clearAllData(child->B);
        clearAllData(child->C);
        clearAllData(child->D);
        clearAllData(child->E);
        clearAllData(child->F);
        child->A = nullptr;
        child->B = nullptr;
        child->C = nullptr;
        child->D = nullptr;
        child->E = nullptr;
        child->F = nullptr;
    }
    if(!shouldPrune) {
        pruneTolerantChildren(child->A, tolerance);
        pruneTolerantChildren(child->B, tolerance);
        pruneTolerantChildren(child->C, tolerance);
        pruneTolerantChildren(child->D, tolerance);
        pruneTolerantChildren(child->E, tolerance);
        pruneTolerantChildren(child->F, tolerance);
    }
}

bool HexTree::checkPrune(Node* child, RGBAPixel average, double tolerance) {
    if(child == nullptr) {
        return true; 
    }

    //If all children are null, then I am at the leaf
    if(child->A == nullptr && child->B == nullptr && child->C == nullptr
    && child->D == nullptr && child->E == nullptr && child->F == nullptr) {
        return child->avg.distanceTo(average) <= tolerance;
        //return (average.distanceTo(child->avg) <= tolerance);
    }
    bool pruneA = checkPrune(child->A, average, tolerance);
    bool pruneB = checkPrune(child->B, average, tolerance);
    bool pruneC = checkPrune(child->C, average, tolerance);
    bool pruneD = checkPrune(child->D, average, tolerance);
    bool pruneE = checkPrune(child->E, average, tolerance);
    bool pruneF = checkPrune(child->F, average, tolerance);

    bool result = (pruneA && pruneB && pruneC && pruneD && pruneE && pruneF);
    return result;
}

Node* HexTree::copyHelper(const Node* other) {
    if(other == nullptr) {
        return nullptr;
    }

    Node* temp = new Node(other->upLeft, other->lowRight, other->avg);

    temp->A = copyHelper(other->A);
    temp->B = copyHelper(other->B);
    temp->C = copyHelper(other->C);
    temp->D = copyHelper(other->D);
    temp->E = copyHelper(other->E);
    temp->F = copyHelper(other->F);

    return temp;
}

void HexTree::flipper(Node* subRoot, unsigned int imageWidth) {
    if (subRoot == nullptr) {
        return;
    }
    
    // Calculate new UL and LR after horizontal flip
    unsigned int newX1 = imageWidth - subRoot->lowRight.first;
    unsigned int newX2 = imageWidth - subRoot->upLeft.first;
    subRoot->upLeft.first = newX1;
    subRoot->lowRight.first = newX2;
    
    // Swap A and C
    Node* temp = subRoot->A;
    subRoot->A = subRoot->C;
    subRoot->C = temp;
    
    // Swap D and F
    temp = subRoot->D;
    subRoot->D = subRoot->F;
    subRoot->F = temp;
    
    // Recursively flip all children
    flipper(subRoot->A, imageWidth);
    flipper(subRoot->B, imageWidth);
    flipper(subRoot->C, imageWidth);
    flipper(subRoot->D, imageWidth);
    flipper(subRoot->E, imageWidth);
    flipper(subRoot->F, imageWidth);
}

