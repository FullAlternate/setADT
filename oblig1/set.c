#include "list.h"
#include "set.h"
#include "common.h"
#include <stdlib.h>

struct set {
    list_t *list;
};

struct set_iter{
    list_iter_t *listIter;
};


set_t *set_create(cmpfunc_t cmpfunc) {
    set_t *s = malloc(sizeof(set_t));

    if(s == NULL){
        fatal_error("out of memory");
    }

    s->list = list_create(cmpfunc);

    return s;
}

void set_destroy(set_t *set) {
    list_destroy(set->list);
    free(set);
}

int set_size(set_t *set) {
    return list_size(set->list);
}

void set_add(set_t *set, void *elem){    
    if(list_contains(set->list, elem) == 0){
    list_addlast(set->list, elem);
    list_sort(set->list);
    }
}

int set_contains(set_t *set, void *elem){
    return list_contains(set->list, elem);
}


set_t *set_union(set_t *a, set_t *b){

    set_t *c = set_create(compare_strings);
    list_iter_t *iterA = list_createiter(a->list);
    list_iter_t *iterB = list_createiter(b->list);
    void *elemA;
    void *elemB;
    
    while(list_hasnext(iterA) == 1){
        elemA = list_next(iterA);

        if(list_contains(c->list, elemA) == 0){
            set_add(c, elemA);
        } 
    }

    while(list_hasnext(iterB) == 1){
        elemB = list_next(iterB);

        if(list_contains(c->list, elemB) == 0){
            set_add(c, elemB);
        } 
    }

    list_sort(c->list);
    return c;
}


/*
 * Returns the intersection of the two given sets; the
 * returned set contains all elements that are contained
 * in both a and b.
 */
set_t *set_intersection(set_t *a, set_t *b){

    set_t *c = set_create(compare_strings);
    list_iter_t *iterA = list_createiter(a->list);
    list_iter_t *iterB = list_createiter(b->list);
    void *elemA;
    void *elemB;

    while(list_hasnext(iterA) == 1){
        elemA = list_next(iterA);

        if(list_contains(c->list, elemA) == 0 && list_contains(b->list, elemA) == 1){
            set_add(c, elemA);
        } 
    }

    list_sort(c->list);
    return c;
}


/*
 * Returns the set difference of the two given sets; the
 * returned set contains all elements that are contained
 * in a and not in b.
 */
set_t *set_difference(set_t *a, set_t *b){

    set_t *c = set_create(compare_strings);
    list_iter_t *iterA = list_createiter(a->list);
    void *elemA;
    
    while(list_hasnext(iterA) == 1){
        elemA = list_next(iterA);

        if(list_contains(c->list, elemA) == 0 && list_contains(b->list, elemA) == 0){
            set_add(c, elemA);
        } 
    }

    list_sort(c->list);
    return c;
}


/*
 * Returns a copy of the given set.
 */
set_t *set_copy(set_t *set){
    set_t *c = set_create(compare_strings);
    list_iter_t *iter = list_createiter(set->list);
    void *elem;
    
    while(list_hasnext(iter) == 1){
        elem = list_next(iter);
        set_add(c, elem);
    }
    
    return c;
}





/*
 * Creates a new set iterator for iterating over the given set.
 */
set_iter_t *set_createiter(set_t *set){
    set_iter_t *iter = malloc(sizeof(set_iter_t));

    if(iter == NULL){
        fatal_error("out of memory");
    }

    iter->listIter = list_createiter(set->list);
    return iter;
}


/*
 * Destroys the given set iterator.
 */
void set_destroyiter(set_iter_t *iter){
    list_destroyiter(iter->listIter);
    free(iter);
}


/*
 * Returns 0 if the given set iterator has reached the end of the
 * set, or 1 otherwise.
 */
int set_hasnext(set_iter_t *iter){
    return list_hasnext(iter->listIter);
 
}


/*
 * Returns the next element in the sequence represented by the given
 * set iterator.
 */
void *set_next(set_iter_t *iter){
    
    return list_next(iter->listIter);

}