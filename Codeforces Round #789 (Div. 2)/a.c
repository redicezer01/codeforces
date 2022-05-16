#include <stdio.h>

int main()
{
	int t, i;
	int aa[101];
	scanf("%d", &t);
	getchar();
	
	while (t--) {
		int n, a;
		int zc = 0;
		int isin = 0;

		scanf("%d", &n);
		getchar();

		for (i = 0; i < 101; ++i)
			aa[i] = 0;
		
		for (i = 0; i < n; ++i) {
			
			scanf("%d", &a);
			getchar();
			
			if (!a) {
				++zc;
			} else if (!isin) {
				if (aa[a])
					isin = 1;
				else  
					++aa[a];
			}
		}
		n -= zc;
		if (!zc && !isin)
			++n;
			
		printf("%d\n", n);	
			
	}

	return (0);
}
