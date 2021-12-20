# ICC-Project Seam Carving by Bastien Armstrong and Himesh Kanattage 
extension.cpp Explanantion File :
1. std::vector<size_t> find_successors(const size_t &Identifier, const GrayImage &gray);
The very first function that we have added in our extension.cpp file is our find_successor function, it takes in as 
arguments ; a size_t Node Identifier and a gray image. And from this Identifier it will then find its successors and 
return them as a vector of size_t. We have also decided to include the different case limits (i.e. if our Node 
Identifier indicates it is on the last line, or on one of the sides of the graph) to have a more readable main body.

2. Path result(const size_t &From, const size_t &To, const Graph &graph, Path shortest);
The next function that we implemented is a recursive function for The Sortest_Path function. It takes in four parameters 
in argument; two size_t that indicate the bounds of action of our function, the graph it is based upon and an initially 
empty Path that we will fill in. The principle behind our function is to go backwards from our "To" until our "From"  
using recursivity to call back our function with the predecessor of our "To" until this predecessor is our "From". As 
long as the predecessor isn't "From", we will insert it into our Path. It will then return this Path directly in the return 
of the shortest_path function. 
 
3. size_t get_lineId(const size_t &Identifier, const size_t &width); 
    size_t get_colId(const size_t &Identifier, const size_t &width);
The next two functions that we decided to implement work hand in hand to get us the column of a size_t, given a certain 
width, this is used in our find_seam project. They booth take in as arguments an Identifier and a Width, both size_t. 
The first one will return the line number as a size_t. And the second one will re-use the first function to return 
the column of a given Identifier, as a size_t.

4. BONUS: GrayImage sharpen(const GrayImage &gray);
         GrayImage Gaussian_blur(const GrayImage &gray);
The next two functions are two functions that implement two new filters ; sharpen and a Gaussian Blur. 
We decided to implement them so that we could explore how the seams will evolve when we pass different filters to an image.

5. BONUS:  GrayImage matrice_transpose (const GrayImage& initial);
This function is a shortcut when we want to re-size an image vertically. Instead of re-writting another set of functions 
to find the horizontal seams, our function will create the transpose of a given image Grayimage so that we can re-use 
our shortest_path, create_graph and find_seam directly with the transpose of our Grayimage. THe only thing we have 
left to do, after this is to pass the resized transpose Image once more in our matrice_transpose function to get the
original orientation of our image. Its working is rather straightforward as it simply creates a new matrix where the 
pixels of a given line become the pixels of a new column!

6. BONUS: RGBImage dupplicate_seam(const RGBImage &image, const Path &seam);
This function enables us to duplicate the increase the size of an image by copying the pixels with the least importance 
i.e. the pixels in a seam. It takes in arguments an image and a seam of this image, what it then does is copy this image 
into another matrix, then for every line we will insert the pixel given by the seam after the seam position.

7. BONUS: GrayImage Inverted_gray(const GrayImage &image);
          RGBImage Inverted_RGB(const RGBImage &image);
These two functions are additions that we wanted to test out with our seams, to see what it would change. They are the 
some principle but for two different applications (RGB colours and grayscales). To find the inverted image of a GrayImage we 