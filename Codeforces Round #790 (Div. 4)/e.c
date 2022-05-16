#include <stdio.h>
#include <stdlib.h>

#define MAXN ((long long int) ((1.5E+5)+1))

int main()
{
	int t;
	struct node {
		long long int v;
		int used;
		struct node *left, *right;
	}

	struct node *root;
	struct node *elem;
	struct node *new;

	scanf("%d", &t);
	getchar();

	a = (long long int *) calloc(MAXN, sizeof(long long int));

	while (t--) {
		long long int n, q, i;
		long long int max = 0;

		scanf("%lld %lld", &n, &q);
		getchar();
	
		for (i = 0; i < n; ++i) {
			long long int ai;
			scanf("%lld", &ai);

			new = (struct node *) malloc(sizeof(struct node));	
			new->v = ai;	
			new->used = 0;

			elem = root;
			while (elem


			max += ai;
		}	
		getchar();

		long long int min = -1;		
		long long int mc = -1;
		for (i = 0; i < q; ++i) {
			long long int qi;
			scanf("%lld", &qi);
			getchar();

			if (qi == max) {
				mc = n;
			} else if (qi < max) {
				
			} else {
				mc= -1;
			}
			
			printf("%lld\n", mc);	
		}
		putchar('\n');
	}
	
	free(a);
	return (0);
}
