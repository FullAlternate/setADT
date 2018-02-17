#include "list.h"
#include "set.h"
#include "common.h"
#include <stdlib.h>

struct set {
    list_t *list;
};


set_t *set_create(cmpfunc_t cmpfunc) {
    set_t *s = malloc(sizeof(set_t));
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
    list_addlast(set->list, elem);
}

int set_contains(set_t *set, void *elem){
    list_contains(set->list, elem);
}

set_t *set_union(set_t *a, set_t *b){
    list_sort(a->list);
    list_sort(b->list);

    set_t *c = set_create(compare_strings);

    list_iter_t *iterA = list_createiter(a->list);
    list_iter_t *iterB = list_createiter(b->list);
    list_iter_t *iterC = list_createiter(c->list);



    while(list_hasnext(iterA) == 1){

    
    if(list_next(iterA) <= list_next(iterB)){
        set_add(c, a->list->head->elem);
        
    }

    else {
        set_add(c, b->list->head->elem);
        list_next(iterB);
    }

    list_next(iterC);
}    
