#include <stdio.h>

int main()
{
	int t;
	long long int a[200][200];

	scanf("%d", &t);
	getchar();

	while (t--) {
		int n, m, i, j;

		scanf("%d %d", &n, &m);
		getchar();
	
		long long int ai;
		for (i = 0; i < n; ++i) {
			for (j = 0; j < m; ++j) {
				scanf("%lld", &ai);
				a[i][j] = ai;	
			}
			getchar();
		}
		
		long long int max;	
		max = 0;
		for (i = 0; i < n; ++i) {
			for (j = 0; j < m; ++j) {
			
				int k, l;
				long long int suml, sumr;
				suml = sumr = 0;

				if (i >= j) {
					k = i - j;
					l = 0;
				} else {
					l = j - i;
					k = 0;
				}

				for (; k < n && l < m; ++k, ++l) {
					suml += a[k][l];
				}


				if ((i+j) < n) {
					k = i + j;
					l = 0;
				} else {
					l = j - (n-(i+1));
					k = n-1;
				}

				for (; k >= 0 && l < m; --k, ++l) {
					sumr += a[k][l];
				}
				
				if (max < (suml + sumr - a[i][j]))
					max = suml + sumr - a[i][j];
			}
		}

		
		printf("%lld\n", max);
	}

	return (0);
}
