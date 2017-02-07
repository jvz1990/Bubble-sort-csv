/*
 * object.h
 *
 *  Created on: 27Jan.,2017
 *      Author: j
 */

#ifndef OBJECTS_CC_HOLDER_H_
#define OBJECTS_CC_HOLDER_H_

#include <commons.h>

typedef struct cc_holder {
	char * last_name;
	char * first_name;
	char age;
	char * cc;
	UInt cents;

	struct cc_holder *next;
	struct cc_holder *previous;
} cc_holder_t;

typedef enum _fields {last, first, cc_no, money} fields;

Bool init_list(cc_holder_t ** head, char ** filepath);
void destroy_cc_list(cc_holder_t ** head);
void print_cc_list(cc_holder_t * head);
void remove_chars(char *str);
void bubbleSort(cc_holder_t * head, choices * choice);
Bool bubbleSortInner(cc_holder_t * head, choices * choice);
Bool writeToFile(cc_holder_t * head, char * filepath);
Bool swap(cc_holder_t * cur, choices * choice);
void searchPerson(cc_holder_t * head);

#endif /* OBJECTS_CC_HOLDER_H_ */
