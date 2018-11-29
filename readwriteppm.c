#include "a4.h"
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>
#include <string.h>

PPM_IMAGE *read_ppm ( const char *file_name ) {
	char ptype [100];
	int width, height, max, values, i, red, blue, green, type;
	FILE *fr = fopen(file_name, "r");

	if (!fr) {
		printf("Unable to open file %s\n", file_name);
		exit(0);
	}

	type = fscanf(fr, "%[^\n]", ptype );
	assert(type);
	if(ptype[0]!='P'|| ptype[1] != '3') {
		printf("%s is not PPM file\n", ptype);
		exit(0);
	}

	PPM_IMAGE *Pixels = (PPM_IMAGE*)malloc(sizeof(PPM_IMAGE));
	assert(Pixels);

	values=fscanf(fr, "%d %d %d", &width, &height, &max);
	assert(values==3);
	Pixels->width = width;
	Pixels->height = height;
	Pixels->max_color = max;

	int size = width*height;
	PIXEL *color = (PIXEL*)malloc(size*sizeof(PIXEL));	

	for (i = 0;i < size; i++){
		values = fscanf(fr, "%d %d %d", &red, &green, &blue);
		assert(values==3);
		color[i].r = red;
		color[i].g = green;
		color[i].b = blue;
	}
	
	Pixels->data = color;
	fclose(fr);
	return Pixels;
}

void write_ppm(const char *file_name, const PPM_IMAGE *image){
	int i;
	FILE *fw = fopen(file_name, "w");
	PIXEL *color = image->data;

	fprintf(fw, "P3\n");
	fprintf(fw, "%d %d\n%d\n",image->width, image->height, image->max_color);

	for(i = 0; i <image->width*image->height; i++){
		fprintf(fw, "%d %d %d ", color[i].r, color[i].g, color[i].b);
		if ((i+1)%10==0)
			fprintf(fw, "\n");
	}
	fclose(fw);
}