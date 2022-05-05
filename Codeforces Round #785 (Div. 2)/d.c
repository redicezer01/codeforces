#include <stdio.h>

#define LLI long long int

#define last(f, d, n) ((n-1) * d + f)
#define isin(x, f, d, n) (((x-f) % d) == 0 && ((x-f) / d) < n)
#define abs(x) ((x < 0) ? -x : x)

int main()
{
	int t;

	scanf("%d", &t);
	getchar();

	while (t--) {
		LLI b, q, y;
		LLI c, r, z;

		scanf("%lld %lld %lld", &b, &q, &y);
		getchar();
		scanf("%lld %lld %lld", &c, &r, &z);
		getchar();
	
		if (c >= b && last(c, r, z) <= last(b, q, y) && 
		    !(r%q) && isin(c, b, q, y)) {
			printf("IN\n");
		} else {
			printf("0\n");
		}
	}
	
	return (0);
}
