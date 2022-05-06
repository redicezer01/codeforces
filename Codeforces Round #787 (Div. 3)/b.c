#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXA ((long long int) 2E+9)

void reverse(char *s, int len);

int main()
{
	int t;
	long long int ar[30];

	scanf("%d", &t);

	while (t--) {
		int n, i;
		int len;
		int cnt = 0;
		scanf("%d", &n);
		getchar();

		for (i = 0; i < n; ++i) {
			long long int a;
			scanf("%lld", &a);
			ar[i] = a;
		}

		while (--n) {
			long long int next;
			while (ar[n-1] >= ar[n] && ar[n-1] != 0) {
				ar[n-1] /= 2;
				++cnt;
			}

			if (ar[n-1] == ar[n]) {
				cnt = -1;
				break;
			}
		}		

		printf("%d\n", cnt);

	}
	return (0);
}
