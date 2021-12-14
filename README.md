# ICC-Project Seam Carving by Bastien Armstrong and Himesh Kanattage 
extension.cpp Explanantion File :
1. The very first function that we have added in our extension.cpp file is our find_successor function, it takes in as arguments ;
a size_t Node Identifier and a gray image. And from this Identifier it will then find its successors and return them as a vector of size_t.
We have also decided to include the different case limits (i.e. if our Node Identifier indicates it is on the last line, or on one of the sides of the graph) to have a more readable main body.

2. The next function that we implemented is a recursive function for The Sortest_Path function. It takes in four parameters 
in argument; two size_t that indicate the bounds of action of our function, the graph it is based upon and an initially 
empty Path that we will fill in. The principle behind our function is to go backwards from our "To" until our "From"  
using recursivity to call back our function with the predecessor of our "To" until this predecessor is our "From". As long as the 
predecessor isn't "From", we will insert it into our Path. It will then return this Path directly in the return of the shortest_path function. 
 
3. The next two functions that we decided to implement work hand in hand to get us the column of a size_t, given a certain width, 
this is used in our find_seam project. They booth take in as arguments an Identifier and a Width, both size_t. THe first one
will return the line number as a size_t. And the second one will re-use the first function to return the column of a given Identifier, 
as a size_t.
