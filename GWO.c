#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rand.h"
#include <time.h>
#include "gwo.h"

#define max 500
#define Inf 123456789

double a,fitness,A,C,D,X1,X2,X3,avg=0;

void verif(int dim, int lb, int ub, int index, Pack *Pack){
	int i;
    for (i = 0; i < dim; ++i){
        if (Pack[index].pos[i] > ub || Pack[index].pos[i] < lb){
            Pack[index].pos[i]= (Pack[32].pos[i]+Pack[31].pos[i]+Pack[30].pos[i])/3;
         } 
    }
}

double randreal(void)
{
    double result;

    if (!isinit) {
	srand(time(0));
	isinit = 1;
    }
    result = ((double) rand());
    result /= RAND_MAX;

    return (result);
}

void initialization(int dim,int lb, int ub, Pack *Pack){

	int i;
	for(i = 0; i<searchAgents; i++){
		
		int j;
		for(j = 0; j<dim; j++){
			Pack[i].pos[j] = randreal()*(ub-lb)+lb;

		}

	}
	Pack[30].fitness = Inf;
	
	Pack[31].fitness = Inf;
	
	Pack[32].fitness = Inf;
	

}

void printResults(Pack *Pack){
	printf("%.75f\n", Pack[32].fitness);
	avg = avg+Pack[32].fitness;

}



void GWO(int dim, int lb, int ub,Pack *Pack, double (*fobj)(double x[])){
	
initialization(dim,lb,ub,Pack);
	int i = 0;
	while(i<max){
		
		int j;
		for(j=0;j<searchAgents;j++){
			verif(dim,lb,ub,j,Pack);
			
			fitness = fobj(Pack[j].pos);
			
			if(fitness < Pack[32].fitness){
				Pack[30].fitness = Pack[31].fitness;
				memcpy(Pack[30].pos, Pack[31].pos, sizeof(Pack[31].pos));
				Pack[31].fitness = Pack[32].fitness;
				memcpy(Pack[31].pos, Pack[32].pos, sizeof(Pack[32].pos));
				Pack[32].fitness = fitness;
				memcpy(Pack[32].pos, Pack[j].pos, sizeof(Pack[j].pos));
			}
			if(fitness > Pack[32].fitness && fitness <Pack[31].fitness){
				Pack[30].fitness = Pack[31].fitness;
				memcpy(Pack[30].pos, Pack[31].pos, sizeof(Pack[31].pos));
				Pack[31].fitness = fitness;
				memcpy(Pack[31].pos, Pack[j].pos, sizeof(Pack[j].pos));
			}
			if(fitness >Pack[32].fitness && fitness > Pack[31].fitness && fitness < Pack[30].fitness){
				Pack[30].fitness = Pack[31].fitness;
				memcpy(Pack[30].pos, Pack[j].pos, sizeof(Pack[j].pos));
			}
		}
		

		a=2-i*(2/max);

		for(j=0;j<searchAgents;j++){
			int k;
			for(k=0;k<dim;k++){

				A = 2*a*randreal()-a;
				C = 2*randreal();
			
				D = fabs(C*Pack[32].pos[k]-Pack[j].pos[k]);
				X1= Pack[32].pos[j]-A*D;

				A = 2*a*randreal()-a;
				C = 2*randreal();

				D = fabs(C*Pack[31].pos[k]-Pack[j].pos[k]);
				X2= Pack[31].pos[j]-A*D;

				A = 2*a*randreal()-a;
				C = 2*randreal();

				D = fabs(C*Pack[30].pos[k]-Pack[j].pos[k]);
				X3= Pack[30].pos[j]-A*D;

				Pack[j].pos[k] = (X1 + X2 + X3)/3;
								
			}
		}
		i++;
	}
	printResults(Pack);
}
