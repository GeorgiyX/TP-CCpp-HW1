#include <stdlib.h>
#include <math.h>
#include <float.h>
#include "list_management.h"

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

int insert_node(country_node **head, country_node *insertable) {
    if (!head || !insertable) { return -1; }
    country_node *previous = NULL;
    country_node *current = *head;
    while (current && is_less(current->data.density, insertable->data.density)) {
        previous = current;
        current = current->next;
    }
    if (previous) {
        previous->next = insertable;
    } else {
        *head = insertable;
    }
    insertable->next = current;
    return 0;
}

void free_list(country_node *head) {
    country_node *node_to_free = NULL;
    while (head) {
        node_to_free = head;
        head = head->next;
        free_node(node_to_free);
    }
}

int is_less(const double lhs, const double rhs) {
    return !(fabs(lhs - rhs) < DBL_EPSILON || lhs > rhs);
}
