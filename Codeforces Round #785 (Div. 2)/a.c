#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAXS ((unsigned int) 2E+5+1)
#define cval(c) (c - 'a'+1)

int cmpr(const void *a, const void *b);

int main()
{
	int t, i;
	char *s;	

	scanf("%d", &t);
	getchar();

	s = (char *) calloc((unsigned int) MAXS, sizeof(char));

	for (i = 0; i < t; ++i) {
		int len;	
		int j;
		fgets(s, MAXS, stdin);
		len = strlen(s);
		if (s[len-1] == '\n')
			s[--len] = '\0';

		if (s[1] == '\0') {
			printf("Bob %d\n", cval(s[0]));
		} else if (s[2] == '\0') {
			printf("Alice %d\n", cval(s[0])+cval(s[1]));
		} else {
			unsigned int sum;
			unsigned int min = 0;
			for (j = 0, sum = 0; j < len; ++j) {
				sum += cval(s[j]);	
			}
			if (len % 2)	
				min = (s[0] < s[len-1]) ? cval(s[0]) : cval(s[len-1]);

		
			printf("Alice %u\n", sum-min-min);
		}
			
	}

	return (0);
}
