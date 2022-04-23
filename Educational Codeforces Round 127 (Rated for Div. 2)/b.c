#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define TMAX ((int) 2E+4)
#define NMAX ((int) 2E+5)
#define VALID_T(t) (1 <= t && t <= TMAX)
#define VALID_N(n) (1 <= n && n <= NMAX)

void atoint(char *s, int *num);

int main()
{
	int t, n, xi;
	scanf("%d", &t);
	if (!VALID_T(t))
		return (0);	

	int *x;
	x = (int *) calloc(NMAX, sizeof(int));
	
	while (t--) {
		scanf("%d", &n);
		getchar();
		if (!VALID_N(n))
			return (0);	
		int newline = 0;	
		int numcnt = 0;
		int  chi = 0;
		char chunk[10];
		/* input all numbers from line */
		while (!newline && numcnt < n) {
			char s[512];
			int  i = 0;

			fgets(s, 512, stdin);
			while (s[i] != '\0') {
				chunk[chi] = s[i];
				if (s[i] == '\n' || s[i] == ' ') {
					chunk[chi] = '\0';
					atoint(chunk, &x[numcnt]);
					chi = 0;
					++numcnt;	
				} else {
					++chi;
				}
				if (s[i] == '\n') {
					newline = 1;
					break;
				}	
				++i;	
			}
		}
		/* end input */

		int i;
		int cml, cmr, yes;
		cml = cmr = yes = 1;
		for (i = 1; i < numcnt; ++i) {
			int diff = x[i] - x[i-1];
			
			if (diff == 2) {
				if (cml) {
					cml = 0;
				} else if (cmr) {
					cmr = 0;
				} else {
					yes = 0;	
					break;
				}
			} else if (diff == 3) {
				if (cml && cmr) {
					cml = cmr = 0;
				} else {
					yes = 0;
					break;
				}	
			} else if (diff >= 4) {
				yes = 0;
				break;
			}
		}
		printf("%s\n", (yes) ? "YES" : "NO");
	}
	free(x);
	return (0);
}

void atoint(char *s, int *num)
{
	int i = 0;
	*num = 0;
	
	while (s[i] != '\0' && i < 10) {
		*num = (*num * 10) + (s[i] - '0');
		++i;
	}	
}
