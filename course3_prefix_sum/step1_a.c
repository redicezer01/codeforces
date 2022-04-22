#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#ifdef BENCH
#include <time.h>
#endif

#define N ((long long int) 1E+6)
#define MIN_AI ((long long int) -1E+9)
#define MAX_AI ((long long int) 1E+9)
#define VALID_N(n) (1 <= n && n <= N)
#define VALID_AI(ai) (MIN_AI <= ai && ai <= MAX_AI)
#define SSIZE 256
#define CHUNK_SIZE 10
#define OUTBUFSIZ 32768

int atolld(char *s, long long int *num);
void lldtoa(long long int num, char *s);

void printstr(char *s);
void flushstr();
char *outbuf;
unsigned int outpos;

int main()
{

#ifdef BENCH
	double st, et;
#endif
	long long int n, i;
	long long int *a, *b;	
	char s[SSIZE];
	char chunk[CHUNK_SIZE];
#ifdef BENCH
	st = clock();
#endif
	a = (long long int *) calloc(N, sizeof(long long int));
	b = (long long int *) calloc(N+1, sizeof(long long int));
	outbuf = (char *) calloc(OUTBUFSIZ, sizeof(char));

	fgets(s, SSIZE, stdin);	
	s[strlen(s)] = '\0';
	atolld(s, &n);
	if (!VALID_N(n))
		return (0);

	int chi = 0;
	int numcnt = 0;
	/* input */
	while ((fgets(s, SSIZE, stdin) != NULL) && (numcnt <= n)) {
		int len = strlen(s);		
		i = 0;
		while (s[i] != '\0') {
			if (s[i] == ' ' || s[i] == '\n') {
				chunk[chi] = '\0';
				chi = 0;
				/* converting */
				atolld(chunk, &a[numcnt]);
				if (!VALID_AI(a[numcnt])) {
					return (0);
				}
				++numcnt;
			} else {
				chunk[chi] = s[i];	
				++chi;
			}
			++i;
		}
	}
	/* end input */

	b[0] = 0;
	printf("0 ");
	for (i = 1; i <= numcnt; ++i) {
		b[i] = b[i-1] + a[i-1];
		lldtoa(b[i], chunk);
		printstr(chunk);
		/*	
		fputs(chunk, stdout);
		putchar(' ');
		*/
	}
	flushstr();

	free(a);
	free(b);
	free(outbuf);
#ifdef BENCH
	et = clock();
	printf("\ntime: %f ns\n", (et-st) / CLOCKS_PER_SEC);
	printf("numcnt: %lld\n", numcnt);
#endif
	return (0);
}

int atolld(char *s, long long int *num)
{
	long long int sign = 1;
	
	*num = 0;

	if (*s == '-') {
		sign = -1;
		++s;	
	}
	
	while(isdigit(*s) && *s != '\0') {
		*num = (*num * (long long int) 10) 
			+ (long long int) (*s - '0');
		++s;
	}
	*num *= sign;

	return 0;
}

void lldtoa(long long int num, char *s)
{
	long long int sign = 1;
	if (num == 0) {
		s[0] = '0';
		s[1] = '\0';
		return;
	}
		
	if (num < 0) {
		sign = -1;
		num = sign * num;
	}
	
	int i = 0;
	long long int tmp;
	while (num > 0) {
		tmp = num % 10;	
		s[i] = (tmp) + '0';
		num /= 10;
		++i;
	}
	if (sign < 0)
		s[i++] = '-';

	tmp = i;
	--i;
	int j = 0;
	/* reverse string */
	while (j < i) {
		char c;
		j = tmp-i-1;
		c = s[i], s[i] = s[j], s[j] = c;
		--i;
	}
	s[tmp]='\0';
}

void printstr(char *s)
{
	int i = 0;
	while (*s != '\0') {

		if (outpos >= OUTBUFSIZ) {
			fwrite(outbuf, 1, outpos, stdout);
			outpos = 0;
		}
		outbuf[outpos] = *s;
		++outpos;
		++i;
		++s;
		/*
		if (i < 10)
			++s;
		*/
	}	
	
	outbuf[outpos++] = ' ';
	outbuf[outpos] = '\0';
}

void flushstr()
{
	fwrite(outbuf, 1, outpos, stdout);
	outpos = 0;
}
