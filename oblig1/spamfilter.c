/* Author: Steffen Viken Valvaag <steffenv@cs.uit.no> */
#include "list.h"
#include "set.h"
#include "common.h"

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

	set_t *s1 = tokenize("spam/spam1.txt");
	set_t *s2 = tokenize("spam/spam2.txt");
	set_t *s3 = tokenize("spam/spam3.txt");
	set_t *s4 = tokenize("spam/spam4.txt");

	s1 = set_intersection(s1, s2);
	s3 = set_intersection(s3, s4);
	s1 = set_intersection(s1, s3);

	set_t *n1 = tokenize("nonspam/nonspam1.txt");
	set_t *n2 = tokenize("nonspam/nonspam2.txt");
	set_t *n3 = tokenize("nonspam/nonspam3.txt");
	set_t *n4 = tokenize("nonspam/nonspam4.txt");

	n1 = set_union(n1, n2);
	n3 = set_union(n3, n4);
	n1 = set_union(n1, n3);
	set_t *combinedSet = set_difference(s1, n1);

	char *mc1 = "mail/mail1.txt";
	char *mc2 = "mail/mail2.txt";
	char *mc3 = "mail/mail3.txt";
	char *mc4 = "mail/mail4.txt";
	char *mc5 = "mail/mail5.txt";

	set_t *m1 = tokenize(mc1);
	m1 = set_intersection(m1, combinedSet);

	set_t *m2 = tokenize(mc2);
	m2 = set_intersection(m2, combinedSet);

	set_t *m3 = tokenize(mc3);
	m3 = set_intersection(m3, combinedSet);

	set_t *m4 = tokenize(mc4);
	m4 = set_intersection(m4, combinedSet);
	
	set_t *m5 = tokenize(mc5);
	m5 = set_intersection(m5, combinedSet);
	
	int sizem1 = set_size(m1);
	int sizem2 = set_size(m2);
	int sizem3 = set_size(m3);
	int sizem4 = set_size(m4);
	int sizem5 = set_size(m5);

	printf("%s: %d spam word(s) -> %s\n", mc1, sizem1, spamcheck(sizem1));
	printf("%s: %d spam word(s) -> %s\n", mc2, sizem2, spamcheck(sizem2));
	printf("%s: %d spam word(s) -> %s\n", mc3, sizem3, spamcheck(sizem3));
	printf("%s: %d spam word(s) -> %s\n", mc4, sizem4, spamcheck(sizem4));
	printf("%s: %d spam word(s) -> %s\n", mc5, sizem5, spamcheck(sizem5));

    return 0;
}

