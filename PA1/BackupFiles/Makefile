EXEMAIN = pa1
OBJS  = main.o PNG.o RGBAPixel.o lodepng.o chain.o chain-given.o block.o

CXX = clang++
CXXFLAGS = -std=c++14 -c -g -O0 -Wall -Wextra -pedantic -Wno-deprecated-copy
LD = clang++
LDFLAGS = -std=c++14 -lpthread -lm

all : pa1

$(EXEMAIN) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXEMAIN)

main.o : main.cpp chain.h cs221util/PNG.h cs221util/RGBAPixel.h block.h
	$(CXX) $(CXXFLAGS) main.cpp

chain.o : chain.cpp chain.h chain-private.h block.h
	$(CXX) $(CXXFLAGS) chain.cpp

chain-given.o: chain-given.cpp chain.h chain-private.h block.h
	$(CXX) $(CXXFLAGS) chain-given.cpp

block.o : block.cpp block.h cs221util/PNG.h cs221util/RGBAPixel.h cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) block.cpp

PNG.o : cs221util/PNG.cpp cs221util/PNG.h cs221util/RGBAPixel.h cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/PNG.cpp

RGBAPixel.o : cs221util/RGBAPixel.cpp cs221util/RGBAPixel.h
	$(CXX) $(CXXFLAGS) cs221util/RGBAPixel.cpp

lodepng.o : cs221util/lodepng/lodepng.cpp cs221util/lodepng/lodepng.h
	$(CXX) $(CXXFLAGS) cs221util/lodepng/lodepng.cpp

clean :
	-rm -f *.o $(EXEMAIN)
