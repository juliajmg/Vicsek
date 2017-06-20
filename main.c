#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


#define N 4
#define SYSTEM_SIZE 6
#define BOX_SIZE 1
#define tamano (int)(SYSTEM_SIZE*SYSTEM_SIZE/BOX_SIZE)

		/* Generate prototype of particle and box structure */

typedef struct {
	int x;
	int y;  
} box_type;

typedef struct {    // MISSING: particles orientations cos and sin. 
	float x;
	float y;
	int id; 
	box_type *box;
} particle_type;



		/* Define amount of particles and boxes structures */

particle_type  particles[N];

box_type boxes[(int)((SYSTEM_SIZE*SYSTEM_SIZE)/BOX_SIZE)];


		/* Create particles coordinates and id */
int plot() {
	system("gnuplot -p -e \"plot '/home/ju/Documents/Vicsek/tarara/Debug/particles.txt'  using 1:2 title 'Particles'\"");
}	

void create_particles() {
	int i;
	int file = fopen("particles.txt", "w");
	
	printf("Particles coordinates:\n");
	
	for(i = 0; i < N; i++){
		particles[i].x = ((float)rand() / (float)(RAND_MAX))*(SYSTEM_SIZE);    // MISSING: particles orientations cos and sin. 
		particles[i].y = ((float)rand() / (float)(RAND_MAX))*(SYSTEM_SIZE);
		particles[i].id = i;
		
		
		printf("Particle %d: x = %f, y = %f\n", particles[i].id, particles[i].x, particles[i].y);
		
		fprintf(file, "%f, %f, %d\n", particles[i].x, particles[i].y, particles[i].id);
	}
	fclose(file);
}

		/* Create boxes coordinates */

void create_boxes() {
	int i, j;
	int count = 0;
	int file = fopen("boxes.txt", "w");
	
	printf("Boxes coordinates:\n");
	
	for(i = 0; i < (int)(SYSTEM_SIZE/BOX_SIZE); i++){
		for(j = 0; j < (int)(SYSTEM_SIZE/BOX_SIZE); j++){
			boxes[count].x = i; 
			boxes[count].y = j;
			
			printf("Box %d: x = %d y = %d\n",count, boxes[count].x, boxes[count].y);
			fprintf(file, "%d, %d\n", boxes[count].x, boxes[count].y);
			count = count + 1;

			}
		}
	fclose(file);
}
		
		
		
		/* Find the box of a given particle and */

void set_box_of(particle_type *p) {                         // The argument is a particle_type pointer to the address of the particle p. 
	int i;
	box_type *b;                                               // Create a box_type pointer b. 
	for(i = 0; i < tamano; i++){  // For each box. 
		b = &boxes[i];                                         // Point b to the address of the box in turn. 
		if((b->x == (int)p->x) && (b->y == (int)p->y)){         // If b x,y coordinates = p (int)x,y coordinates:
			p->box = b;                                      // Save b pointer to address of box[i], into "box" pointer variable inside particle p. 
			printf("Box of particle %d is x = %d and y = %d\n", p->id, b->x, b->y);
			//return p->box;                                       // Return box pointer variable inside particle. Unnecessary: already saved in p->box. 
		}
	}
}


box_type * neighbor_boxes(particle_type *p) {       // Pointer as output because an array of structures is obtained. 
	int i, j, y, x;
	box_type *b;                                 // Create a box_type pointer b. 
	b = p->box;                                  // assign b to the box pointer variable of particle p. 
	box_type result[9]; //                       // Create an array (pointer) of 9 box_type structures for the 9 boxes that are in the neighborhood. 
	int count = 0;
	printf("Neighbor boxes of particle %d\n", p->id);
	for(i = -1; i <= 1; i++){                    // Box interval 
		for(j = -1; j <= 1; j++){
			y = b->y + i;                        // MISSING: Periodic boundaries. 
			x = b->x + j;
			result[count].y = y;                // Save each neighbor box coordinates (x, y) in each slot in the result structure array. 
			result[count].x = x;
			printf("x = %d, y = %d\n",(b->x + j),(b->y + i));
			count = count + 1;
		}
	}
	return result;                               // Returns the address of the first element of the array of structures "results".
}


particle_type *particles_in_box(box_type *b){
	int count = 0;
	int i;
	particle_type *ps = calloc(N,sizeof(particle_type));
	for(i = 0; i < N; i++) {
		if(particles[i].box = b){
			ps[count] = particles[i];
			printf("Ps %d: x = %d, y = %d\n", i, ps[count].x, ps[count].y);
			count = count + 1;
	
		}
	}
 realloc(ps, count); // 
 return ps;
 // Freeeeeee (in one time step function or here?) 
}
		


int main() {
	srand(time(NULL));
	printf("%d\n", tamano);
	create_particles();
	create_boxes();
	set_box_of(&particles[1]);
	neighbor_boxes(&particles[1]);
	printf("Particle 1 box x = %d, y = %d\n", particles[1].box->x, particles[1].box->y);
	particles_in_box(&boxes[0]);
	plot();
	return 0;
}