/*
 ============================================================================
 Name        : Bubble-sort-csv
 Author      : Johan van Zyl
 Version     : 0.90
 Copyright   : None! Educational purpose
 Description : Experimental C project for algorithm analysis and general learning

 	 	 	 	 The program loads a csv file similar to database table into a doubly linked list (circular).
 	 	 	 	 Then (for now) sorts it using bubble sort algorithm.

 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

#include "objects/cc_holder.h"
#include "commons.h"

#include <string.h>

int main(void) {

	cc_holder_t * head = NULL;

	if(init_list(&head) == false) return EXIT_FAILURE;

	print_cc_list(head);

	bubbleSort(head);

	print_cc_list(head);

	//printf("Success status %d", (writeToFile(head) == true ?  1 : 0));

	destroy_cc_list(&head);


	return EXIT_SUCCESS;
}
