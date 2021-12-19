#include "extension.h"

// Creating a function that allows us to find the successors 
// from a given Node Identifier, and taking in account the different case limits. 
std::vector<size_t> find_successors(const size_t &Identifier, const GrayImage &gray){
    std::vector<size_t> vect_successors (0);
    if (Identifier >= (gray.size() - 1) * gray[0].size()){
        vect_successors.push_back(size_t (gray.size() * gray[0].size() + 1));
        return vect_successors;
    }
    size_t successors_1, successors_2, successors_3;
    successors_1 = Identifier + gray[0].size() - 1;
    successors_2 = Identifier + gray[0].size();
    successors_3 = Identifier + gray[0].size() + 1;
    if (successors_2 % gray[0].size() == 0){
        vect_successors.push_back(successors_2);
        vect_successors.push_back(successors_3);
        return vect_successors;
    }
    if (successors_3 % gray[0].size() == 0){
        vect_successors.push_back(successors_1);
        vect_successors.push_back(successors_2);
        return vect_successors; 
    }
    vect_successors.push_back(successors_1);
    vect_successors.push_back(successors_2);
    vect_successors.push_back(successors_3);
return vect_successors;
}

// Creating a recursive function that will call itself and insert the optimised path
// from a given value to another 
Path result(const size_t &From, const size_t &To, const Graph &graph, Path shortest){
    if (graph[To].predecessor_to_target == From){
        return shortest;
    } else {
        shortest.insert(shortest.begin(), graph[To].predecessor_to_target);
    }
return result(From, graph[To].predecessor_to_target, graph, shortest);
}

// Creating a function that allows us to find the line of a 
// given value from graph
size_t get_lineId(const size_t &Identifier, const size_t &width){
    size_t line;
    line = Identifier / width;
return line;
}

// Creating a function that allows us to find the column of a 
// given value from a graph
size_t get_colId(const size_t &Identifier, const size_t &width){
    size_t col;
    col = Identifier - (get_lineId(Identifier, width) * width);
return col;
}

// Messing around with different kernels and filters
GrayImage sharpen(const GrayImage &gray)
{
    Kernel sharpened {{0, -1,  0},
                      {-1, 5, -1},
                      {0, -1, 0}};
return filter(gray, sharpened);
}

// Messing around with different kernels and filters
GrayImage Gaussian_blur(const GrayImage &gray)
{
    Kernel blurred {{(1/16), (2/16), (1/16)},
                    {(2/16), (4/16), (2/16)},
                    {(1/16), (2/16), (1/16)}};
return filter(gray, blurred);
}

// Computing the transpose of a matrix to easen up the horizontal resizing
GrayImage matrice_transpose (const GrayImage& initial)
{
    GrayImage transpose(initial[0].size(), std::vector<double>(initial.size()));
    for(size_t i(0); i<initial.size(); i++)
    {
        for(size_t j(0); j<initial[0].size(); j++)
        {
            transpose[j][i]=initial[i][j];
        }
    }
return transpose;
}

// Function that will inset a pixel after the "seamed" pixel
RGBImage dupplicate_seam(const RGBImage &image, const Path &seam)
{
    RGBImage result(image);
    size_t line(0);
    for (size_t row(0); row < seam.size(); ++row) 
    {
        result[row].insert(result[row].begin() + seam[row], image[line][seam[row]]);
        ++line;
    }
return result;
}

// Addition that inverts the gray-scale gradients of a given grayscale image 
GrayImage Inverted_gray(const GrayImage &image)
{
    GrayImage Inv_Gray(image);
    for (int line(0); line < image.size(); ++line)
    {
        for (int row(0); row < image[0].size(); ++row)
        {
            Inv_Gray[line][row] = 1.0 - (1/256) - get_gray(image[line][row]);
        }
    }
return Inv_Gray;
}

// Addition that tries to invert the RGB gradients of a given image
RGBImage Inverted_RGB(const RGBImage &image)
{
    RGBImage Inv_RGB(image);
    for (int line(0); line < image.size(); ++line)
    {
        for (int row(0); row < image[0].size(); ++row)
        {
            Inv_RGB[line][row] = 256.0 - 1.0 - image[line][row];
        }
    }
return Inv_RGB;
}

/* A UTILISER POUR LE CODAGE EVENTUEL D'EXTENSIONS */
