#include "a4.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int cmpfitness(const void *a, const void *b) {
  return ((*(Individual*)a).fitness - (*(Individual*)b).fitness);
}

PPM_IMAGE *evolve_image(const PPM_IMAGE *image, int num_generations, int population_size, double rate){

	Individual *gen = generate_population(population_size, image->width, image->height, image->max_color);
	comp_fitness_population(image->data, gen, population_size);
	qsort(gen,population_size, sizeof(Individual), cmpfitness);
	printf("Generation: 0 / %d 	Fitness: %f\n",num_generations-1, gen[0].fitness);
	write_ppm("file0.ppm", &gen[0].image);
	
	for (int i = 1; i < num_generations; ++i){
		char s1[100] = "file";
		char s2[100];
		char ext[100] =".ppm";
		char *s;
		char *t;
		sprintf(s2, "%d", i);
		s = strcat(s1,s2);
		t = strcat(s,ext); 
		crossover(gen, population_size);
		mutate_population(gen, population_size, rate);
		comp_fitness_population(image->data, gen, population_size);
		qsort(gen,population_size, sizeof(Individual), cmpfitness);
		printf("Generation: %d / %d 	Fitness: %f\n",i,num_generations-1, gen[0].fitness);
		if (i%50 == 0 )
			write_ppm(t,&gen[0].image);		
	}
	PPM_IMAGE *result = (PPM_IMAGE*)malloc(sizeof(PPM_IMAGE));
	result->width=gen[0].image.width;
	result->height=gen[0].image.height;
	result->max_color=gen[0].image.max_color;

	int size = result->width*result->height;
	PIXEL *color = (PIXEL*)malloc(size*sizeof(PIXEL));	

	for (int i = 0;i < size; i++){
		color[i].r = gen[0].image.data[i].r;
		color[i].g = gen[0].image.data[i].g;
		color[i].b = gen[0].image.data[i].b;
	}
	
	result->data = color;

	for (int i = 0; i < population_size; i++){
		free(gen[i].image.data);		
	}
	free(gen);
	return result;
}

void free_image(PPM_IMAGE *p){

	free(p->data);
	free(p);
}
