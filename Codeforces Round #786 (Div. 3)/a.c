#include <stdio.h>
#include <math.h>

#define LL long long int
#define ULL(x) ((unsigned LL) (x))

int main()
{

	int t;
	int i;

	scanf("%d", &t);
	getchar();

	for (i = 0; i < t; ++i) {
		int x, y;
		scanf("%d %d", &x, &y);
		getchar();
		
		if (y < x) {
			printf("0 0\n");
			continue;
		}
		if (x == 1) {
			printf("1 %d\n", y);
			continue;
		}
		if (x == y) {
			printf("1 1\n");
			continue;
		}
		if (y % x) {
			printf("0 0\n");
			continue;
		} else {
			printf("1 %d\n", ULL(y / x));
		}
	}

	return (0);
}
