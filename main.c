
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct s_list
{
	void* content;
	struct s_list* next;
}	t_list;

t_list* ft_lstnew(void* content)
{
	t_list* element;

	element = malloc(sizeof(t_list));
	if (element == 0)
		return (0);

	element->content = content;
	element->next = 0;

	return (element);
}

t_list* ft_lstlast(t_list* lst)
{
	if (lst == 0)
		return (0);
	while (lst->next != 0)
		lst = lst->next;
	return (lst);
}

void	ft_lstadd_back(t_list** lst, t_list* new)
{
	t_list* prev;

	if (lst == 0)
	{
		printf("Null list, cant ft_lstadd_back\n");
		return;
	}

	if (*lst == 0) {

		printf("ft_lstadd_back - new\n");
		*lst = new;
		return;

	}

	prev = *lst;

	while (prev->next != 0)
		prev = prev->next;

	prev->next = new;

	printf("ft_lstadd_back\n");

}

void	ft_lstdelone(t_list* lst, void (*del)(void*))
{
	if (lst == 0)
		return;

	if (del != 0)
		del(lst->content);

	free(lst);
}

void	ft_lstclear(t_list** lst, void (*del)(void*))
{
	t_list* next;
	t_list* cur;

	if (lst == 0)
		return;

	next = 0;
	cur = *lst;

	while (cur != 0)
	{

		next = cur->next;
		ft_lstdelone(cur, del);
		cur = next;
	}

	*lst = 0;

	printf("lstclear done\n");

}

t_list* ft_lstmap(t_list* lst, void* (*f)(void*), void (*del)(void*))
{
	void* temp;
	t_list* start;
	t_list* cur;

	temp = 0;
	start = 0;
	while (lst != 0)
	{
		temp = f(lst->content);
		cur = ft_lstnew(temp);
		if (cur == 0)
		{
			ft_lstclear(&start, del);
			free(temp);
			return(0);
		}
		ft_lstadd_back(&start, cur);
		lst = lst->next;
	}
	return (start);
}

void	del_func(void* content)
{
	if (content == 0)
		return;

	printf("del_func\n");

	free(content);
}

void* f_func(void* content)
{
	void* copy;
	unsigned int	size;

	if (content == 0)
		return (0);

	size = strlen((char*)content);
	copy = malloc(size + 1);
	if (copy == 0)
		return (0);

	memcpy((char*)copy, (char*)content, size + 1);

	return (copy);
}

void	ft_printlst(t_list* lst, int len)
{

	if (lst == 0 || len == 0)
	{
		printf("ft_printlst - null list\n");
		return;

	}

	t_list* cur = lst;

	for (int i = 0; i < len; i++) {

		printf("lst[%d]->content %s : %p\n", i, (char*)cur->content, &(cur->content));
		cur = cur->next;

	}

}

char* ft_strcpy(char* s1, char* s2)
{
	int i;

	i = 0;
	while (s2[i])
	{
		s1[i] = s2[i]; // so this will make s1 = to whatever s2 is looping through the string
		i++;
	}
	s1[i] = s2[i];  // now that we are finsihing looping though s1[i] will equal s2[i]
	return (s1);
}

int	main(void)
{
	printf("- CList Test -\n");

	int		len = 3;
	char	strs[3][5] = { "str1", "str2", "str3" };
	char* tmp = 0;
	t_list** lst = (t_list**)malloc(sizeof(t_list*));
	*lst = 0;

	t_list* cur = 0;

	for (int i = 0; i < 3; i++) {

		tmp = (char*)malloc(strlen(strs[i]) + 1);

		if (tmp == 0)
		{
			printf("- Malloc fail -\n");
			break;
		}

		ft_strcpy(tmp, strs[i]);
		printf("strcpy %s -> %s\n", strs[i], tmp);
		printf("mem : original %p - new %p\n", &strs[i], &tmp);

		cur = ft_lstnew((void*)tmp);

		if (cur == 0)
		{
			printf("- Malloc fail -\n");
			break;
		}

		printf("new node->content %s\n", strs[i]);
		ft_lstadd_back(lst, cur);

	}

	printf("- lst -\n");

	ft_printlst(*lst, len);

	printf("- lstmap -\n");

	t_list* copy = ft_lstmap(*lst, f_func, del_func);

	ft_printlst(copy, len);

	printf("- lstclear -\n");

	ft_lstclear(&copy, del_func);

	ft_printlst(copy, len);

	return (0);
}
