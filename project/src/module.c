#include <stdio.h>
#include <stdlib.h>
#include "module.h"

struct country_node {
    struct {
        size_t square;
        size_t population;
        char *country_name;
    } data;
    country_node *next;
};

country_node *create_node() {
    return calloc(1, sizeof(country_node));
}

void free_node(country_node *node) {
    if (!node) { return; }
    if (node->data.country_name) {
        free(node->data.country_name);
    }
    free(node);
}
