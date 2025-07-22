#define CATCH_CONFIG_MAIN
#include "cs221util/catch.hpp"
#include <limits.h>
#include <vector>
#include <sys/stat.h>
#include <iostream>
#include "cs221util/PNG.h"
#include "cs221util/RGBAPixel.h"
#include "filler.h"
#include "solidColourPicker.h"
#include "stripeColourPicker.h"
#include "photoNegativeColourPicker.h"
#include "edgeColourPicker.h"
#include "colourPicker.h"

using namespace std;
using namespace cs221util;

#define IMAGEDIR "images-orig/"
#define SOLNIMGDIR "images-soln/"

#define FUNCTORTESTHEIGHT 300
#define FUNCTORTESTWIDTH 300
#define FUNCTORTESTFREQ 10
#define FUNCTORTESTX 40
#define FUNCTORTESTY 10
#define FUNCTORTESTRADIUS 45
#define FUNCTORTESTIMAGEW "images-orig/white-300x300.png"
#define FUNCTORTESTIMAGEP "images-orig/mr-300x300.png"

#define SOLIDX 119
#define SOLIDY 31
#define SOLIDTOLERANCE 0.05
#define SOLIDTESTIMAGE "images-orig/mr-300x300.png"
#define SOLIDFRAMEFREQ 70

#define STRIPEX 54 
#define STRIPEY 50
#define STRIPETOLERANCE 0.25
#define STRIPETESTIMAGE "images-orig/ibr-d-150x250.png"
#define STRIPEWIDTH 15
#define STRIPEFRAMEFREQ 180

#define PHOTONEGATIVEX 128
#define PHOTONEGATIVEY 102
#define PHOTONEGATIVETOLERANCE 0.1
#define PHOTONEGATIVETESTIMAGE "images-orig/mr-300x300.png"
#define PHOTONEGATIVEFRAMEFREQ 80

#define EDGEX 203
#define EDGEY 159
#define EDGETOLERANCE 0.25
#define EDGEWIDTH 6
#define EDGETESTIMAGE "images-orig/mr-300x300.png"
#define EDGEFRAMEFREQ 160

/**
 * Applies the ColourPicker's operator() to every pixel in the test image.
 * No flood fill is performed.
 */
PNG testColourPicker(ColourPicker& picker)
{
    PNG img;
    img.resize(FUNCTORTESTWIDTH, FUNCTORTESTHEIGHT);
    RGBAPixel px;

    for (unsigned int x = 0; x < FUNCTORTESTWIDTH; x++){
        for (unsigned int y = 0; y < FUNCTORTESTHEIGHT; y++){
            RGBAPixel* p = img.getPixel(x,y);
            *p = picker(pair<unsigned int, unsigned int>(x, y));
        }
    }

    return img;
}

TEST_CASE("colourPicker::basic solid","[weight=0][part=colourPicker]"){

    cout << "Entered colourPicker::basic solid..." << endl;

    RGBAPixel px(0, 255, 0); // green
    SolidColourPicker solidPicker(px);

    PNG result = testColourPicker(solidPicker);// result.convert();
    result.writeToFile("images-output/solidColourPickerTest.png");
    PNG expected; expected.readFromFile("images-soln/ex-solidColourPickerTest.png");
    REQUIRE(result == expected);
    
    cout << "Leaving colourPicker::basic solid..." << endl;
}

TEST_CASE("colourPicker::basic stripe","[weight=1][part=colourPicker]"){

    cout << "Entered colourPicker::basic stripe..." << endl;

    PNG imgtest, imgother;
    imgtest.readFromFile(STRIPETESTIMAGE);

    StripeColourPicker stripePicker(STRIPEWIDTH, RGBAPixel(255, 96, 96), RGBAPixel(255, 196, 196));

    PNG result = testColourPicker(stripePicker);// result.convert();
    result.writeToFile("images-output/stripeColourPickerTest.png");
    PNG expected; expected.readFromFile("images-soln/ex-stripeColourPickerTest.png");
    REQUIRE(result == expected);

    cout << "Leaving colourPicker::basic stripe..." << endl;
}

