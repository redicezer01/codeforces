#include <stdio.h>

int main()
{
	int n, cnt = 0;
	scanf("%d\n", &n);

	while (n--) {
		int p,v,t;
		scanf("%d %d %d\n", &p, &v, &t);
		if (p+v+t >= 2)
			++cnt;	
	}	
	printf("%d", cnt);
	return (0);
}
