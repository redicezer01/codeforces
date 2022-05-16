#include <stdio.h>

int main()
{
	int t;
	scanf("%d", &t);
	getchar();

	while (t--) {
		long long int n, ai, prev;
		int yes = 0;
		scanf("%lld", &n);
		getchar();
		
		scanf("%lld", &prev);
		while (--n) {
			scanf("%lld", &ai);
			if (ai >= prev)
				yes = 1;

			prev = ai;
		}	
		getchar();

		printf("%s\n", (yes) ? "YES" : "NO");
	}

	return (0);
}
