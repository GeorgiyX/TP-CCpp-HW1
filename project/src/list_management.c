#include <stdlib.h>
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

int insert_node(country_node **head, country_node *new) {
    if (!head || !new) { return -1; }
    country_node *previous = NULL;
    country_node *current = *head;
    while (current && current->data.population < new->data.population) {
        previous = current;
        current = current->next;
    }
    if (previous) {
        previous->next = new;
    } else {
        *head = new;
    }
    new->next = current;
    return 0;
}

void free_list(country_node *head) {
    country_node *node_to_free = NULL;
    while (head) {
        if (head->data.country_name) {
            free(head->data.country_name);
        }
        node_to_free = head;
        head = head->next;
        free(node_to_free);
    }
}
