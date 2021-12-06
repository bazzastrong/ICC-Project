#pragma once
#include "seam_types.h"

std::vector<size_t> find_successors(const size_t &Identifier, const GrayImage &gray);

size_t get_lineId(const size_t &Identifier, const size_t &width);

size_t get_colId(const size_t &Identifier, const size_t &width);

Path result(const size_t &From, const size_t &To, const Graph &graph, Path shortest);
/* A UTILISER POUR LE CODAGE EVENTUEL D'EXTENSIONS */
