#pragma once
#include "seam_types.h"

std::vector<size_t> find_successors(const size_t &Identifier, const GrayImage &gray);

size_t get_row(size_t Identifier, size_t width);

size_t get_col(size_t Identifier, size_t width);

Path result(size_t Identifier, Graph graph, Path shortest);
/* A UTILISER POUR LE CODAGE EVENTUEL D'EXTENSIONS */
