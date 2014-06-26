#include "util.h"
#include "opencv2/highgui/highgui.hpp"


void fatalError(string message) {
    fprintf(stderr, "Fatal error: %s\n", message.c_str());
    exit(1);
}


vector<uchar> readFile(FILE *file) {
    int blockSize = 2000000;
    int capacity = blockSize;
    int pos = 0;
    vector<uchar> vec;
    vec.resize(capacity);
    while (fread(&((vec.data())[pos]), blockSize, 1, file) > 0) {
        capacity += blockSize;
        pos += blockSize;
        vec.resize(capacity);
    }
    return vec;
}


Mat decodeImage(vector<uchar> data, int flags) {
    Mat img = imdecode(data, flags);
    if (img.empty()) {
        fatalError("decoding image");
    }
    return img;
}


void writePNG(Mat img) {
    vector<int> compression_params;
    compression_params.push_back(CV_IMWRITE_PNG_COMPRESSION);
    compression_params.push_back(1);
    vector<uchar> vec;
    if (!imencode(".png", img, vec, compression_params)) {
        fatalError("encoding image");
    }
    if (fwrite(vec.data(), vec.size(), 1, stdout) != 1) {
        fatalError("writing image");
    }
}


Mat detectEdges(Mat gray, int threshold) {
    Mat edges;
    blur(gray, edges, Size(3, 3));
    Canny(edges, edges, threshold, threshold * 3, 3);
    return edges;
}


void fillToNorthwesternNeighbors(Mat mask, int fillSize) {
    if (!mask.isContinuous()) {
        fatalError("!mask.isContinuous()");
    }
    Size size = mask.size();
    uchar *pixels = mask.ptr(0);
    for (int y = 0; y < size.height; y++) {
        for (int x = 0; x < size.width; x++) {
            if (pixels[(y * size.width) + x]) {

                // Look leftwards
                for (int x2 = (x - 1); x2 >= max(0, x - fillSize); x2--) {
                    if (pixels[(y * size.width) + x2]) {
                        // Fill inbetween
                        for (int x3 = x2 + 1; x3 < x; x3++) {
                            pixels[(y * size.width) + x3] = 0xFF;
                        }
                        break;
                    }
                }

                // Fill upwards
                for (int y2 = (y - 1); y2 >= max(0, y - fillSize); y2--) {
                    if (pixels[(y2 * size.width) + x]) {
                        // Fill inbetween
                        for (int y3 = y2 + 1; y3 < y; y3++) {
                            pixels[(y3 * size.width) + x] = 0xFF;
                        }
                        break;
                    }
                }
            }
        }
    }
}
