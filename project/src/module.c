#include <stdio.h>
#include <stdlib.h>
#include "module.h"

void test_redirect() {
    char *buf;
    scanf("%ms", &buf);
    printf("Прочитал такое: %s", buf );
    free(buf);
}
