#pragma once
#include "seam_types.h"
#include "seam.h"

std::vector<size_t> find_successors(const size_t &Identifier, const GrayImage &gray);

Path result(const size_t &From, const size_t &To, const Graph &graph, Path shortest);

size_t get_lineId(const size_t &Identifier, const size_t &width);

size_t get_colId(const size_t &Identifier, const size_t &width);

GrayImage sharpen(const GrayImage &gray);

GrayImage Gaussian_blur(const GrayImage &gray);

GrayImage matrice_transpose (const GrayImage& initial);

RGBImage dupplicate_seam(const RGBImage &image, const Path &seam);

GrayImage Inverted_gray(const GrayImage &image);

RGBImage Inverted_RGB(const RGBImage &image);

/* A UTILISER POUR LE CODAGE EVENTUEL D'EXTENSIONS */
