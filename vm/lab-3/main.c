#include <stdio.h>
#include <math.h>

int a= 1, b= 0, c= 0;

double f(double x)
{
	double value = sqrt(x);
	return a - b*value - exp(c*(x*x));
	//return a*x*x+b*x+c;
}

double df(double x)
{
	return 2*a*x+b;
}

// double halfDivision(double i1, double i2)
// {
// 	printf("fault= %lf\n", fabs(i2-i1)/2);
// 	double i= fabs(i1+i2)/2;
// 	double i1_f= f(i1);
// 	double i2_f= f(i2);
// 	double i_f= f(i);
// 	if((i1_f<= 0.000001)&&(i1_f>= 0.0000001))
// 		return i1;
// 	if((i2_f<= 0.000001)&&(i2_f>= 0.0000001))
// 		return i2;
// 	if((i_f<= 0.000001)&&(i_f>= 0.0000001))
// 		return i;
	
// 	if((i1_f*i_f) < 0.0)
// 		return halfDivision(i1, i);
// 	if((i_f*i2_f) < 0.0)
// 		return halfDivision(i, i2);
// 	return -1;
// }

// double chord(double a, double b, double fault)
// {
// 	double c= (a*f(b)-b*f(a))/(f(b)-f(a));
// 	printf("fault= %lf\n", fabs(c-b));
// 	if(fabs(c-b)>fault)
// 		c = chord(a, c, fault);
// 	return c;
// }

// double newton(double x, double fault)
// {
// 	double x1= x-f(x)/df(x);
// 	printf("fault= %lf\n", fabs(x1-x));
// 	if(fabs(x1-x)>fault)
// 		x1= newton(x1, fault);
// 	return x1;
// }

double steffan(double x, double fault)
{
	double denom = f(x) + x;
	double kva = (f(x)*f(x));
	double x1 = (x -(kva/(denom - f(x))));

	printf("fault= %lf\n", fabs(x1-x));
	if(fabs(x1-x)>fault)
	{
		x1 = steffan(x1, fault);
	}

	return x1;

}

int main()
{
	printf("sizeof(double)= %ld\n", sizeof(double));
	int scanf_count= 0;
	double i1, i2;
	printf("a*x^2+ b*x+c=0\n\n");
	
	printf("введите a: ");
	scanf_count+= scanf("%d", &a);
	
	printf("введите b: ");
	scanf_count+= scanf("%d", &b);
	
	printf("введите c: ");
	scanf_count+= scanf("%d", &c);
	if(!scanf_count)
		printf("вы ничего не ввели");
	printf("a= %d b= %d c= %d\n", a, b, c);
	
	scanf_count= 0;
	printf("[i1, i2]\n\n");
	
	printf("введите i1: ");
	scanf_count+= scanf("%lf", &i1);
	
	printf("введите i2: ");
	scanf_count+= scanf("%lf", &i2);
	
	if(scanf_count!= 2)
	{
		printf("вы не ввели интервал");
		return -1;
	}
	printf("i1= %lf i2= %lf\n", i1, i2);
	// printf("метод половинного деления\n");
	// printf("корень %lf\n", halfDivision(i1, i2));
	// printf("метод хорд\n");
	// printf("корень %lf\n", chord(i1, i2, 0.000001));
	// printf("метод Ньютона\n");
	// printf("корень %lf\n",newton(i2, 0.000001));


	printf("метод Стеффана\n");
	printf("корень %lf\n", steffan(i2, 0.000001));

	return 0;
}
