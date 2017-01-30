/*
 * cc_holder.c
 *
 *  Created on: 27Jan.,2017
 *      Author: j
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

#include "../commons.h"
#include "cc_holder.h"

#define _file "C:\\Users\\j\\workspace\\CCcsvParser\\convertcsv.csv"
#define _file2 "C:\\Users\\j\\workspace\\CCcsvParser\\convertcsv_sorted.csv"

const char* inject_record(char* line)
{

	return NULL;
}

Bool init_list(cc_holder_t ** head, cc_holder_t ** tail) {

	if(*head != NULL || *tail != NULL) {
		puts("\n\n!!=== ERROR - EXISTING LIST DETECTED ===!!\n\n");
		return false;
	}

	cc_holder_t * tmp_node;

	FILE* input_file = fopen(_file, "r");

	char record[1024];
	fields field = last;
	char *tmp, *tok;

	while (fgets(record, 1024, input_file))
	{
		tmp = strdup(record);
		field = last;

		if((tmp_node = malloc(sizeof(cc_holder_t))) == NULL) return false;

		for (tok = strtok(tmp, ",");
			tok && *tok;
			tok =  strtok(NULL, ",\n"))	{

			switch(field) {
				case(last):
						tmp_node->last_name = tok;
						break;
				case(first):
						tmp_node->first_name = tok;
						break;
				case(cc_no):
						tmp_node->cc = tok;
						break;
				case(money):
						remove_chars(tok);
						tmp_node->cents = (unsigned int) (atoi(tok));
						break;
				default:
					break;
			}

			field++;
		}

		if(*head == NULL) {
			tmp_node->next = NULL;
			tmp_node->previous = NULL;
			*head = tmp_node;
		} else if(*tail == NULL) {
			(*head)->next = tmp_node;
			tmp_node->previous = *head;
			tmp_node->next = NULL;
			*tail = tmp_node;
		} else {
			tmp_node->previous = *tail;
			tmp_node->next = NULL;
			(*tail)->next = tmp_node;
			*tail = tmp_node;
		}

	}

	if(fclose(input_file) == 0) return true;
		else
	return false;
}

void destroy_cc_list(cc_holder_t ** head, cc_holder_t ** last) {

	if(*head == NULL) {
		puts("\n!!--NO LIST FOUND. PLEASE INITIALIZE!--!!\n");
		return;
	}

	//end to start
	cc_holder_t * temp;
	temp = *last;
	while(temp->previous != NULL) {
		temp = (*last)->previous;
		free(*last);
		*last = NULL;
		*last = temp;
	}
	free(*head); // destroying head
	*head = NULL; // setting NULL
	*last = NULL;
}

void print_cc_list(cc_holder_t ** head) {

	if(*head == NULL) {
		puts("\n!!--NO LIST FOUND. PLEASE INITIALIZE!--!!\n");
		return;
	}

	int i = 0;
	cc_holder_t * current = *head;
	int c = 0;

	while(current != NULL) {
		c = current->cents % 100;
		printf("Object no. [%i] with person [%s %s] has cc no [%s] and has [$%d%s%d]\n",
				i++,
				current->first_name,
				current->last_name,
				current->cc,
				(unsigned int) (current->cents / 100),
				(c < 10)  ? ".0" : ".",
				c);
		current = current->next;
	}
}

void remove_chars(char *str) {
	char *read = str, *write = str;
	while(*read) {
		*write = *read++;
		write += ((*write != ',') && (*write != '$') && (*write != '.'));
	}
	*write = '\0';
	str = write;
}

void bubbleSort(cc_holder_t ** head) {

	int i = 0;
	while(1) {
		if(bubbleSortInner(*head) == false) break;
		while((*head)->previous != NULL) *head = (*head)->previous;
		i++;
	}

	printf("number of iterations [%i]\n", i);

}

Bool bubbleSortInner(cc_holder_t * node) {

	//TODO pointer swap instead of value swap
	//pointer swap proving to be problematic, perhaps pop/push
	// Update. Can look confusing but its do able.
	/*
	 * Have to consider 4 elements, previous (1), current (2), next(3) & next->next (4)
	 *
	 * 4.previous = 2
	 * 1.next = 3
	 *
	 * 2.next = 4
	 * 2.previous = 1
	 *
	 * 3.previous = 1
	 * 3.next = 2
	 *
	 */

	Bool swapped = false;
	cc_holder_t *temp;

	while(node->next != NULL) {
		if(node->cents > node->next->cents) {

			temp = node->next;

			if(node->next->next != NULL) {
				node->next->next->previous = node;
				node->next = node->next->next;
			} else {
				node->next = NULL;
			}

			if(node->previous != NULL) {
				node->previous->next = temp;
				temp->previous = node->previous;
			} else {
				temp->previous = NULL;
			}

			temp->next = node;
			node->previous = temp;

			swapped = true;
		} else {
			node = node->next;
		}
	}
	return swapped;
}

Bool writeToFile(cc_holder_t * node) {

	FILE* output_file = fopen(_file2, "w");
	int c = 0;

	while(node != NULL) {
		c = node->cents % 100;
		fprintf(output_file, "%s,%s,%s,$%d%s%d\n",
				node->last_name,
				node->first_name,
				node->cc,
				(unsigned int) (node->cents / 100),
				(c < 10)  ? ".0" : ".",
				c);

		node = node->next;
	}
	while(node != NULL) node = node->previous;

	if(fclose(output_file) == 0) return true;
		else
	return false;

}
