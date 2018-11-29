#include "a4.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

double comp_distance(const PIXEL *A, const PIXEL *B, int image_size){
	double r_d = 0, g_d = 0, b_d = 0, distance=0;

	for (int i = 0; i < image_size; i++){
		r_d = (int)(A[i].r) - (int)(B[i].r);
		g_d = (int)(A[i].g) - (int)(B[i].g);
		b_d = (int)(A[i].b) - (int)(B[i].b);
		
		distance += ((r_d*r_d)+(g_d*g_d)+(b_d*b_d));
	}
	return sqrt(distance);
}

void comp_fitness_population(const PIXEL *image, Individual *individual, int population_size){
  	int size = individual->image.width*individual->image.height;

  	for (int i = 0; i < population_size; i++)
  	{
  		individual[i].fitness = comp_distance (image, (individual[i].image.data),size);
  	}
}