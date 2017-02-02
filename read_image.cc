//
// Created by julio on 1/31/17.
//

#include <iostream>

#include "allegro_utils.h"

using namespace Eigen;

int main() {
  al_init();
  al_init_image_addon();

  ALLEGRO_DISPLAY *display=NULL;
  ALLEGRO_BITMAP* image=NULL;

  ArrayXXf Ir, Ig, Ib;
  read_gimage_arrayf("./data/foto01.jpg", Ig);



  display = al_create_display(Ig.cols(), Ig.rows());
  create_gbitmap_from_arrayf(Ig, &image);
  al_draw_bitmap(image, 0, 0, 0);
  al_flip_display();

  al_rest(2);

  al_destroy_display(display);
  return 0;
}