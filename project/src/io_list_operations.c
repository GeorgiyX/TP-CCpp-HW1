#include <stdio.h>
#include "io_list_operations.h"

/* Number of parameters to read in the country_node structure */
const int PARAMETERS_TO_READ_COUNT = 3;

country_node *read_country_node() {
    country_node *node = create_node();
    if (!node) {
        return NULL;
    }
    if (scanf("%zd %zd %ms", &node->data.square, &node->data.population, &node->data.country_name)
        != PARAMETERS_TO_READ_COUNT || !node->data.square || !node->data.population) {
        free_node(node);
        return NULL;
    }
    node->data.density = ((double) node->data.population) / node->data.square;
    return node;
}

void print_list(const country_node *head) {
    while (head) {
        if (head->data.country_name) {
            printf("%zd %zd %.2f %s\n", head->data.square, head->data.population,
                   head->data.density, head->data.country_name);
        } else {
            printf("%zd %zd %.2f error_country_name\n", head->data.square, head->data.population, head->data.density);
        }
        head = head->next;
    }
}

country_node *get_ordered_list() {
    country_node *head = NULL;
    country_node *new = read_country_node();
    while (new) {
        if (insert_node(&head, new) < 0) {
            free_list(head);
            free_node(new);
            head = NULL;
            break;
        }
        new = read_country_node();
    }
    return head;
}
