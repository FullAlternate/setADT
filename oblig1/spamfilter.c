/* Author: Steffen Viken Valvaag <steffenv@cs.uit.no> */
#include "list.h"
#include "set.h"
#include "common.h"

void printset(char *name, set_t *a)
{
	printf("check");
	set_iter_t *iter;
	char *elem;
	
	printf("%s:   [", name);
	
	/* Validate the result sets */
	iter = set_createiter(a);
	while(set_hasnext(iter))
	{
		elem = (char *)set_next(iter);
		printf("%s", elem);
		if(set_hasnext(iter))
			printf(", ");
	}
	
	set_destroyiter(iter);

	printf("]\n");
}

/*
 * Case-insensitive comparison function for strings.
 */
static int compare_words(void *a, void *b)
{
    return strcasecmp(a, b);
}

/*
 * Returns the set of (unique) words found in the given file.
 */
static set_t *tokenize(char *filename)
{
	set_t *wordset = set_create(compare_words);
	list_t *wordlist = list_create(compare_words);
	list_iter_t *it;
	FILE *f;
	
	f = fopen(filename, "r");
	if (f == NULL) {
		perror("fopen");
		fatal_error("fopen() failed");
	}
	tokenize_file(f, wordlist);
	
	it = list_createiter(wordlist);
	while (list_hasnext(it)) {
		set_add(wordset, list_next(it));		
	}
	list_destroyiter(it);
	list_destroy(wordlist);
	return wordset;
}

/*
 * Prints a set of words.
 */
static void printwords(char *prefix, set_t *words)
{
	set_iter_t *it;
	
	it = set_createiter(words);
	printf("%s: ", prefix);
	while (set_hasnext(it)) {
		printf(" %s", set_next(it));
	}
	printf("\n");
	set_destroyiter(it);
}

char *spamcheck(int spamAmount){

	char *check;
	if(spamAmount > 0){
		check = "SPAM";
	} else {
		check = "Not spam";
	}

	return check;
}

/*
 * Main entry point.
 */
int main(int argc, char **argv)
{
	char *spamdir, *nonspamdir, *maildir;
	
	if (argc != 4) {
		fprintf(stderr, "usage: %s <spamdir> <nonspamdir> <maildir>\n",
				argv[0]);
		return 1;
	}
	spamdir = argv[1];
	nonspamdir = argv[2];
	maildir = argv[3];

	list_t *spamlist = find_files(spamdir);
	list_t *nonspamlist = find_files(nonspamdir);
	list_t *maillist = find_files(maildir);
	
	list_iter_t *spamIter = list_createiter(spamlist);
	list_iter_t *nonspamIter = list_createiter(nonspamlist);
	list_iter_t *mailIter = list_createiter(maillist);

	set_t *s1 = tokenize(list_next(spamIter));

	while(list_hasnext(spamIter) == 1){
		set_t *s2 = tokenize(list_next(spamIter));

		s1 = set_intersection(s1, s2);
	}


	set_t *n1 = tokenize(list_next(nonspamIter));

	while(list_hasnext(nonspamIter) == 1){
		set_t *n2 = tokenize(list_next(nonspamIter));

		n1 = set_union(n1, n2);

	}


	set_t *combinedSet = set_difference(s1, n1);

	while(list_hasnext(mailIter) == 1){
		void *name = list_next(mailIter);
		
		set_t *m = tokenize(name);
		m = set_intersection(m, combinedSet);		
		int size = set_size(m);

		printf("%s: %d spam word(s) -> %s\n", name, size, spamcheck(size));
	}

    return 0;
}

