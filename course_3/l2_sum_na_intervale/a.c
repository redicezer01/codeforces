#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define BENCH
#ifdef BENCH
#include <time.h>
float st, et;
#endif

#define N ((int) 1E+6)
#define WSIZE 10
#define LLI long long int
#define BSIZ 8192

#define VALID_N(n) (1 <= n && n <= N)
#define readw(s) _readw(s, WSIZE)
#define readwbuf(s) _readwbuf(s, WSIZE, buf, BSIZ)

void _readw(char *s, unsigned int size);
void _readwbuf(char *s, unsigned int size, char *buf, const int bufsiz);
void atolld(char *s, LLI *num);

int main()
{
#ifdef BENCH
	st = clock();
#endif

	char s[WSIZE+1];
	int i;
	LLI n ,ai, q;
	LLI *a, *b;
	static char *buf;

	/* input n */
	readw(s);
	atolld(s, &n);
	if (!VALID_N(n))
		return (0);
	
	/* alloc memory */
	a = (LLI *) calloc(n, sizeof(LLI));
	b = (LLI *) calloc(n+1, sizeof(LLI));
	buf = (char *) calloc(BSIZ, sizeof(char));

	b[0] = 0;

	/* input a and prefix sum to b */
	for (i = 0;  i < n; ++i) {
		readwbuf(s);
		atolld(s, &ai);
		a[i] = ai;	
		b[i+1] = a[i] + b[i];
	}

	/*	
	for (i = 0;  i <= n; ++i) {
		printf("%lld ", b[i]);
	}
	*/

#ifdef BENCH
	et = clock();
	printf("\nbench: %f\n", (et - st) / CLOCKS_PER_SEC);
#endif
	free(a);
	free(b);
	free(buf);
	return (0);
}

void _readw(char *s, unsigned int size)
{
	int i, c;

	for (i = 0; (i < size) && ((c=getchar()) != EOF 
	  	     && c != '\0' && c != '\n' && c != ' '); ++i) {
		s[i] = c;
	}
	s[i] = '\0';
}

void _readwbuf(char *s, unsigned int size, char *buf, const int bufsiz)
{
	static int pos, len;

	int i, j, c;
	for (i = 0; (i < size) && ((c = buf[pos]) != EOF 
	  	     && c != '\0' && c != '\n' && c != ' '); ++i) {
		if (pos == len) {
			pos = len = 0;
			for (j = 0; j < bufsiz; ++j) {
				buf[j] = c;
				++len;
			}
		}
		s[i] = c;
		++pos;
	}
	s[i] = '\0';
}

void atolld(char *s, LLI *num)
{
	int sign = 1;
	*num = 0;
	if (*s == '-')
		sign = -1;
		
	while (*s != '\0') {
		*num = (*num * 10) + (*s - '0');
		++s;	
	}
	*num *= sign;
}