TEST_CASE("colourPicker::basic photonegative","[weight=1][part=colourPicker]"){
    
    cout << "Entered colourPicker::basic photonegative..." << endl;

    PNG imgtest;
    imgtest.readFromFile(FUNCTORTESTIMAGEP);

    PhotoNegativeColourPicker photoNegativePicker(imgtest);

    PNG result = testColourPicker(photoNegativePicker);// result.convert();
    result.writeToFile("images-output/photoNegativeColourPickerTest.png");
    PNG expected; expected.readFromFile("images-soln/ex-photoNegativeColourPickerTest.png");// expected.convert();
    REQUIRE(result == expected);

    cout << "Leaving colorPicker::basic photonegative..." << endl;
}

TEST_CASE("colourPicker::basic edge", "[weight=1][part=colourPicker]") {
  
    cout << "Entered colourPicker::basic edge..." << endl;

    PNG imgtest;
    imgtest.readFromFile(FUNCTORTESTIMAGEW);
    EdgeColourPicker edgePicker(EDGEWIDTH, imgtest, *(imgtest.getPixel(EDGEX, EDGEY)), RGBAPixel(0, 255, 0), EDGETOLERANCE);

    PNG result = testColourPicker(edgePicker);// result.convert();
    result.writeToFile("images-output/edgeColourPickerTest.png");
    PNG expected; expected.readFromFile("images-soln/ex-edgeColourPickerTest.png");
    REQUIRE(result == expected);

    cout << "Leaving colourPicker::basic edge..." << endl;
}

TEST_CASE("fill::basic solid dfs","[weight=1][part=fill]"){
    
    cout << "Entered fill::basic solid dfs..." << endl;

    RGBAPixel px(188, 212, 174);
    SolidColourPicker solidPicker(px);

    filler::FillerConfig solidconfig;
    solidconfig.img.readFromFile(SOLIDTESTIMAGE);
    solidconfig.frameFreq = SOLIDFRAMEFREQ;
    solidconfig.tolerance = SOLIDTOLERANCE;
    solidconfig.seedpoint = pair<unsigned int, unsigned int>(SOLIDX, SOLIDY);
    solidconfig.seedcolour = *(solidconfig.img.getPixel(SOLIDX, SOLIDY));
    solidconfig.picker = &solidPicker;

    animation anim;
    anim = filler::FillDFS(solidconfig);
    PNG result = anim.write("images-output/dfssolid.gif");//  result.convert();
    result.writeToFile("images-output/dfssolid.png");

    PNG expected; expected.readFromFile("images-soln/ex-dfssolid.png");
    REQUIRE(result==expected);

    cout << "Leaving fill::basic solid dfs..." << endl;
}


TEST_CASE("fill::basic solid bfs","[weight=1][part=fill]"){
    
    cout << "Entered fill::basic solid bfs..." << endl;

    RGBAPixel px(188, 212, 174);
    SolidColourPicker solidPicker(px);

    filler::FillerConfig solidconfig;
    solidconfig.img.readFromFile(SOLIDTESTIMAGE);
    solidconfig.frameFreq = SOLIDFRAMEFREQ;
    solidconfig.tolerance = SOLIDTOLERANCE;
    solidconfig.seedpoint = pair<unsigned int, unsigned int>(SOLIDX, SOLIDY);
    solidconfig.seedcolour = *(solidconfig.img.getPixel(SOLIDX, SOLIDY));
    solidconfig.picker = &solidPicker;

    animation anim;
    anim = filler::FillBFS(solidconfig);
    PNG result = anim.write("images-output/bfssolid.gif");// result.convert();
    result.writeToFile("images-output/bfssolid.png");

    PNG expected; expected.readFromFile("images-soln/ex-bfssolid.png");
    REQUIRE(result==expected);

    cout << "Leaving fill::basic solid bfs..." << endl;
}

