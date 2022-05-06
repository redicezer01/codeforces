#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXS ((long long int) 2E+5)
#define cn(c) (c - 'a')

char abc['z'];

int main()
{
	int t;
	char *s;
	
	s = (char *) calloc(MAXS, sizeof(char));

	scanf("%d", &t);

	while (t--) {
		long long int n, k, i = 0;

		scanf("%lld %lld", &n, &k);
		getchar();
		
		for (i = 0; i < 'z'; ++i)
			abc[i] = 0;

		int c;

		while ((c=getchar()) != '\n' && c != EOF) {
			while (c > 'a') {
				if (abc[c]) {
					--c;
				} else if (k > 0) {
					++abc[c];
					--k;
					--c;
				} else {
					break;
				}
			}
			s[i++] = c;
		}
		s[i] = '\0';	
			
		printf("%s\n", s);
	}
	return (0);
}
