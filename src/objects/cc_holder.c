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

Bool init_list(cc_holder_t ** head, cc_holder_t ** tail) {

	if (*head != NULL || *tail != NULL) {
		puts("\n\n!!=== ERROR - EXISTING LIST DETECTED ===!!\n\n");
		return false;
	}

	cc_holder_t * tmp_node;

	FILE* input_file = fopen(_file, "r");

	char record[1024];
	fields field = last;
	char *tmp, *tok;

	while (fgets(record, 1024, input_file)) {
		tmp = strdup(record);
		field = last;

		if ((tmp_node = malloc(sizeof(cc_holder_t))) == NULL)
			return false;

		for (tok = strtok(tmp, ","); tok && *tok; tok = strtok(NULL, ",\n")) {

			switch (field) {
			case (last):
				tmp_node->last_name = tok;
				break;
			case (first):
				tmp_node->first_name = tok;
				break;
			case (cc_no):
				tmp_node->cc = tok;
				break;
			case (money):
				remove_chars(tok);
				tmp_node->cents = (unsigned int) (atoi(tok));
				break;
			default:
				break;
			}

			field++;
		}

		if (*head == NULL) {
			tmp_node->next = NULL;
			tmp_node->previous = NULL;
			*head = tmp_node;
		} else if (*tail == NULL) {
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

	if (fclose(input_file) == 0)
		return true;
	else
		return false;
}

void destroy_cc_list(cc_holder_t ** head, cc_holder_t ** last) {

	if (*head == NULL) {
		puts("\n!!--NO LIST FOUND. PLEASE INITIALIZE!--!!\n");
		return;
	}

	//end to start
	cc_holder_t * temp;
	temp = *last;
	while (temp->previous != NULL) {
		temp = (*last)->previous;
		free(*last);
		*last = NULL;
		*last = temp;
	}
	free(*head); // destroying head
	*head = NULL; // setting NULL
	*last = NULL;
}

void print_cc_list(cc_holder_t * head) {

	if (head == NULL) {
		puts("\n!!--NO LIST FOUND. PLEASE INITIALIZE!--!!\n");
		return;
	}

	int i = 0;
	cc_holder_t * current = head;
	int c = 0;

	while (current != NULL) {
		c = current->cents % 100;
		printf("Object no. [%i] with person [%s %s] has cc no [%s] and has [$%d%s%d]\n",
				i++, current->first_name,
				current->last_name,
				current->cc,
				(unsigned int) (current->cents / 100),
				(c < 10) ? ".0" : ".",
				c);
		current = current->next;
	}
}

void remove_chars(char *str) {
	char *read = str, *write = str;
	while (*read) {
		//write same position as read
		*write = *read++;
		//write does not include characters below
		write += ((*write != ',') && (*write != '$') && (*write != '.'));
	}
	*write = '\0';
	str = write;
}

void bubbleSort(cc_holder_t * head) {

	/*
	 * Essentially start from the head and find an item to 'bubble up'
	 * until there are items to 'bubble up'.
	 * TODO optimize algorithm to exclude highest values -> need counter and chain size counter
	 */
	int i = 0;
	while (1) {
		if (bubbleSortInner(head) == false)
			break;
		while (head->previous != NULL)
			head = head->previous;
		i++;
	}

	printf("number of outer iterations [%i]\n", i);

}

Bool bubbleSortInner(cc_holder_t * node) {

	// Update. Can look confusing but pointer swap is do able.
	/*
	 * Have to consider 4 elements, previous (1), current (2), next(3) & next->next (4)
	 * So swap positions 2 & 3. 1 & 4 have to be corrected as well (prev/next ptr)
	 *
	 * 4.previous = 2 //outer 2
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
	//UInt i = 0;

	while (node->next != NULL) {
		if (node->cents > node->next->cents) {

			temp = node->next;

			if (node->next->next != NULL) {
				node->next->next->previous = node; //4 pointing to 2
				node->next = node->next->next; //2 pointing to 4
			} else {
				node->next = NULL; // else there will be no next node to point to
			}

			if (node->previous != NULL) {
				node->previous->next = temp; //1 pointing to 3
				temp->previous = node->previous; //3 pointing to 1
			} else {
				temp->previous = NULL; // dealing with the head
			}

			temp->next = node; //3 = 2
			node->previous = temp; //2 = 3

			swapped = true;
		} else {
			node = node->next;
		}
		//i++;
	}
	//printf("number of inner iterations [%d]\n", i);
	return swapped;
}

Bool writeToFile(cc_holder_t * node) {

	FILE* output_file = fopen(_file2, "w");
	int c = 0;

	while (node != NULL) {
		c = node->cents % 100;
		fprintf(output_file,
				"%s,%s,%s,$%d%s%d\n",
				node->last_name,
				node->first_name,
				node->cc, (unsigned int) (node->cents / 100),
				(c < 10) ? ".0" : ".", c);

		node = node->next;
	}
	while (node != NULL)
		node = node->previous; // reverse head to beginning

	if (fclose(output_file) == 0)
		return true;
	else
		return false;

}