TEST_CASE("fill::basic stripe dfs", "[weight=1][part=fill]") {
    
    cout << "Entered fill::basic stripe dfs..." << endl;

    PNG stripetest;
    stripetest.readFromFile(STRIPETESTIMAGE);
    StripeColourPicker stripePicker(STRIPEWIDTH, RGBAPixel(255, 96, 96), RGBAPixel(255, 196, 196));

    filler::FillerConfig stripeconfig;
    stripeconfig.img = stripetest;
    stripeconfig.frameFreq = STRIPEFRAMEFREQ;
    stripeconfig.tolerance = STRIPETOLERANCE;
    stripeconfig.seedpoint = pair<unsigned int, unsigned int>(STRIPEX, STRIPEY);
    stripeconfig.seedcolour = *(stripeconfig.img.getPixel(STRIPEX, STRIPEY));
    stripeconfig.picker = &stripePicker;

    animation anim;
    anim = filler::FillDFS(stripeconfig);
    PNG result = anim.write("images-output/dfsstripe.gif");// result.convert();
    result.writeToFile("images-output/dfsstripe.png");

    PNG expected; expected.readFromFile("images-soln/ex-dfsstripe.png");
    REQUIRE(result == expected);

    cout << "Leaving fill::basic stripe dfs..." << endl;
}

TEST_CASE("fill::basic stripe bfs", "[weight=1][part=fill]") {
  
    cout << "Entered fill::basic stripe bfs..." << endl;

    PNG stripetest;
    stripetest.readFromFile(STRIPETESTIMAGE);
    StripeColourPicker stripePicker(STRIPEWIDTH, RGBAPixel(255, 96, 96), RGBAPixel(255, 196, 196));

    filler::FillerConfig stripeconfig;
    stripeconfig.img = stripetest;
    stripeconfig.frameFreq = STRIPEFRAMEFREQ;
    stripeconfig.tolerance = STRIPETOLERANCE;
    stripeconfig.seedpoint = pair<unsigned int, unsigned int>(STRIPEX, STRIPEY);
    stripeconfig.seedcolour = *(stripeconfig.img.getPixel(STRIPEX, STRIPEY));
    stripeconfig.picker = &stripePicker;

    animation anim;
    anim = filler::FillBFS(stripeconfig);
    PNG result = anim.write("images-output/bfsstripe.gif");// result.convert();
    result.writeToFile("images-output/bfsstripe.png");

    PNG expected; expected.readFromFile("images-soln/ex-bfsstripe.png");
    REQUIRE(result == expected);

    cout << "Leaving fill::basic stripe bfs..." << endl;
}

TEST_CASE("fill::basic photonegative dfs","[weight=1][part=fill]"){
    
    cout << "Entered fill::basic photonegative dfs..." << endl;

    PNG photonegativetest;
    photonegativetest.readFromFile(PHOTONEGATIVETESTIMAGE);
    PhotoNegativeColourPicker photoNegativePicker(photonegativetest);

    filler::FillerConfig photonegativeconfig;
    photonegativeconfig.img = photonegativetest;
    photonegativeconfig.frameFreq = PHOTONEGATIVEFRAMEFREQ;
    photonegativeconfig.tolerance = PHOTONEGATIVETOLERANCE;
    photonegativeconfig.seedpoint = pair<unsigned int, unsigned int>(PHOTONEGATIVEX, PHOTONEGATIVEY);
    photonegativeconfig.seedcolour = *(photonegativeconfig.img.getPixel(PHOTONEGATIVEX, PHOTONEGATIVEY));
    photonegativeconfig.picker = &photoNegativePicker;

    animation anim;
    anim = filler::FillDFS(photonegativeconfig);
    PNG result = anim.write("images-output/dfsphotonegative.gif");// result.convert();
    result.writeToFile("images-output/dfsphotonegative.png");

    PNG expected; expected.readFromFile("images-soln/ex-dfsphotonegative.png");
    REQUIRE(result==expected);

    cout << "Leaving fill::basic photonegative dfs..." << endl;
}

