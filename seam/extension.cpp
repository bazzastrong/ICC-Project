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

// Creating a recursive function that will call itself and insert the optimised path
// from a given value to another 
Path result(const size_t &From, const size_t &To, const Graph &graph, Path shortest){
    if (graph[To].predecessor_to_target == From){
        return shortest;
    }
    else {
        shortest.insert(shortest.begin(), graph[To].predecessor_to_target);
    }
return result(From, graph[To].predecessor_to_target, graph, shortest);
}

/* A UTILISER POUR LE CODAGE EVENTUEL D'EXTENSIONS */
