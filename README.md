# CPSC221-Data-Structures-and-algorithms
Three programming Assignments for cpsc 221 Data Structures and Algoithms. The code is written in and older version of C++

Each of the three Programming Assignments (PAs) provided students with template code that we were required to complete. The files in which I wrote my code are listed under each PA section. Only the files listed in their respective sections contain code that I personally wrote. Each PA was designed to help us build a foundational understanding of memory management and apply the concepts learned in class. Some files are labeled as `private`; these were intended for students to include any helper methods and were the required destination for such methods. 

Each PA also includes a "backup" folder, which contains all the required files for the program to run. There is also a "answer" file that contains just the files that I wrote my code in. 

# Running the files
1| Drag and drop the "answer" files into the "backup" file
2| Compile the files and run.

# Checking the output
The files should contain three files: `image-orig`, `images-soln` and a `image-output` file. The image-org will contain the original image and the image-soln will show the desired output for the image. When the code is ran the image that gets ran in the program will be contained in the `image-output` file.

# PA1: Linked List
Discription of assignment: Given an image, the image must flip the pixels horizontally, render the average pixel colour in a preset block size and resize the image. Note that the resize image will show an image that looks incorrect, but that is the desired effect. See Image-soln to see the desired effects. 

  - block.cpp
  - chain.cpp
  - chain-private.h

# PA2: Breath first Search and Depth first search 

GeneralDiscription of assignment: Implements a flood-fill algorithm using a templated ordering structure (e.g., a stack for DFS or a queue for BFS). Starting from a seed point, it processes pixels by adding unprocessed neighbors (up, down, left, right) within a specified color tolerance, marking them as processed, and changing their color upon removal from the structure. Neighbors must be added in a fixed order (north, south, west, east) to match the expected animation output. A frame is added to the animation every k filled pixels (frameFreq), with a final frame added at the end.

  - stack.cpp
  - queue.cpp
  - photoNegativeColourPicker.cpp
  - photoNegativeColourPicker-private.h
  - edgeColourPicker.cpp
  - edgeColourPicker-private
  - stripeColourPicker.cpp
  - stripeColourPicker-private.h
  - filler.cpp
  - filler-private.h

#PA3: Hextree image compression.
Discription of assignment: This project involves implementing a HexTree constructor that recursively builds a tree from a PNG image. Each node represents a rectangular region of pixels, storing the region's average color (computed in constant time), and subdivides into up to six child regions based on specific splitting rules. Leaf nodes correspond to individual pixels, while internal nodes represent progressively larger regions of the image. The splitting ensures full, non-overlapping coverage of the original image.

  - Hextree.cpp
  - Hextree-private.h
  
