#include <stdio.h>
#include "io_list_operations.h"

int main() {
    country_node *head = get_ordered_list();
    if (!head) {
        printf("can't get country list");
        return 1;
    }
    print_list(head);
    free_list(head);
    return 0;
}
