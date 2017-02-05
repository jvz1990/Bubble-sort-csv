/*
 * util.c
 *
 *  Created on: 3Feb.,2017
 *      Author: j
 */

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

void disp_arguments(int argc, char ** argv) {
	int i = 0;
	for(; i < argc; ++i) {
		printf("argv[%d]: %s\n", i, *(argv+i));
	}
}

char * getline(void) {
    char * line = malloc(100), * linep = line;
    size_t lenmax = 100, len = lenmax;
    int c;

    if(line == NULL)
        return NULL;

    for(;;) {
        c = fgetc(stdin);
        if(c == EOF)
            break;

        if(--len == 0) {
            len = lenmax;
            char * linen = realloc(linep, lenmax *= 2);

            if(linen == NULL) {
                free(linep);
                return NULL;
            }
            line = linen + (line - linep);
            linep = linen;
        }

        if((*line++ = c) == '\n')
            break;
    }
    *(--line) = '\0';
    return linep;
}
