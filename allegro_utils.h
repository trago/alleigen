//
// Created by julio on 1/31/17.
//

#ifndef ALLEGRO_TEST_ALLEGRO_UTILS_H
#define ALLEGRO_TEST_ALLEGRO_UTILS_H

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_primitives.h>
#include <Eigen/Dense>


void normalize_arrayf(Eigen::ArrayXXf& im, const float min=0.0,
                      const float max=1.0);

void create_gbitmap_from_arrayf(const Eigen::ArrayXXf &im,
                                ALLEGRO_BITMAP **bitmap);

void create_cbitmap_from_arraysf(const Eigen::ArrayXXf &R,
                                 const Eigen::ArrayXXf &G,
                                 const Eigen::ArrayXXf &B,
                                 ALLEGRO_BITMAP **bitmap);

void get_rgb_arraysf(ALLEGRO_BITMAP *bitmap, Eigen::ArrayXXf& R,
                     Eigen::ArrayXXf& G, Eigen::ArrayXXf& B);

void read_cimage_arrayf(const char *fname, Eigen::ArrayXXf &R,
                        Eigen::ArrayXXf &G,
                        Eigen::ArrayXXf &B);

void read_gimage_arrayf(const char *fname, Eigen::ArrayXXf &G);


#endif //ALLEGRO_TEST_ALLEGRO_UTILS_H
