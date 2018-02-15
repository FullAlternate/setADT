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

    set_t *c = set_create(cmpfunc);
    c->list->head = merge(a->list->head, b->list->head, cmpfunc);

    listnode_t *tmp1 = c->list->head;
    listnode_t *tmp2 = c->list->head->next;

    tmp1->prev = NULL;

    while(tmp2->next != NULL){
        while(tmp1->elem == tmp2->elem){
            tmp2-> = tmp2->next
        }

        tmp1->next->item = tmp2->item;
        tmp1->next->prev = tmp1;
        tmp1 = tmp1->next;
    }
    

    while(tmp1->next != NULL){
        list_poplast(c->list);
    }
    
    return c;
}

/*set_t *set_intersection(set_t *a, set_t *b){
    list_sort(a->list);
    list_sort(b->list);

    listnode_t *tmp1 = a->list->head;
    listnode_t *tmp2 = b->list->head;

    set_t *c = set_create(cmpfunc);

    while(tmp1 != NULL || tmp2 != NULL){
        if(tmp1->item == tmp2->item && tmp1->item != c->list->tail->prev){
            list_addlast(c->list);
            tmp1 = tmp1->next;
            tmp2 = tmp2->next;
        }

        else if(tmp1->item > tmp2->item){
            tmp2 = tmp2->next;
        }

        else{
            tmp1 = tmp1->next;
        }
    }
    
    return c;
}*/