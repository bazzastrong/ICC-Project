#include <cassert>
#include <limits>
#include <tgmath.h>
#include <vector>
#include <cmath>

#include "seam.h"
#include "extension.h"

using namespace std;

// ***********************************
// TASK 1: COLOR
// ***********************************

// Returns red component (in the scale 0.0-1.0) from given RGB color.
double get_red(int rgb)
{
    int r0 = rgb >> 16;
    int r = r0 & 0b11111111;
    double doubleR = r / 255.00;
return doubleR;
}

// Returns green component (in the scale 0.0-1.0) from given RGB color.
double get_green(int rgb) 
{
    int g0 = rgb >> 8;
    int g = g0 & 0b11111111;
    double doubleG = g / 255.00;
return doubleG;
}

// Returns blue component (in the scale 0.0-1.0) from given RGB color.
double get_blue(int rgb)
{
    int b = rgb & 0b11111111;
    double doubleB = b / 255.00;
return doubleB; 
}

// Returns the average of red, green and blue components from given RGB color. (Scale: 0.0-1.0)
double get_gray(int rgb) 
{
    double gray = (get_red(rgb) + get_green(rgb) + get_blue(rgb)) / 3;
return gray;
}

// Returns the RGB value of the given red, green and blue components.
int get_RGB(double red, double green, double blue)
{
    int r0(red * 255), g0(green * 255), b0(blue * 255);
    int bin_RGB = 0b00000000;
    bin_RGB = (bin_RGB << 8) + r0; 
    bin_RGB = (bin_RGB << 8) + g0;
    bin_RGB = (bin_RGB << 8) + b0;
return bin_RGB;
}

// Returns the RGB components from given grayscale value (between 0.0 and 1.0).
int get_RGB(double gray)
{
    int bin_RGB(get_RGB(gray, gray, gray));
return bin_RGB; 
}

// Converts  RGB image to grayscale double image.
// Converting every pixel of the Colour Image to a gray pixel using two for loops.
GrayImage to_gray(const RGBImage &cimage)
{
    GrayImage cimage_in_gray;
    for (size_t i(0); i < cimage.size(); i++)
    {
        cimage_in_gray.push_back(vector<double> (0));
        for (size_t j(0); j < cimage[0].size(); j++)
        {
            cimage_in_gray[i].push_back(get_gray(cimage[i][j]));
        }
    }
return cimage_in_gray;
}

// Converts grayscale double image to an RGB image.
// Using two for loops, we are converting every gray pixel to its colour alternative.
RGBImage to_RGB(const GrayImage &gimage)
{
    RGBImage gimage_in_col;
    for (size_t i(0); i < gimage.size(); i++)
    {
        gimage_in_col.push_back(vector<int> (0));
        for (size_t j(0); j < gimage[0].size(); j++)
        {
            gimage_in_col[i].push_back(get_RGB(gimage[i][j]));
        }
    }
return gimage_in_col;
}

// ***********************************
// TASK 2: FILTER
// ***********************************

// Get a pixel without accessing out of bounds, returns nearest valid pixel color
void clamp(long& val, long max)
{ 
    if(val<0)
    {
        val = 0;
    }
    if(val>= max)
    {
        val=max;
    }
}

// Convolve a single-channel image with the given kernel.
// Using the two first for loops, we access every given pixel from the given gray image. Then 
// With the two last for loops we map out, how given a kernel to our function, the pixel will be 
// Modified by the kernel
GrayImage filter(const GrayImage &gray, const Kernel &kernel)
{
    long s, t;
    GrayImage filtered_image;
        for (size_t i(0); i < gray.size(); i++)
        {
            filtered_image.push_back(vector<double> (0));
            for (size_t j(0); j < gray[0].size(); j++)
            {
                filtered_image[i].push_back(0.0);
                for (size_t ligne_kernel(0); ligne_kernel < kernel.size(); ligne_kernel++)
                {
                    for (size_t col_kernel(0); col_kernel < kernel[0].size(); col_kernel++)
                    {
                        s = i - (kernel.size() - 1) / 2 + ligne_kernel;
                        clamp(s, gray.size() - 1);
                        t = j - (kernel[0].size() - 1) / 2 + col_kernel;
                        clamp(t, gray[0].size() - 1);
                        filtered_image[i][j] += gray[s][t] * kernel[ligne_kernel][col_kernel];
                    }
                }

            }
        }
return filtered_image;
}

// Smooth a single-channel image
GrayImage smooth(const GrayImage &gray)
{
    Kernel smoother {{0.10, 0.10,  0.10},
                        {0.10, 0.20, 0.10},
                        {0.10, 0.10, 0.10}};
return filter(gray, smoother);
}

// Compute horizontal Sobel filter
GrayImage sobelX(const GrayImage &gray)
{
    Kernel sobelerX {{-1, 0, 1},
                    {-2, 0, 2},
                    {-1, 0, 1}};
return filter(gray, sobelerX);
}

