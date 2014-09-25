
#define d 30
#define searchAgents 30

#define lb2 -10
#define ub2 10

#define lb4 -100
#define ub4 100

#define lb5 -30
#define ub5 30

typedef struct Wolf{
    double pos[d];
    double fitness;
}Pack;

void GWO(int, int, int, Pack *,double (*fobj)(double[],int));

double fun2(double[], int);
double fun4(double[], int);
double fun5(double[], int);
