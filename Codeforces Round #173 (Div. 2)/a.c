#include <stdio.h>

#define ISINC(s) (s[1] == '+')

int main()
{
	char s[5];
	int n, x = 0;

	scanf("%d\n", &n);
	
	while (n--) {
		fgets(s, 5, stdin);
		
		x += (ISINC(s)) ? 1 : -1;	
	}

	printf("%d\n", x);
	

	return (0);
}
