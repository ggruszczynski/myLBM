#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <conio.h>

#pragma warning(disable : 4996) // some warnings due to old writing functions


#define pi (4.*atan(1.))
// parameters
double S = 0.001; //reference area
double C = 0.5; //drag coefficient
double q = 1.2; //air density
double g = 9.81; //gravity acceleration
double Vw = 30; // initial wind velocity 
double m = 0.01; //mass of bullet

double Ct = q*S*C / 2; //total drag coeff

#define MAXN 10 // maksymalna ilosc rownan
void vrk4(double x0, double y0[], double h, int n, void(*fun)(double, double*, double*), double yNext[]);

// wykonuje jeden krok calkowania 
// wektorowego rownania rozniczkowego zwyczjanego:
//
//  dY/dx = Fun(x,Y),    Y(x0)=Y0
//
// metoda  Rungego-Kutty IV-tego rzedu.
//
// Parametry formalne:
// x0 - wartosc startowa zm. niezaleznej
// y0 - wartosc startowa zm. zaleznej (tablica n-elementowa)
// h  - krok calkowania
// n  - liczba rownan
// fun(x,y,prawastr) - nazwa funkcji obliczajacej prawe strony
// yNext - obliczona wartosc zmiennej zaleznej w punkcie x0+h
//      (tablica n-elementowa)

void rhs(double t0, double z0[], double f[]);

int main()
{
	// time interval
	double h, t0;
	t0 = 0;	//initial time
	h = 0.01; //time step


	double V0 = 800;		// initial velocity of a bullet
	double alfa = pi / 6;	//angle between ground and rifle


							//initial conditions
	double z0[4];
	z0[0] = 0;				 //y0
	z0[1] = V0*sin(alfa);	 //Vy0 
	z0[2] = 0;				 //x0
	z0[3] = V0*cos(alfa);	 //Vx0

	printf("Initial velocity V0=%lf angle = %lf --> Vy=%lf and Vx=%lf \n\n", V0, alfa, z0[1], z0[3]);
	// after some time t
	double zNext[4];

	FILE *f;
	f = fopen("data_results.txt", "wt");
	if (f == NULL)
	{
		printf("error\n");
		exit(-1);
	}

	int i = 0; int j = 0;
	for (i = 0; z0[0] >= 0; i++) // loop will end if bullet exceed this height
	{
		vrk4(t0, z0, h, 4, rhs, zNext);
		for (j = 0; j<4; j++)
		{
			z0[j] = zNext[j];
		}

		//printf("i=%d \t t0=%lg \t y0=%lg \t Vy0=%lg \t x0=%lg \t Vx0=%lg \n", i, t0, z0[0], z0[1], z0[2], z0[3]);
		fprintf(f, "%lg \t %lg \t %lg \t %lg \t %lg \n", t0, z0[0], z0[1], z0[2], z0[3]);

		t0 += h;
	}
	printf("\nh=%lg \t i=%d \t t0=%lg \n", h, i, t0);
	printf("y0=%lg\t Vy0=%lg\t x0=%lg\t Vx0=%lg\n", z0[0], z0[1], z0[2], z0[3]);

	system("PAUSE");
	return 0;
}

void rhs(double t0, double z0[], double f[]) // liczy prawe strony RRZ, np x'(x,t) = rhs(x,t), np x'(x,t) = 3x^2 + 5t
{
	f[0] = z0[1];																								//Vy
	f[1] = (Ct / m)*sqrt((-Vw*sin(t0) - z0[3])*(-Vw*sin(t0) - z0[3]) + z0[1] * z0[1])*  (-z0[1]) - g;			//ay
	f[2] = z0[3];																								//Vx
	f[3] = (Ct / m)*sqrt((-Vw*sin(t0) - z0[3])*(-Vw*sin(t0) - z0[3]) + z0[1] * z0[1])*(-Vw*sin(t0) - z0[3]);	//ax
}

void vrk4(double x0, double y0[], double h, int n, void(*fun)(double, double*, double*), double yNext[])
{
	int		i;
	double	k1[MAXN], k2[MAXN], k3[MAXN], k4[MAXN];
	double	ytmp[MAXN];

	fun(x0, y0, k1);
	for (i = 0; i<n; ++i)
	{
		k1[i] *= h;
		ytmp[i] = y0[i] + k1[i] / 2.0;
	}

	fun(x0 + h / 2.0, ytmp, k2);
	for (i = 0; i<n; ++i)
	{
		k2[i] *= h;
		ytmp[i] = y0[i] + k2[i] / 2.0;
	}

	fun(x0 + h / 2.0, ytmp, k3);
	for (i = 0; i<n; ++i)
	{
		k3[i] *= h;
		ytmp[i] = y0[i] + k3[i];
	}

	fun(x0 + h, ytmp, k4);
	for (i = 0; i<n; ++i)
		k4[i] *= h;

	for (i = 0; i<n; ++i)
		yNext[i] = y0[i] + (k1[i] + 2.*k2[i] + 2.*k3[i] + k4[i]) / 6.;
}