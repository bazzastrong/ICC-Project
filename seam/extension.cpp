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
    };
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
/* A UTILISER POUR LE CODAGE EVENTUEL D'EXTENSIONS */
