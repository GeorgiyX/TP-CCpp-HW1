#ifndef TP_HW1_LIST_MANAGEMENT
#define TP_HW1_LIST_MANAGEMENT

/**
 * A single-linked list node that stores country parameters and a pointer to the next element.
 */
typedef struct country_node {
    struct {
        size_t square;
        size_t population;
        char *country_name;
    } data;
    struct country_node *next;
} country_node;

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
 * Adds insertable to the linked list before the first node greater than or equal to insertable.
 * If such a node is head (or the list is empty), then head will also be overwritten with insertable.
 * @param head - pointer to pointer the first item in the list.
 * @param insertable - pointer to the element to add.
 * @return 0 if the node is added to the list or -1 otherwise
 */
int insert_node(country_node **head, country_node *insertable);

/**
 * Frees up the memory allocated for the list nodes.
 * @param head - pointer to the first item in the list. If it is null, then the function does nothing.
 */
void free_list(country_node *head);

#endif  // TP_HW1_LIST_MANAGEMENT
