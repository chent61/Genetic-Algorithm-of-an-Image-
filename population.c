#include "a4.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>


PIXEL *generate_random_image(int width, int height, int max_color) {
    int size = width * height;
    int i;
    PIXEL *image = (PIXEL*)malloc(size*sizeof(PIXEL));
    assert(image);

    for(i=0; i < size; i++)
    {
        image[i].r = rand()%max_color+1;
        image[i].g = rand()%max_color+1;
        image[i].b = rand()%max_color+1;
    }
    return image;
}

Individual *generate_population(int population_size, int width, int height, int max_color)
{
    Individual *child = (Individual*)malloc(population_size*sizeof(Individual));
  
    for (int i = 0; i < population_size; i++)
    {
        child[i].image.width = width;
        child[i].image.height = height;
        child[i].image.max_color = max_color;
        child[i].image.data = generate_random_image(width,height,max_color);
    }
    return child;
}


