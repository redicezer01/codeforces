#include <stdio.h>

#define ctoi(c) (c - '0')

int main()
{
	int t, suml, sumr;
	scanf("%d", &t);
	getchar();

	while (t--) {
		suml =	ctoi(getchar()) + ctoi(getchar()) + ctoi(getchar());
		sumr =	ctoi(getchar()) + ctoi(getchar()) + ctoi(getchar());
		getchar();
		
		printf("%s\n", (suml == sumr) ? "YES" : "NO");

	}

	return(0);
}
