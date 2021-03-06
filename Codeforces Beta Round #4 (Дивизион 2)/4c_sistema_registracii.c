#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* 635491 */
/* 251877 */
/* 971253 */

#define DB_SIZE ((unsigned) 635491)
#define MAX_NAME_LEN 40

#define strhash(s) strnhash(s, DB_SIZE)
#define VALID_N(n) (1 <= n && (unsigned int) n <= DB_SIZE)
#define VALID_NAME(name) (0 < strlen(name) && strlen(name) <= MAX_NAME_LEN)

#define ISNULL(item) ((item) == NULL)
#define DUPLI(item, newname) (!ISNULL(item) && (strcmp(item->name, newname) == 0))
#define COLLS(item, newname) (!ISNULL(item) && (strcmp(item->name, newname) != 0))

#define getnamed() {							\
		int c, j;						\
		for (j = 0; (c = getchar()) != '\n' && c != EOF; ++j) 	\
			name[j] = c;					\
		name[j] = '\0';						\
}									\

struct item {
	char name[MAX_NAME_LEN];
	unsigned int cnt;
	struct item *next;
};

int coll;
int dupl;
int firs;
struct item *buf;
unsigned int pos;

unsigned int strnhash(const char *s, int n);
unsigned int db_items_cnt(struct item *db[]);


void db_free(struct item *db[]);
struct item *lookup(struct item *db[], const char *name);
void add(struct item *db[], const char *name);

int main()
{
	int i, n;
	int skiped = 0;	/* invalid names count */
	char name[MAX_NAME_LEN];

	struct item **db = (struct item **) calloc(DB_SIZE, sizeof(struct item *));
	buf = (struct item *) calloc(110000, sizeof(struct item));

	/* number of requests */
	scanf("%d", &n);
	if (!VALID_N(n))
		return (0);
	i = getchar();

	/* process requests */
	for (i = 0; (i < n); ++i) {
		/* getname(name); */
		/* scanf("%s", name); */
		getnamed();

		if (!VALID_NAME(name)) {
			++skiped;
			continue;	
		}

		add(db, name); 

		*name = '\0';
	}

	/* debug stat */
	/*
	printf("duplicates: %d\n", dupl);
	printf("collisions: %d\n", coll);
	printf("skipped: %d\n", skiped);
	printf("first added: %d\n", firs);
	printf("total: %d\n", db_items_cnt(db));
	*/

	/* db_free(db); */
	free(db);	
	free(buf);

	return (0);
}

unsigned int db_items_cnt(struct item *db[])
{
	unsigned int i;
	unsigned int t = 0;
	for (i = 0; i < DB_SIZE; ++i)
		if (!ISNULL(db[i]))
			++t;	
	return t;
}

void db_free(struct item *db[])
{
	unsigned int i;
	struct item *cur;
	struct item *next;

	for (i = 0; i < DB_SIZE; ++i) {
		next = cur  = db[i];	
		while (!ISNULL(next)) {
			next = cur->next;
			free(cur);
			cur = next;
		}
	}
}

struct item *
lookup(struct item *db[], const char *name)
{
	struct item *np;
	
	for (np = db[strhash(name)]; !ISNULL(np); np = np->next)
		if (strcmp(np->name, name) == 0)
			return np;
	return NULL;
}

void add(struct item *db[], const char *name)
{
	struct item *cur = NULL, *next = NULL;
	unsigned int hash;
	char newname[MAX_NAME_LEN];

	strcpy(newname, name);

	/* duplicate */
	for ((next = cur = lookup(db, newname)); !ISNULL(next); next = lookup(db, newname)) {
		sprintf(newname, "%s%d", name, cur->cnt++);
	}
	
	/* output */
	if (!ISNULL(cur)) {
		printf("%s\n", newname);
		++dupl;
	} else {
		printf("OK\n");
	}

	hash = strhash(newname);
	cur = db[hash];

	if (COLLS(cur, newname)) {
		while (!ISNULL(next = cur->next)) {
			cur = next;
		}
		cur->next = &buf[pos++];
		cur = cur->next;
		++coll;
	} else {
		cur = &buf[pos++];
		db[hash] = cur;
	}

	strcpy(cur->name, newname);
	cur->cnt=1;
	cur->next = NULL;
}

unsigned int strnhash(const char *s, int n)
{
	unsigned int h = 0;
	int i;

	for (i = 0; s[i] != '\0'; ++i)
		h = h * 31 + s[i];

	return (h % n);
}
