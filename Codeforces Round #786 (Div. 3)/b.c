#include <stdio.h>

#define ABCS 26
#define abcs() (ABCS - 1)
#define getcn(c) (c - 'a')

int main()
{
	int t, i;
	char s[4];
	scanf("%d", &t);
	getchar();
	
	for (i = 0; i < t; ++i) {
		char a, b;
		fgets(s, 4, stdin);
		a = getcn(s[0]);
		b = getcn(s[1]);
		printf("%d\n", (a*abcs()) + ((b < a) ? b+1 : b));
	}

	return (0);
}
