/*
 ============================================================================
 Name        : CCcsvParser.c
 Author      : j
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "objects/cc_holder.h"
#include "commons.h"

#include <string.h>

int main(void) {

	cc_holder_t * head = NULL;
	cc_holder_t * tail = NULL;

	if(init_list(&head, &tail) == false) return EXIT_FAILURE;

	print_cc_list(head);

	bubbleSort(head);

	print_cc_list(head);

	printf("Success status %d", (writeToFile(head) == true ?  1 : 0));

	destroy_cc_list(&head, &tail);


	return EXIT_SUCCESS;
}
