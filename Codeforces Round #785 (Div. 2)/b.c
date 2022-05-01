#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXS ((unsigned int) 2E+5+1)
#define cval(c) (c - 'a')
#define bm(c) (1 << cval(c))

unsigned int abc[26];

int main()
{
	int t, i;
	char *s;

	scanf("%d", &t);
	getchar();
	s = (char *) calloc(MAXS, sizeof(char));

	for (i = 0; i < t; ++i) {
		int yes = 1;
		char c;
		int end = 0;
		int expd = 0;
		int siz = 0;
		int p = 0;
	
		while ((c=getchar()) != '\n' && c != EOF) {
			if (!end && !(p & bm(c))) {
				p |= bm(c);
				s[siz++] = c;
			} else {
				end = 1;
			}

			if (end) {
				if (expd == siz)
					expd = 0;
				if (c != s[expd++]) {
					yes = 0;
				}		
			}
		}		
		
		printf("%s\n", (yes) ? "YES" : "NO");
		
	}

	return (0);
}
