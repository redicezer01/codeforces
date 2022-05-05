#include <stdio.h>

int main()
{
	int t, i;
	scanf("%d", &t);
	getchar();

	for (i = 0; i < t; ++i) {
		int n, j, a, p1, p2;
		int pn1, pn2;
		int etwo = 0;
		int yes =  1;

		scanf("%d", &n);
		getchar();
		int odd = n % 2;
		int after;
		after = ((odd) ? 0 : 1);
		for (j = 0; j < n; ++j) {
			scanf("%d", &a);

			if (odd && j == 0) {
				p2 = a;
				p1 = a;
			} else if (etwo == 2) {
				p2 = pn2;
				p1 = pn1;
				etwo = 1;
			} else {
				++etwo;
			}

			if (j > after && (a < p1 || a < p2)) {
				yes = 0;
			}	

			pn2 = pn1;
			pn1 = a;
		}
		printf("%s\n", (yes) ? "YES" : "NO");
		getchar();
	}	

	return (0);
}
