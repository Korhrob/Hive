#include <stdlib.h>
#include <stdio.h>
#include "list.h"

t_list *list_new(int i) {
	t_list* element;

	element = malloc(sizeof(t_list));
	if (!element)
		return (0);
	element->data = i;
	element->next = 0;
	return (element);
}

void	list_add_first(t_list** list, t_list* element) {
	t_list* cur;

	cur = *list;
	if (cur == 0) {
		*list = element;
		return;
	}
	element->next = cur;
	*list = element;
}

void	list_add_last(t_list** list, t_list *element) {
	t_list *cur;

	cur = *list;
	if (cur == 0) {
		*list = element;
		return;
	}
	while (cur->next != 0)
		cur = cur->next;
	cur->next = element;
}

t_list	*list_remove_first(t_list** list) {
	t_list* cur;

	cur = *list;
	*list = cur->next;
	cur->next = 0;
	return (cur);
}

t_list* list_remove_last(t_list** list) {
	t_list* cur;
	t_list* prev;

	cur = *list;
	prev = cur;
	while (cur->next != 0) {
		prev = cur;
		cur = cur->next;
	}
	prev->next = 0;
	cur->next = 0;
	return (cur);
}

int	list_count(t_list** list) {
	t_list* cur;
	int	count;

	cur = *list;
	count = 0;
	if (cur == 0)
		return (0);
	while (cur != 0) {
		count++;
		cur = cur->next;
	}
	return (count);
}

void	list_print(t_list** list) {
	t_list* cur;

	cur = *list;
	if (cur == 0)
		return (0);
	while (cur != 0) {
		printf("%d\n", cur->data);
		cur = cur->next;
	}
}

void	list_print_both(t_list** a, t_list** b) {
	t_list* cur_a;
	t_list* cur_b;

	cur_a = *a;
	cur_b = *b;

	printf("---------\n");
	printf("A\tB\n");

	while (1) {

		if (cur_a != 0) {
			printf("%d", cur_a->data);
			cur_a = cur_a->next;
		}
		else
			printf("-");

		printf("\t");

		if (cur_b != 0) {
			printf("%d", cur_b->data);
			cur_b = cur_b->next;
		}
		else
			printf("-");

		printf("\n");

		if (cur_a == 0 && cur_b == 0)
			break;
	
	}

}

void	list_free(t_list** list) {
	t_list* cur;
	t_list* next;

	cur = *list;
	while (cur != 0) {
		next = cur->next;
		free(cur);
		cur = next;
	}
	free(list);
	list = 0;
}

int	list_smallest(t_list** list) {
	t_list* cur;
	int	i;

	if (*list == 0)
		return (0);
	cur = *list;
	i = cur->data;
	while (cur != 0) {
		if (cur->data < i)
			i = cur->data;
		cur = cur->next;
	}
	return (i);
}

int	list_largest(t_list** list) {
	t_list* cur;
	int	i;

	if (*list == 0)
		return (0);
	cur = *list;
	i = cur->data;
	while (cur != 0) {
		if (cur->data > i)
			i = cur->data;
		cur = cur->next;
	}
	return (i);
}

// searched for value in list and returns its index or -1 if not found
int	list_index(t_list** list, int (*f)(int, int), int value) {
	t_list* cur;
	int index;

	cur = *list;
	index = 0; // -1
	while (cur != 0) {
		if (f(cur->data, value))
			break;
		index++;
		cur = cur->next;
	}
	return (index);
}

int	list_last(t_list** list) {
	t_list* cur;
	int	r;

	cur = *list;
	r = 0;
	while (cur != 0) {
		r = cur->data;
		cur = cur->next;
	}
	return (r);
}

int	list_index_of(t_list** list, int val) {
	t_list* cur;
	int	index;

	cur = *list;
	index = 0;
	while (cur != 0) {
		if (cur->data == val)
			break;
		index++;
		cur = cur->next;
	}
	return (index);
}