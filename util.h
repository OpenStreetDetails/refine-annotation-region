#include "opencv2/imgproc/imgproc.hpp"
#include <stdio.h>

using namespace cv;
using namespace std;

void fatalError(string message);
vector<uchar> readFile(FILE *file);
Mat decodeImage(vector<uchar> data, int flags);
void writePNG(Mat image);
Mat detectEdges(Mat gray, int threshold);
void fillToNorthwesternNeighbors(Mat mask, int fillSize);
