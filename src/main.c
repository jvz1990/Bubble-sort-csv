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

#include <cc_holder.h>
#include <commons.h>
#include <util.h>
#include <menu.h>

#include <string.h>


int main(int argc, char **argv) {

	cc_holder_t * head = NULL;
	char * filepath = NULL;

	if(argc > 1) {
		puts("\nThe program has received command line arguments\n");
		puts("Will process arguments and exit!\nArgument List:\n");
		disp_arguments(argc, argv);
	} else {
		choices choice;
		while(process_input(&choice) != false) {
			switch (choice) {
				case(ERR):
					puts("\n!!!Input Error!!!\n TRY AGAIN!\n");
					break;
				case(ONE):
					puts("Option 1 has been selected.\n");
					if(get_file_path(&filepath) == false) {
						printf("\n!! ERROR: file does not exist:\n[%s]\n", filepath);
					} else {
						printf("\n User has entered file location:\n[%s]\n", filepath);
					}
					break;
				case(TWO):
					puts("Option 2 has been selected.\n");
					break;
				case(THREE):
					puts("Option 3 has been selected.\n");
					break;
				case(FOUR):
					puts("Option 4 has been selected.\n");
					break;
				case(FIVE):
					puts("Option 5 has been selected.\n");
					break;
				case(SIX):
					puts("Option 6 has been selected.\n");
					break;
				case(SEVEN):
					puts("Option 7 has been selected.\n");
					break;
				case(EIGHT):
					puts("Option 8 has been selected.\n");
					break;
				case(NINE):
					puts("Option 9 has been selected.\n");
					break;
			}
		}

		puts("\n Goodbye! \n");
	}

	destroy_cc_list(&head);

	return EXIT_SUCCESS;
}
