#include "a4.h"
#include <stdio.h>
#include <stdlib.h>

void mutate(Individual *individual, double rate) {

    int n = (individual->image.width)*(individual->image.height);
    int number_mutated = rate/100*n;

    PIXEL *image = individual->image.data;
    int p, i, max_color = individual->image.max_color;

    for(i = 0; i < number_mutated; i++)  {
        // Pick a pixel at random.
        p = rand()%n-1;
        p = p < 0 ? 0 : p;
        // and modify it
        image[p].r = rand()%max_color+1;
        image[p].g = rand()%max_color+1;
        image[p].b = rand()%max_color+1;
    }
}

void mutate_population(Individual *individual, int population_size, double rate) {

	for (int i=(population_size/4); i < population_size; i++ ) {
		mutate(individual+i,rate );
	}
}