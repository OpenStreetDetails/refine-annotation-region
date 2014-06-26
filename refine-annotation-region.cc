#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "util.h"

using namespace cv;
using namespace std;


int main(int argc, const char **argv)  {

    Mat gray = decodeImage(readFile(stdin), CV_LOAD_IMAGE_GRAYSCALE);
    Mat edges = detectEdges(gray, 45);
    fillToNorthwesternNeighbors(edges, max(gray.rows, gray.cols) / 3);
    writePNG(edges);

    return 0;
}
