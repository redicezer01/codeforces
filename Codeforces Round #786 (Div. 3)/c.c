#include <stdio.h>
#include <string.h>

#define MAXSSIZ 52

int cins(char *t, char c);

int main()
{
	int q, i;
	char s[MAXSSIZ], t[MAXSSIZ];

	scanf("%d", &q);
	getchar();
	
	for (i = 0; i < q; ++i) {
		int sl, tl, ain = 0;
		fgets(s, MAXSSIZ, stdin); 
		fgets(t, MAXSSIZ, stdin); 

		sl = strlen(s);
		tl = strlen(t);

		if (s[sl-1] == '\n')
			s[--sl] = '\0';
		if (t[tl-1] == '\n')
			t[--tl] = '\0';
		
		ain = cins(t, 'a');
		if (ain && tl == 1)
			printf("1\n");
		else if (ain)
			printf("-1\n");
		else {
			printf("%llu\n", 1ULL << sl);
		}
	}
	return (0);
}

int cins(char *t, char c)
{
	while (*t != '\0')
		if (*t++ == c)
			return 1;
	return 0;
}
