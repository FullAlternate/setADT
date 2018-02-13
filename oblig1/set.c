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


