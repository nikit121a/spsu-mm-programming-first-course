#include <stdio.h>
#include <math.h>

#define EPS 0.000001

int gcd(int u, int v) //using Stein's binary GCD algorithm
{
  int shift;

  if(u == 0) return v;
  if(v == 0) return u;
 
  for (shift = 0; ((u | v) & 1) == 0; ++shift)
  {
         u >>= 1;
         v >>= 1;
  }
 
  while ((u & 1) == 0)
    u >>= 1;

    do 
    {
       while ((v & 1) == 0)
           v >>= 1;
       if (u > v) {
         unsigned int t = v; v = u; u = t;
	   }  
       v = v - u;                      
    } while (v != 0);

  return u << shift;
}

int main()
{
	float float_a, float_b, float_c;
	int a, b, c;
	printf("Input three positive integer numbers:\n");
	scanf("%f %f %f", &float_a, &float_b, &float_c);

	while(float_a - floorf(float_a) > EPS || float_b - floorf(float_b) > EPS || float_c - floorf(float_c) > EPS || float_a * float_b * float_c < EPS)
	{
		printf("Your input is incorrect, please try again:\n");
		scanf("%f %f %f", &float_a, &float_b, &float_c);
		getchar();
	}

	a = floorf(float_a);
	b = floorf(float_b);
	c = floorf(float_c);

	if(a * a + b * b == c * c || a * a + c * c == b * b || b * b + c * c == a * a)
	{
		printf("%d,%d,%d is a Pythogorean triple.\n", a, b, c);
		printf("This triple is %s. The coefficient is equal to %d.", 
			(gcd(c, gcd(a, b)) - 1) ? "not primitive" : "primitive", gcd(c, gcd(a, b)));
	} 
	else 
	{
		printf("%d, %d, %d is not a Pythogorean triple.\n",a, b, c);
	}
	getchar();
	getchar();
	return 0;
}