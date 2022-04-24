#include <stdio.h>

int main()
{
	int n, k, ai, i = 1, cnt = 0, kv = 0;
	scanf("%d %d\n", &n, &k);

	while (n--) {
		scanf("%d\n", &ai);
		if (i == k)
			kv = ai;
		if (ai > 0)
			if ((i <= k) || (i > k && ai == kv))
				++cnt;	
		++i;
	}

	printf("%d\n", cnt);

	return (0);
}
