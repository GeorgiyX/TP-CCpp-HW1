#ifndef TP_CCPP_HW1_PROJECT_INCLUDE_IO_LIST_OPERATIONS_H_
#define TP_CCPP_HW1_PROJECT_INCLUDE_IO_LIST_OPERATIONS_H_

#include "list_management.h"

/**
 * Creates a node and reads the country parameters to it from stdin
 * @return created node or NULL
 */
country_node *read_country_node();

/**
 * Outputs the country parameters to stdout. If the country name is represented by an empty pointer,
 * "error_country_name" will be printed instead.
 * @param head - pointer to the first item in the list. If it is null, then the function does nothing.
 */
void print_list(country_node *head);

/**
 * Generates an ordered list of countries based on data from stdin
 * @return pointer to the first item in the list or NULL
 */
country_node *get_ordered_list();

#endif  // TP_CCPP_HW1_PROJECT_INCLUDE_IO_LIST_OPERATIONS_H_
