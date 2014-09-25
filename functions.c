#include "gwo.h"
#include <math.h>

double fun2(double x[], int dim){
	double fitness=0;
	int k;
	for(k=0; k<dim; k++){

		fitness = fitness + fabs(x[k]);	
		
	}
	double mult=1;
	int m;
		for (m = 0; m < dim;m++)
		{
			mult = mult*fabs(x[m]);
		}
	fitness = fitness + mult;
	return fitness;
}

double fun4(double x[], int dim){
	int k;
	double maxim = 0;
	for(k=0; k<dim; k++){
		if(fabs(x[k]) > maxim){
			maxim = fabs(x[k]);
		}	
		
	}
	return maxim;
}

double fun5(double x[],int dim){
	double fitness=0;
	int k;
	for(k=0; k<dim-1; k++){

		double term1 = (x[k+1] - (x[k] * x[k]))*(x[k+1] - (x[k] * x[k]));
		
		double term2 = (x[k]-1) * (x[k]-1);
		
		fitness = fitness + ((100 * term1) + term2);
		
	}
	return fitness;
}

int main(){
	Pack packArray[searchAgents+3];
	double (*fptr)(double[],int);

	printf("funcion 2\n");
	fptr = fun2;
	GWO(d,lb2,ub2,packArray,fptr);

	printf("funcion 4\n");
	fptr = fun4;
	GWO(d,lb4,ub4,packArray,fptr);

	printf("funcion 5\n");
	fptr = fun5;
	GWO(d,lb2,ub2,packArray,fptr);
	return 0;
}
