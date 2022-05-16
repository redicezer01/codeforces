#include <stdio.h>
#include <string.h>

#define abs(n) ((n < 0) ? -n : n)

int getdiff(char *s1, char *s2, int n);
	
int main()
{
	int t;
	int a[2500];
	
	scanf("%d", &t);
	getchar();

	while (t--) {
		int n, m, i, j, acnt = 0;
		char s[9];
		char all[50][9];
		int min = (int) 1E+5;

		scanf("%d %d", &n, &m);
		getchar();

		
		
		for (i = 0; i < n; ++i) {
			fgets(s, m+1, stdin);	
			strcpy(all[i], s);
			getchar();

			for (j = i-1; j >= 0; --j) {
				a[acnt] = getdiff(s, all[j], m);	
				
				if (min > a[acnt])
					min = a[acnt];
				++acnt;
			}

		}
		printf("%d\n", min);	

		for (i = 0; i < acnt; ++i) {
			a[acnt] = 0;
		}
	}

	return (0);
}


int getdiff(char *s1, char *s2, int n)
{
	int i, diff = 0, temp;
	for (i = 0; i < n; ++i) {
		temp = s1[i] - s2[i];
		diff += abs(temp);
	}

	return diff;
}
