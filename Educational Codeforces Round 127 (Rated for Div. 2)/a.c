#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifdef BENCH
#include <time.h>
float st, et;
#endif


#define SMAX 51
#define SMIN 1
#define TMAX 1000
#define TMIN 1

#define VALID_T(t) (TMIN <= t && t <= TMAX)


int main()
{
#ifdef BENCH
	st = clock();
#endif
	char s[SMAX];
	int t = 0, rt = 0;
	int i, j;
	char **set;


	scanf("%d", &t);
	if (!VALID_T(t))
		return (0);
	getchar();
	
	set = (char **) calloc(t, sizeof(char *));

	for (i = 0; i < t; ++i) {
		set[i] = (char *) calloc(SMAX, sizeof(char));	
		/*
		fgets(s, SMAX, stdin);
		strcpy(set[i], s);
		*/
		scanf("%s", set[i]);
	}
	rt = i;

	
	for (i = 0; i < rt; ++i) {
		int yes = 1;
		char *str = set[i];
		int len = strlen(str);
		/*
		if (str[len-1] == '\n')
			str[len-1] = '\0';
		*/
		if (len == 0)
			yes = 0;
		for (j = 0; j < len && str[j] != '\0' && str[j] != '\n'; ++j) {
			char prev = '0', next = '0';	
			if (j > 0) {
				prev = str[j-1];
			}
			if (j < len) {
				next = str[j+1];
			}
			if (str[j] != prev && str[j] != next) {
				yes = 0;
				break;
			}
				
		}
		printf("%s\n", (yes) ? "YES" : "NO");	
		
		free(set[i]);
	}
	free(set);

#ifdef BENCH
	et = clock();
	printf("\nbench: %f\n", (et - st) / CLOCKS_PER_SEC);
#endif
	return (0);
}
