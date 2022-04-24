#include <stdio.h>

int main()
{
	unsigned long long int n, m, a;

	scanf("%llu %llu %llu", &n, &m, &a);
	
	unsigned long long int cnt;
	cnt  = (unsigned long long int) (n / a) + (unsigned long long int) ((n%a) && 1);
	cnt *= (unsigned long long int) (m / a) + (unsigned long long int) ((m%a) && 1);

	printf("%llu", cnt);
	
	return (0);
}