// Compute vertical Sobel filter
GrayImage sobelY(const GrayImage &gray)
{
    Kernel sobelerY{{-1, -2, -1},
                    {0, 0, 0,},
                    {1, 2, 1}};
return filter(gray, sobelerY);
}

// Compute the magnitude of combined Sobel filters
GrayImage sobel(const GrayImage &gray)
{
    GrayImage sobeleredX = sobelX(gray);
    GrayImage SobeleredY = sobelY(gray);
    GrayImage Sobelered;
    for (int i(0); i < gray.size(); ++i)
    {
        Sobelered.push_back(vector<double> (0));
        for (int j(0); j < gray[0].size(); ++j)
        {
            Sobelered[i].push_back(0.0);
            Sobelered[i][j] = sqrt(pow(sobeleredX[i][j],2) + pow(SobeleredY[i][j], 2));
        }
    }
return Sobelered;
}

// ************************************
// TASK 3: SEAM
// ************************************

// Creating a graph
Graph create_graph(const GrayImage &gray)
{
    Graph graph (gray.size() * gray[0].size());
    size_t k(0);
    constexpr double INF(numeric_limits <double >::max());
    for(size_t i(0); i < gray.size() ; i++)
    {
        for(size_t j(0); j < gray[0].size() ; j++)
        {
            // In order to find The successors we use a function that allows us to 
            // have the case limits already defined in the function
            graph[k].successors = find_successors(k, gray); 
            graph[k].costs= gray[i][j];
            graph[k].distance_to_target = INF; 
            graph[k].predecessor_to_target = 0;
            ++k;
        }
    }
    // Initializing the Beginning node 
    graph.push_back(Node {});
    for (size_t n(0); n < gray[0].size(); ++n)
    {
        graph[gray.size() * gray[0].size()].successors.push_back(size_t (n));
    }
    graph[gray.size() * gray[0].size()].costs = 0;
    graph[gray.size() * gray[0].size()].distance_to_target = INF;
    graph[gray.size() * gray[0].size()].predecessor_to_target = 0;
    // Initializing the End node 
    graph.push_back(Node {});
    graph[gray.size() * gray[0].size() + 1].successors = {};
    graph[gray.size() * gray[0].size() + 1].costs = 0;
    graph[gray.size() * gray[0].size() + 1].distance_to_target = INF;
    graph[gray.size() * gray[0].size() + 1].predecessor_to_target = 0;
return graph;
}

// Return shortest path from Node from to Node to
// The path does NOT include the from and to Node
Path shortest_path(Graph &graph, size_t from, size_t to)
{
    Path shortest;
    // Reusing the Dijkstra Algorithm provided by the instructions
    graph[from].distance_to_target = graph[from].costs;
    bool modified(true);
    while (modified)
    {
        modified = false;
        for (size_t v(0); v < graph.size(); ++v)
        {
            for (auto successors : graph[v].successors)
            {
                if (graph[successors].distance_to_target > (graph[v].distance_to_target + graph[successors].costs))
                {
                    graph[successors].distance_to_target = (graph[v].distance_to_target + graph[successors].costs);
                    graph[successors].predecessor_to_target = v;
                    modified = true;
                }
            }
        }
    }
    // Returning the Path created by our recursive function 
return result(from, to, graph, shortest);
}

// Implementing every aspect of our project in order to return a 
// Path with every column where the energy is the lowest
Path find_seam(const GrayImage &gray)
{
    Graph graph;
    Path shortest;
    size_t width = gray[0].size();
    graph = create_graph(gray);
    shortest = shortest_path(graph, graph.size() - 2, graph.size() - 1);
    Path seam(shortest.size());
    for (size_t i(0); i < shortest.size(); ++i) 
    {
        seam[i] = get_colId(shortest[i], width);
    }
return seam; 
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
    for (size_t row(0); row < seam.size(); ++row)
    {
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
    for (size_t row(0); row < seam.size(); ++row) 
    {
        result[row][seam[row]] = 0x000ff;
    }
return result;
}

// Remove specified seam from a gray-scale image
// Return the new gray image (width is decreased by 1)
GrayImage remove_seam(const GrayImage &gray, const Path &seam)
{
    GrayImage result(gray);
    for (size_t row(0); row < seam.size(); ++row) 
    {
        result[row].erase(result[row].begin() + seam[row]);
    }
return result;
}

// Remove specified seam from an RGB image
// return the new RGB image (width is decreased by 1)
RGBImage remove_seam(const RGBImage &image, const Path &seam)
{
    RGBImage result(image);
    for (size_t row(0); row < seam.size(); ++row) 
    {
        result[row].erase(result[row].begin() + seam[row]);
    }
return result;
}
