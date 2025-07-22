	/**
 * @file main.cpp
 * @description Basic tests for Chain class, CPSC 221 PA1
 *              You should modify these tests with different parameters,
 *              or add your own.
 * 
 *              Note that simply passing the PNG comparison checks does
 *              not guarantee that your code functions correctly according
 *              to the required specifications.
 *              Pay special attention to the way your nodes are linked;
 *              we will be testing the integrity of your pointers.
 * 
 *              This file will not be submitted.
 */

#include <iostream>

#include "chain.h"

using namespace std;

/**
 * Program entry point
 */
int main(int argc, char* argv[]) {
	// create a new list using input image
	PNG img_in;
	img_in.readFromFile("images-orig/asv-256x224.png");

	int rows = 14; // feel free to change these values
	int cols = 16; // but make sure your image dimensions are divisible
	cout << "Constructing list from image with " << rows << " rows and " << cols << " columns... ";
	Chain testchain(img_in, rows, cols);
	cout << "done." << endl;

	// render chain to output image
	cout << "Rendering to output image with " << cols << " columns and original pixel colours... ";
	PNG img_out = testchain.Render(cols, false);
	img_out.writeToFile("images-output/asv-render-normal-false.png");
	cout << "done." << endl;

	cout << "Comparing your PNG with expected PNG... ";
	PNG img_ex_normal;
	img_ex_normal.readFromFile("images-soln/soln-asv-render-normal-false.png");
	if (img_out != img_ex_normal)
		cout << "Rendered PNG does not match expected PNG." << endl;
	else
		cout << "OK." << endl;

	// render chain to output image using average colour
	cout << "Rendering to output image with " << cols << " columns and average block colour... ";
	PNG img_out_avg = testchain.Render(cols, true);
	img_out_avg.writeToFile("images-output/asv-render-normal-true.png");
	cout << "done." << endl;

	cout << "Comparing your PNG with expected PNG... ";
	PNG img_ex_avg;
	img_ex_avg.readFromFile("images-soln/soln-asv-render-normal-true.png");
	if (img_out_avg != img_ex_avg)
		cout << "Rendered PNG does not match expected PNG." << endl;
	else
		cout << "OK." << endl;

	// render chain to output image with "incorrect" number of columns
	cout << "Rendering to output image with " << cols + 2 << " columns and original pixel colours... ";
	PNG img_out_plus2 = testchain.Render(cols + 2, false);
	img_out_plus2.writeToFile("images-output/asv-render-plus2-false.png");
	cout << "done." << endl;

	cout << "Comparing your PNG with expected PNG... ";
	PNG img_ex_plus2;
	img_ex_plus2.readFromFile("images-soln/soln-asv-render-plus2-false.png");
	if (img_out_plus2 != img_ex_plus2)
		cout << "Rendered PNG does not match expected PNG." << endl;
	else
		cout << "OK." << endl;

	// flip the chain with "correct" number of columns and render
	cout << "Calling FlipHorizontal with " << cols << " columns... ";
	testchain.FlipHorizontal(cols);
	cout << "done." << endl;

	// render flipped chain to output image
	cout << "Rendering flipped chain to output image with " << cols << " columns and original pixel colours... ";
	PNG img_out_fh = testchain.Render(cols, false);
	img_out_fh.writeToFile("images-output/asv-render-fh-false.png");
	cout << "done." << endl;

	cout << "Comparing your PNG with expected PNG... ";
	PNG img_ex_fh;
	img_ex_fh.readFromFile("images-soln/soln-asv-render-fh-false.png");
	if (img_out_fh != img_ex_fh)
		cout << "Rendered PNG does not match expected PNG." << endl;
	else
		cout << "OK." << endl;

	return 0;
}