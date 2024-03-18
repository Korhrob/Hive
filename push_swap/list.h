#pragma once

typedef struct s_list {
	int		data;
	struct s_list* next;
} t_list;

// Basic
t_list* list_new(int data);
void	list_add_first(t_list** list, t_list* element);
void	list_add_last(t_list** list, t_list* element);
t_list* list_remove_first(t_list** list);
t_list* list_remove_last(t_list** list);

// Utils
int		list_count(t_list** list);
void	list_print(t_list** list);
void	list_print_both(t_list** a, t_list** b);
void	list_free(t_list** list);
int		list_smallest(t_list** list);
int		list_largest(t_list** list);
int		list_last(t_list** list);
int		list_index_of(t_list** list, int val);