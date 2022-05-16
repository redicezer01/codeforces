#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ch(c) (c - 'a')

int main()
{
	int t;
	long long int ar[30];

	scanf("%d", &t);
	getchar();

	while (t--) {
		int c, i = 0, r0, l1;
		r0 = -1;
		l1 = 0;
		while ((c=getchar()) != '\n') {
			if (c == '0' && r0 < 0)
				r0 = i;
			else if (c == '1')
				l1 = i;
			++i;
		}

		if (r0 == -1)
			r0 = i-1;
		printf("%d\n", r0-l1+1);
	}
	return (0);
}
