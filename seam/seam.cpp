#include <cassert>
#include <limits>
#include <tgmath.h>
#include <vector>

#include "seam.h"

using namespace std;

// ***********************************
// TASK 1: COLOR
// ***********************************

// Returns red component (in the scale 0.0-1.0) from given RGB color.
double get_red(int rgb){
    int r0 = rgb >> 16;
    int r = r0 & 0b11111111;
    double doubleR = r / 255.00;
return doubleR;
}

// Returns green component (in the scale 0.0-1.0) from given RGB color.
double get_green(int rgb) {
    int g0 = rgb >> 8;
    int g = g0 & 0b11111111;
    double doubleG = g / 255.00;
return doubleG;
}

// Returns blue component (in the scale 0.0-1.0) from given RGB color.
double get_blue(int rgb){
    int b = rgb & 0b11111111;
    double doubleB = b / 255.00;
return doubleB; 
}

// Returns the average of red, green and blue components from given RGB color. (Scale: 0.0-1.0)
double get_gray(int rgb) {
    double gray = (get_red(rgb) + get_green(rgb) + get_blue(rgb)) / 3;
return gray;
}

// Returns the RGB value of the given red, green and blue components.
int get_RGB(double red, double green, double blue){
    int r0(red * 255), g0(green * 255), b0(blue * 255);
    int bin_RGB = 0b00000000;
    bin_RGB = (bin_RGB << 8) + r0; 
    bin_RGB = (bin_RGB << 8) + g0;
    bin_RGB = (bin_RGB << 8) + b0;
return bin_RGB;
}

// Returns the RGB components from given grayscale value (between 0.0 and 1.0).
int get_RGB(double gray){
    int colour0 = (gray / 3) * 255;
    int bin_RGB = 0b00000000;
    bin_RGB = (bin_RGB << 8) + colour0; 
    bin_RGB = (bin_RGB << 8) + colour0;
    bin_RGB = (bin_RGB << 8) + colour0;
return bin_RGB; 
}

// Converts  RGB image to grayscale double image.
GrayImage to_gray(const RGBImage &cimage){
    GrayImage cimage_in_gray;
    for (size_t i(0); i < cimage.size(); i++){
        cimage_in_gray.push_back(vector<double> (0));
        for (size_t j(0); j < cimage[0].size(); j++){
            cimage_in_gray[i].push_back(get_gray(cimage[i][j]));
        }
    }
return cimage_in_gray;
}

// Converts grayscale double image to an RGB image.
RGBImage to_RGB(const GrayImage &gimage){
    RGBImage gimage_in_col;
    for (size_t i(0); i < gimage.size(); i++){
        gimage_in_col.push_back(vector<int> (0));
        for (size_t j(0); j < gimage[0].size(); j++){
            gimage_in_col[i].push_back(get_RGB(gimage[i][j]));
        }
    }
return gimage_in_col;
}

// ***********************************
// TASK 2: FILTER
// ***********************************

// Get a pixel without accessing out of bounds
// return nearest valid pixel color
void clamp(long &val, long max){ 
    if(val<0){
        val = 0;
    }
    if(val>= max){
        val=max;
    }
}

// Convolve a single-channel image with the given kernel.
GrayImage filter(const GrayImage &gray, const Kernel &kernel){
    size_t s, t;
    GrayImage filtered_image;
        for (size_t i(0); i < gray.size(); i++){
            filtered_image.push_back(vector<double> (0.0));
            for (size_t j(0); j < gray[0].size(); j++){
                filtered_image[i].push_back(0.0);
                for (size_t ligne_kernel(0); ligne_kernel < kernel.size(); ligne_kernel++){
                    for (size_t col_kernel(0); col_kernel < kernel[0].size(); col_kernel++){
                        s = i - kernel.size() / 2 + ligne_kernel;
                        t = j - kernel[0].size() / 2 + col_kernel;
                        clamp(s, kernel.size());
                        clamp(t, kernel[0].size());
                        filtered_image[i][j] += gray[s][t] * kernel[ligne_kernel][col_kernel];
                    }
                }

            }
        }
    return filtered_image;
}

// Smooth a single-channel image
GrayImage smooth(const GrayImage &gray){
    
return {}; // TODO MODIFY AND COMPLETE
}

// Compute horizontal Sobel filter
GrayImage sobelX(const GrayImage &gray){
    
return {}; // TODO MODIFY AND COMPLETE
}

// Compute vertical Sobel filter
GrayImage sobelY(const GrayImage &gray){
    
return {}; // TODO MODIFY AND COMPLETE
}

// Compute the magnitude of combined Sobel filters

GrayImage sobel(const GrayImage &gray){
    
return {}; // TODO MODIFY AND COMPLETE
}

// ************************************
// TASK 3: SEAM
// ************************************

Graph create_graph(const GrayImage &gray)
{
    return {}; // TODO MODIFY AND COMPLETE
}

// Return shortest path from Node from to Node to
// The path does NOT include the from and to Node
Path shortest_path(Graph &graph, size_t from, size_t to)
{

    return {}; // TODO MODIFY AND COMPLETE
};

Path find_seam(const GrayImage &gray)
{
    return {}; // TODO MODIFY AND COMPLETE
}

// ***********************************
// TASK 3 provided functions
// Highlight or remove seam from RGB or gray image
// ***********************************

// Draw a seam on a gray image
// return a new gray image with the seam in black
GrayImage highlight_seam(const GrayImage &gray, const Path &seam)
{
    GrayImage result(gray);
    // Paint seam in black
    for (size_t row(0); row < seam.size(); ++row) {
        result[row][seam[row]] = 0;
    }
    return result;
}

// Draw a seam on an RGB image
// return a new RGB image with the seam in blue
RGBImage highlight_seam(const RGBImage &image, const Path &seam)
{
    RGBImage result(image);
    // Paint seam in blue
    for (size_t row(0); row < seam.size(); ++row) {
        result[row][seam[row]] = 0x000ff;
    }
    return result;
}

// Remove specified seam from a gray-scale image
// return the new gray image (width is decreased by 1)

GrayImage remove_seam(const GrayImage &gray, const Path &seam)
{
    GrayImage result(gray);
    for (size_t row(0); row < seam.size(); ++row) {
        result[row].erase(result[row].begin() + seam[row]);
    }
    return result;
}

// Remove specified seam from an RGB image
// return the new RGB image (width is decreased by 1)
RGBImage remove_seam(const RGBImage &image, const Path &seam)
{
    RGBImage result(image);
    for (size_t row(0); row < seam.size(); ++row) {
        result[row].erase(result[row].begin() + seam[row]);
    }
    return result;
}
