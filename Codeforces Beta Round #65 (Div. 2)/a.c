#include <stdio.h>
#include <string.h>

#define MAXW 100

int main()
{
	int n, i;

	scanf("%d\n", &n);
	
	while (n--) {
		char s[MAXW+2];
		int len = 0;
		fgets(s, MAXW+2, stdin);
		len = strlen(s);
		if (s[len-1] == '\n')
			s[--len] = '\0';

		if (len > 10) {
			printf("%c%d%c\n", s[0], len-2, s[len-1]);
		} else {
			fputs(s, stdout);
			putchar('\n');
		}
	}	
	return (0);
}
