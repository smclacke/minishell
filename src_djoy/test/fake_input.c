/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fake_input.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/18 18:13:54 by dreijans      #+#    #+#                 */
/*   Updated: 2023/07/21 18:52:05 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"
/**
 * @param argvs data passed from environment splitted
 * @brief malloc's and init node for linked list containing: 
 * commands
 * @return node made
 * @todo 
 * 1) needs to add previous in case of doubly linked list
*/
t_command	*command_lstnew(char **commands)
{
	t_command	*new;

	new = (t_command *)malloc(sizeof(t_command));
	if (!new)
		return (NULL);
	new->arg = commands;
	new->next = NULL;
	return (new);
}

/**
 * @param lst linked list to loop through
 * @brief loops to list to go to last position
*/
t_command	*command_lstlast(t_command *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

/**
 * @param lst linked list
 * @param new new node to be added to linked list 
 * @brief loops through list to add the new node to the back
 * @todo adding previous in case of doubly linked list
*/
void	command_lstadd_back(t_command **lst, t_command *new)
{
	t_command	*last;

	if (*lst)
	{
		last = command_lstlast(*lst);
		last->next = new;
	}
	else
		*lst = new;
}

t_command	*init_command(void)
{
	t_command		*list;
	t_command		*new_node;
	int				i;
	static char		*argv0[3] = {"unset", "PATH", NULL};
	static char		*argv1[3] = {"cd", "src_djoy", NULL};
	static char		*argv2[2] = {"pwd", NULL};
	static char		*argv3[3] = {"echo", "hellowww", NULL};
	static char		*argv4[2] = {"env", NULL};
	static char		*argv5[3] = {"export", "djoyke=gek", NULL};
	static char		**argvs[7] = {argv0, argv1, argv2, argv3, argv4, argv5, NULL};

	i = 0;
	list = NULL;
	while (argvs[i])
	{
		new_node = command_lstnew(argvs[i]);
		command_lstadd_back(&list, new_node);
		i++;
	}
	return (list);
}

/**
 * @param env environment stored in linked list
 * @brief prints linked list containing env key or value
*/
void	print_list_command(t_command *list)
{
	int			i;

	while (list != NULL)
	{
		i = 0;
		while (list->arg && list->arg[i])
		{
			printf("%s\n", list->arg[i]);
			i++;
		}
		list = list->next;
	}
}