TEST_CASE("fill::basic photonegative bfs","[weight=1][part=fill]"){
    
    cout << "Entered fill::basic photonegative bfs..." << endl;

    PNG photonegativetest;
    photonegativetest.readFromFile(PHOTONEGATIVETESTIMAGE);
    PhotoNegativeColourPicker photoNegativePicker(photonegativetest);

    filler::FillerConfig photonegativeconfig;
    photonegativeconfig.img = photonegativetest;
    photonegativeconfig.frameFreq = PHOTONEGATIVEFRAMEFREQ;
    photonegativeconfig.tolerance = PHOTONEGATIVETOLERANCE;
    photonegativeconfig.seedpoint = pair<unsigned int, unsigned int>(PHOTONEGATIVEX, PHOTONEGATIVEY);
    photonegativeconfig.seedcolour = *(photonegativeconfig.img.getPixel(PHOTONEGATIVEX, PHOTONEGATIVEY));
    photonegativeconfig.picker = &photoNegativePicker;

    animation anim;
    anim = filler::FillBFS(photonegativeconfig);
    PNG result = anim.write("images-output/bfsphotonegative.gif");// result.convert();
    result.writeToFile("images-output/bfsphotonegative.png");

    PNG expected; expected.readFromFile("images-soln/ex-bfsphotonegative.png");
    REQUIRE(result == expected);

    cout << "Leaving fill::basic photonegative bfs..." << endl;
}

TEST_CASE("fill::basic edge dfs","[weight=1][part=fill]"){
  
    cout << "Entered fill::basic edge dfs..." << endl;
  
    PNG imgtest;
    imgtest.readFromFile(EDGETESTIMAGE);
    EdgeColourPicker edgePicker(EDGEWIDTH, imgtest, *(imgtest.getPixel(EDGEX, EDGEY)), RGBAPixel(0, 255, 0), EDGETOLERANCE);

    filler::FillerConfig edgeconfig;
    edgeconfig.img = imgtest;
    edgeconfig.frameFreq = EDGEFRAMEFREQ;
    edgeconfig.tolerance = EDGETOLERANCE;
    edgeconfig.seedpoint = pair<unsigned int, unsigned int>(EDGEX, EDGEY);
    edgeconfig.seedcolour = *(edgeconfig.img.getPixel(EDGEX, EDGEY));
    edgeconfig.picker = &edgePicker;

    animation anim;
    anim = filler::FillDFS(edgeconfig);
    PNG result = anim.write("images-output/dfsedge.gif");// result.convert();
    result.writeToFile("images-output/dfsedge.png");

    PNG expected; expected.readFromFile("images-soln/ex-dfsedge.png");
    REQUIRE(result==expected);

    cout << "Leaving fill::basic edge dfs..." << endl;
}

TEST_CASE("fill::basic edge bfs","[weight=1][part=fill]"){
  
    cout << "Entered fill::basic edge bfs..." << endl;

    PNG imgtest;
    imgtest.readFromFile(EDGETESTIMAGE);
    EdgeColourPicker edgePicker(EDGEWIDTH, imgtest, *(imgtest.getPixel(EDGEX, EDGEY)), RGBAPixel(0, 255, 0), EDGETOLERANCE);

    filler::FillerConfig edgeconfig;
    edgeconfig.img = imgtest;
    edgeconfig.frameFreq = EDGEFRAMEFREQ;
    edgeconfig.tolerance = EDGETOLERANCE;
    edgeconfig.seedpoint = pair<unsigned int, unsigned int>(EDGEX, EDGEY);
    edgeconfig.seedcolour = *(edgeconfig.img.getPixel(EDGEX, EDGEY));
    edgeconfig.picker = &edgePicker;

    animation anim;
    anim = filler::FillBFS(edgeconfig);
    PNG result = anim.write("images-output/bfsedge.gif");// result.convert();
    result.writeToFile("images-output/bfsedge.png");

    PNG expected; expected.readFromFile("images-soln/ex-bfsedge.png");
    REQUIRE(result == expected);

    cout << "Leaving fill::basic edge bfs..." << endl;
}
