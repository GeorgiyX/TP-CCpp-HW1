#ifndef TP_CCPP_HW1_MODULE_H
#define TP_CCPP_HW1_MODULE_H

/**
 * A single-linked list node that stores country parameters and a pointer to the next element.
 */
typedef struct country_node country_node;
/**
 * Creates a new node.
 * @return new node or NULL.
 */
country_node *create_node();
/**
 * Frees up the memory allocated to the node.
 * @param node - node to free. If it is null, then the function does nothing.
 */
void free_node(country_node *node);

/**
 * Creates a node and reads the country parameters to it from stdin
 * @return created node or NULL
 */
country_node *read_country_node();
/**
 * Adds node_to_add to the linked list before the first node greater than or equal to node_to_add.
 * @param head - pointer to the first item in the list. If it is null, then the function does nothing.
 * @param node_to_add - pointer to the element to add. If it is null, then the function does nothing.
 */
void insert_node(country_node *head, country_node *node_to_add);
/**
 * Outputs the country parameters to stdout.
 * @param head - pointer to the first item in the list. If it is null, then the function does nothing.
 */
void print_list(country_node *head);
/**
 * Frees up the memory allocated for the list nodes.
 * @param head - pointer to the first item in the list. If it is null, then the function does nothing.
 */
void free_list(country_node *head);

#endif //TP_CCPP_HW1_MODULE_H
