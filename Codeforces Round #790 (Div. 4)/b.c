#include <stdio.h>

int main()
{
	int t;
	scanf("%d", &t);
	getchar();

	while (t--) {
		int n, i;
		long long int a[50], min = 0, sum = 0;
		scanf("%d", &n);
		getchar();
		
		i = n;
		while (i--) {
			long long int ai;
			scanf("%lld", &ai);
			getchar();
			if (!min)
				min = ai;
		
			if (min > ai)
				min = ai;
			a[i] = ai;
		}

		for (i = 0; i < n; ++i) {
			sum += (a[i] - min);
		}

		printf("%lld\n", sum);
		
	}

	return (0);
}
