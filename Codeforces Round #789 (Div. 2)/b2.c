#include <stdio.h>

int main()
{
	int t;
	scanf("%d", &t);
	getchar();

	while (t--) {
		int n, si, seq = 0, prev = -1, minop = 0;
		int minseq = 0;
		scanf("%d", &n);
		getchar();

		while (n--) {
			si = getchar();
			if (!seq) {
				++seq;
			} else if (prev == si) {
				++seq;
			} else if (seq % 2) {
				seq = 0;
				++minop;
			} else {
				++minseq;
				seq = 1;
			}	
			prev = si;
		}
		getchar();

		printf("%d %d\n", minop, minseq);
		
	}

	return (0);
}
