/**
 * @file filler_private.h
 * @description student declarations of private functions
 *              for Filler, CPSC 221 PA2
 *
 *              THIS FILE WILL BE SUBMITTED.
 *
 *              Simply declare your function prototypes here.
 *              No other scaffolding is necessary.
 */

 // begin your declarations below
 


int getColourDistance(const RGBAPixel seed, const RGBAPixel* nextPixel);


int getColourDistance(const RGBAPixel seed, const RGBAPixel* nextPixel);

void configureVectorSpace(vector<vector<bool>> &vector, const PNG img);

void markSeen(vector<vector<bool>>& vector, unsigned int x, unsigned int y);

void updateImage(PNG& img, pair<unsigned int, unsigned int> cords, ColourPicker* picker);

void addValidNeighborPixels(
    OrderingStructure<pair<unsigned int, unsigned int>>& os,
    pair<unsigned int, unsigned int> oldPair,
    PNG& img,
    double tolerance,
    RGBAPixel seed,
    vector<vector<bool>>& sawPixel);

bool isValidPixel(
    RGBAPixel* nextPixel, 
    double tolerance, 
    RGBAPixel seed);

