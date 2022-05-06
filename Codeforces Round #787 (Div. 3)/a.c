#include <stdio.h>

#define rem(k, p) (((p-k) < 0) ? 0 : p-k)

int main()
{
	int t;
	scanf("%d", &t);

	while (t--) {
		long int a,b,c,x,y;

		scanf("%ld %ld %ld %ld %ld", &a, &b, &c, &x, &y);
		getchar();
		printf("%s\n", (((rem(a, x) + rem(b, y)) <= c) ? "YES" : "NO"));
	}
	return (0);
}
