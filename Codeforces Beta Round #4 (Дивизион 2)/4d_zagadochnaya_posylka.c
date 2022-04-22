#include <stdio.h>
#include <stdlib.h>

#define MAX_N 5000
#define MAX_WH (1E+6)
#define VALID_N(n) (1 <= n && n <= MAX_N) 
#define VALID_W(w) (1 <= w && w <= MAX_WH)
#define VALID_H(h) (1 <= h && h <= MAX_WH)
#define VALID_WH(w,h) (VALID_W(w) && VALID_H(h))

#define DEBUG_INFO() for (i = 0; i < rn; ++i)			\
			     printf("%u - %u:%u:%u:%p\n", 	\
			     ea[i].n, ea[i].w, ea[i].h,		\
			     ea[i].len, ea[i].envs);		\

struct envel {
	unsigned int n;
	unsigned int w;
	unsigned int h;
	unsigned int len;
	struct envel **envs;
};

struct envel *ea;

int main()
{
	unsigned int n, w, h;	
	unsigned int rn = 0;	/* readed count of lines */
	int i;

	/* input 1st line n, w, h */
	scanf("%u %u %u", &n, &w, &h);
	if (!VALID_N(n) || !VALID_WH(w,h))
		return 0;

	/* table of envelopes */
	ea = (struct envel *) calloc(n, sizeof(struct envel));

	/* input w and h of i-th envelop */
	unsigned wi, hi;
	while (scanf("%u %u", &wi, &hi) > 0 && rn < n) {
		ea[rn].n = rn+1;
		ea[rn].w = wi;
		ea[rn].h = hi;
		ea[rn].len= 0;
		ea[rn].envs = NULL;
		++rn;	
	}
	if (rn != n) {
		printf("n not equal to number of readed lines\n");
		return (0);
	}
	
	/* debug info */
	DEBUG_INFO(); 

	free(ea);

	return (0);
}
