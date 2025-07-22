/**
 * @file hextree-private.h
 * @description student declaration of private HexTree functions
 *              CPSC 221 PA3
 *
 *              SUBMIT THIS FILE.
 *
 *				Simply declare your function prototypes here.
 *              No other scaffolding is necessary.
 */

 // begin your declarations below

pair<unsigned int, unsigned int> getImageSize(const Node* child, bool fulldepth, unsigned int maxlevel) const;

void buildImage(PNG& imageCanvas, bool fulldepth, unsigned int maxlevel, Node* child, unsigned int level) const;

void colourImage(PNG& imageCanvas, const Node* child) const;

void updatePixel(PNG& imageCanvas, const Node* child, unsigned int x, unsigned int y) const;

/// Delete data helper function
void clearAllData(Node* child);

/// Prune Function
void pruneTolerantChildren(Node* child, double tolerance);

bool checkPrune(Node* child, RGBAPixel average, double tolerance);


Node* copyHelper(const Node* other);

void flipper(Node* child, unsigned int width);