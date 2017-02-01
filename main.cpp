#include <iostream>
#include "allegro_utils.h"

using namespace Eigen;

int main() {
  al_init();
  al_init_image_addon();

  ALLEGRO_DISPLAY *display = al_create_display(256,256);
  ALLEGRO_BITMAP* image;
  ALLEGRO_COLOR color;

  image = al_create_bitmap(256, 256);
  ArrayXXf im(256,256);

  for(int t=0; t<500; t++) {
    for (int n = 0; n < im.cols(); n++)
      for (int m = 0; m < im.rows(); m++)
        im(m, n) = sin(t*0.4 + 0.1 * m);
    normalize_arrayf(im);
    create_gbitmap_from_arrayf(im, &image);
    al_draw_bitmap(image, 0, 0, ALLEGRO_FLIP_HORIZONTAL);
    al_flip_display();
  }

  al_rest(2);

  al_destroy_display(display);
  return 0;
}