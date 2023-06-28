/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 13:29:40 by dreijans      #+#    #+#                 */
/*   Updated: 2023/06/28 18:13:07 by djoyke        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/djoyke.h"

/* error message with perror */
void	error(char *string, int error)
{
	perror(string);
	exit(error);
}

/* function that puts env in a linked list */ 
void	list_env(char **envp, t_env *env)//?? declare i parameters or in function?
{
	int	i;
	
	i = 0;
	if (env == NULL)
		perror("env", errno);
	while (env[i] != NULL)
	{
		ft_lstnew(env[i]);
		ft_lstadd_back(node to list);
		i++;
	}
}


/*

	ft_split the envp
	then loop through the 2d array and make linked list from it?

	or loop through the env
	and per index make linked list from it?

*/