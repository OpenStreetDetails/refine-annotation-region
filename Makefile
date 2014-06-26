all:
	mkdir -p build
	g++ -Wall -O3 `pkg-config --libs opencv` -o build/refine-annotation-region refine-annotation-region.cc util.cc
