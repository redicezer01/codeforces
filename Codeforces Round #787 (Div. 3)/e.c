#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXS ((long long int) 2E+5)
#define cn(c) (c - 'a')

int main()
{
	int t;
	char *s;

	s = (char *) calloc(MAXS, sizeof(char));

	scanf("%d", &t);

	while (t--) {
		long long int n, k;
		long long int len, i;

		scanf("%lld %lld", &n, &k);
		getchar();
		fgets(s, n+1, stdin);
		len = strlen(s);

		long long int stf = 0;
		while (k > 0) {
			long long int to, from, max = 0; 
			for (i = 0; i < len; ++i) {
				if (!cn(s[i]))
					continue;
				if (!max) {
					if (cn(s[i]) <= k) {
						max = cn(s[i]);
						to = 0;
						from = k;
					} else {
						max = k;
						to = cn(s[i]) - max;
						from = cn(s[i]);
					}
				}	

				if (to < cn(s[i]) && cn(s[i]) <= from) {
					if (!to && cn(s[i]) > max)
						max = cn(s[i]);
					s[i] = to + 'a';
				}
			}
			k -= max;
		}
			
		printf("%s\n", s);
	}
	return (0);
}
