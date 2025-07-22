/**
 * @file        filler.cpp
 * @description Implementation of functions in the filler namespace.
 *
 *              SUBMIT THIS FILE WITH YOUR MODIFICATIONS
 */

/**
 * Performs a flood fill using breadth first search.
 *
 * @param config FillerConfig struct to setup the fill
 * @return animation object illustrating progression of flood fill algorithm
 */
animation filler::FillBFS(FillerConfig& config) {
    /*
    for(int x = 0; x < 30; x++) {
       cout << "-----------ooooooooooooooooooooo--------------" << endl; 
    }
       */
    return Fill<Queue>(config);
	// complete your implementation below
	// You should replace the following line with a
	// correct call to fill.
    //return animation();
}

/**
 * Performs a flood fill using depth first search.
 *
 * @param  config - FillerConfig struct to setup the fill
 * @return animation object illustrating progression of flood fill algorithm
 */
animation filler::FillDFS(FillerConfig& config) {
    return Fill<Stack>(config);
    //Fill<stack>(config);

	// complete your implementation below
	// You should replace the following line with a
	// correct call to fill.
	//return animation(); // REPLACE THIS STUB
}

/**
 * Run a flood fill on an image starting at the seed point
 *
 * @param config FillerConfig struct with data for flood fill of image
 * @return animation object illustrating progression of flood fill algorithm
 */
template <template <class T> class OrderingStructure> animation filler::Fill(FillerConfig& config) {
	// Variables
    animation anim;
    PNG img = config.img;
    //double tolerance = config.tolerance;
    RGBAPixel seedcolour = config.seedcolour;
    int frameFreq = config.frameFreq;
    int frameCounter = 0;

    // Sets up lookup map
    unsigned int imgWidth = img.width();
    unsigned int imgHeight = img.height();
    vector<vector<bool>> sawPixel;
    sawPixel.resize(imgWidth);
    for(unsigned int x = 0; x < imgWidth; x++) {
        sawPixel[x].resize(imgHeight, false);
    }
    
    // Starting seed cords <x, y>
    unsigned int orgX = config.seedpoint.first;
    unsigned int orgY = config.seedpoint.second;

    //Setup the Structure base case
    OrderingStructure<pair<unsigned int, unsigned int>> OS;

    sawPixel[orgX][orgY] = true;
    OS.Add(config.seedpoint);
    
    
    
    while(!OS.IsEmpty()) {
        // I have my next pixel.
        pair<unsigned int, unsigned int> nextPixelCoord = OS.Remove();
        unsigned int x = nextPixelCoord.first;
        unsigned int y = nextPixelCoord.second;

        *img.getPixel(x, y) = (*config.picker)(nextPixelCoord);
        frameCounter++;

        if(frameCounter % frameFreq == 0) {
            anim.addFrame(img);      
        }

        /*	 
        *        1.1.  add its unprocessed neighbors (up/down/left/right) whose color values are
        *              within (or equal to) tolerance distance from the seed point,
        *              to the ordering structure, and
        *              mark them as processed.
        *        1.2.  if it is an appropriate frame, send the current PNG to the
	    *              animation (as described below).
        */

        // Array Map grabs Pixels UP, DOWN, LEFT, RIGHT 
        int xAdjMap[] = {0, 0, -1, 1};
        int yAdjMap[] = {1, -1, 0, 0};

        // Going to itereate over the range of ADJ pixels using my Array Map
        for(int z = 0; z < 4; z++) {

            // Grabs the next ADJ pixel coords 
            int TempnextX = (int) x + xAdjMap[z];
            int TempnextY = (int) y + yAdjMap[z];
            

            // Edge case: What happends if I am off the edge of the image? 
            // Solution is probably check to see if I am off the edge and then continue if I am.

            if(TempnextX < 0 || TempnextY < 0) {
                continue;
            }
            
            unsigned int nextX = (unsigned int) TempnextX;
            unsigned int nextY = (unsigned int) TempnextY;

            
            if(nextX >= imgWidth || nextY >= imgHeight) {
                continue;
            }

            // Edge Case: If the pixel has already been looked at go to the next one
            if(sawPixel[nextX][nextY]) {
                continue;
            }

            
            
            RGBAPixel* adjPixel = img.getPixel(nextX, nextY);
            //Grabs the distance and if it meets the tolerance value add it to the Stack/Queue
            //Marks it as seen and update frame counter
            if(adjPixel->distanceTo(config.seedcolour) <= config.tolerance) {
                sawPixel[nextX][nextY] = true;
                OS.Add(make_pair(nextX, nextY));
            }

            /* 
            * 3.     For every k pixels filled, **starting at the kth pixel**, you
            *        must add a frame to the animation, where k = frameFreq.
            *
            *        For example, if frameFreq is 4, then after the 4th pixel has
            *        been filled you should add a frame to the animation, then again
            *        after the 8th pixel, etc.  You must only add frames for the
            *        number of pixels that have been filled, not the number that
            *        have been checked. So if frameFreq is set to 1, a pixel should
            *        be filled every frame.
            *
            */

            //Checks to see if it's time to update my animation
        }
    }

    
    /**
	 * You need to implement this function!
	 *
	 * This is the basic description of a flood-fill algorithm: Every fill
	 * algorithm requires an ordering structure, which is passed to this
	 * function via its template parameter. For a breadth-first-search
	 * fill, that structure is a Queue, for a depth-first-search, that
	 * structure is a Stack. To begin the algorithm, you simply place the
	 * given point in the ordering structure, marking it processed
	 * (the way you mark it is a design decision you'll make yourself).
	 * We have a choice to either change the color, if appropriate, when we
	 * add the point to the OS, or when we take it off. In our test cases,
	 * we have assumed that you will change the color when a point is removed
	 * from the structure.
	 * Until the structure is empty, you do the following:
	 *
	 * 1.     Remove a point from the ordering structure, and then...
	 *
	 *        1.1.  add its unprocessed neighbors (up/down/left/right) whose color values are
	 *              within (or equal to) tolerance distance from the seed point,
	 *              to the ordering structure, and
	 *              mark them as processed.
	 *        1.2.  if it is an appropriate frame, send the current PNG to the
	 *              animation (as described below).
	 *
	 * 2.     When implementing your breadth-first-search and
	 *        depth-first-search fills, you will need to explore neighboring
	 *        pixels (up/down/left/right) in some order.
	 *
	 *        While the order in which you examine neighbors does not matter
	 *        for a proper fill, you must use the same order as we do for
	 *        your animations to come out like ours! The order you should put
	 *        neighboring pixels **ONTO** the queue or stack is as follows:
	 *        2.1. northern neighbour (up)
	 *        2.2. southern neighbour (down)
	 *        2.3. western neighbour (left)
	 *        2.4. eastern neighbour (right)
	 * 
	 *        If you process the neighbours in a different order, your fill may
	 *        still work correctly, but your animations will be different
	 *        from the grading scripts!
	 *
	 * 3.     For every k pixels filled, **starting at the kth pixel**, you
	 *        must add a frame to the animation, where k = frameFreq.
	 *
	 *        For example, if frameFreq is 4, then after the 4th pixel has
	 *        been filled you should add a frame to the animation, then again
	 *        after the 8th pixel, etc.  You must only add frames for the
	 *        number of pixels that have been filled, not the number that
	 *        have been checked. So if frameFreq is set to 1, a pixel should
	 *        be filled every frame.
	 *
	 * 4.     Finally, as you leave the function, send one last frame to the
	 *        animation. This frame will be the final result of the fill, and
	 *        it will be the one we test against.
	 *
	 */
	
    anim.addFrame(img);
	return anim;
}
