//
// Created by julio on 1/31/17.
//

#include "allegro_utils.h"

using namespace Eigen;

void create_gbitmap_from_arrayf(const ArrayXXf &im, ALLEGRO_BITMAP **bitmap)
{
  ALLEGRO_BITMAP* current_bitmap;
  if(*bitmap != NULL)
    al_destroy_bitmap(*bitmap);
  current_bitmap = al_get_target_bitmap();

  int flags = al_get_new_bitmap_flags();
  al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP | ALLEGRO_MIN_LINEAR);

  *bitmap = al_create_bitmap(im.cols(), im.rows());
  al_lock_bitmap(*bitmap, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_WRITEONLY);
  al_set_target_bitmap(*bitmap);

  ALLEGRO_COLOR color;
  for(int n = 0; n<im.cols(); n++)
    for(int m = 0; m<im.rows(); m++){
      color = al_map_rgb_f(im(m,n), im(m,n), im(m,n));
      al_put_pixel(n, m, color);
    }

  al_unlock_bitmap(*bitmap);
  al_set_target_bitmap(current_bitmap);
  al_set_new_bitmap_flags(flags);
  //al_convert_bitmap(*bitmap);
}

void normalize_arrayf(Eigen::ArrayXXf& im, const float min, const float max)
{
  const float a = im.minCoeff();
  const float b = im.maxCoeff();

  im = (im-a)*((max-min)/(b-a)) + min;
}

void get_rgb_arraysf(ALLEGRO_BITMAP *bitmap, Eigen::ArrayXXf& R,
                     Eigen::ArrayXXf& G, Eigen::ArrayXXf& B)
{
  const int M = al_get_bitmap_height(bitmap);
  const int N = al_get_bitmap_width(bitmap);
  ALLEGRO_BITMAP *current_bitmap, *mem_bitmap;
  current_bitmap = al_get_target_bitmap();


  int flags = al_get_new_bitmap_flags();
  al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP | ALLEGRO_MIN_LINEAR);
  mem_bitmap = al_clone_bitmap(bitmap);

  al_lock_bitmap(mem_bitmap, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READONLY);
  al_set_target_bitmap(mem_bitmap);

  ALLEGRO_COLOR color;
  R.resize(M,N);
  G.resize(M,N);
  B.resize(M,N);
  float r,g,b;
  for(int n = 0; n<N; n++)
    for(int m = 0; m<M; m++){
      color = al_get_pixel(mem_bitmap, n, m);
      al_unmap_rgb_f(color, &r, &g, &b);
      R(m,n) = r;
      G(m,n) = b;
      B(m,n) = b;
    }

  al_unlock_bitmap(mem_bitmap);
  al_set_target_bitmap(current_bitmap);
  al_set_new_bitmap_flags(flags);
  al_destroy_bitmap(mem_bitmap);
}

void get_grey_arraysf(ALLEGRO_BITMAP *bitmap, Eigen::ArrayXXf& G)
{
  const int M = al_get_bitmap_height(bitmap);
  const int N = al_get_bitmap_width(bitmap);
  ALLEGRO_BITMAP *current_bitmap, *mem_bitmap;
  current_bitmap = al_get_target_bitmap();


  int flags = al_get_new_bitmap_flags();
  al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP | ALLEGRO_MIN_LINEAR);
  mem_bitmap = al_clone_bitmap(bitmap);

  al_lock_bitmap(mem_bitmap, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_READONLY);
  al_set_target_bitmap(mem_bitmap);

  ALLEGRO_COLOR color;
  G.resize(M,N);
  float r,g,b;
  for(int n = 0; n<N; n++)
    for(int m = 0; m<M; m++){
      color = al_get_pixel(mem_bitmap, n, m);
      al_unmap_rgb_f(color, &r, &g, &b);
      G(m,n) = 0.2989*r + 0.5870*g + 0.1140*b;
    }

  al_unlock_bitmap(mem_bitmap);
  al_set_target_bitmap(current_bitmap);
  al_set_new_bitmap_flags(flags);
  al_destroy_bitmap(mem_bitmap);
}

void create_cbitmap_from_arraysf(const Eigen::ArrayXXf &R,
                                 const Eigen::ArrayXXf &G,
                                 const Eigen::ArrayXXf &B,
                                 ALLEGRO_BITMAP **bitmap)
{
  ALLEGRO_BITMAP* current_bitmap;
  if(*bitmap != NULL)
    al_destroy_bitmap(*bitmap);
  current_bitmap = al_get_target_bitmap();

  int flags = al_get_new_bitmap_flags();
  al_set_new_bitmap_flags(ALLEGRO_MEMORY_BITMAP | ALLEGRO_MIN_LINEAR);

  *bitmap = al_create_bitmap(R.cols(), R.rows());
  al_lock_bitmap(*bitmap, ALLEGRO_PIXEL_FORMAT_ANY, ALLEGRO_LOCK_WRITEONLY);
  al_set_target_bitmap(*bitmap);

  ALLEGRO_COLOR color;
  for(int n = 0; n<R.cols(); n++)
    for(int m = 0; m<R.rows(); m++){
      color = al_map_rgb_f(R(m,n), G(m,n), B(m,n));
      al_put_pixel(n, m, color);
    }

  al_unlock_bitmap(*bitmap);
  al_set_target_bitmap(current_bitmap);
  al_set_new_bitmap_flags(flags);
}

void read_cimage_arrayf(const char *fname, Eigen::ArrayXXf &R,
                        Eigen::ArrayXXf &G,
                        Eigen::ArrayXXf &B)
{
  ALLEGRO_BITMAP* image;

  image = al_load_bitmap(fname);

  get_rgb_arraysf(image, R, G, B);

  al_destroy_bitmap(image);
}

void read_gimage_arrayf(const char *fname, Eigen::ArrayXXf &G)
{
  ALLEGRO_BITMAP* image;

  image = al_load_bitmap(fname);

  get_grey_arraysf(image, G);

  al_destroy_bitmap(image);
}