/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 13:29:40 by dreijans      #+#    #+#                 */
/*   Updated: 2023/06/29 16:36:39 by dreijans      ########   odam.nl         */
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
void	list_env(char **envp, t_env *env)
{
	int	i;

	i = 0;
	if (envp == NULL)
		error("env", errno);
	while (envp[i] != NULL)
	{
		ft_lstnew(envp[i]);
		ft_lstadd_back(env, envp);
		i++;
	}
}

/*

	ft_split the envp
	then loop through the 2d array and make linked list from it?

	or loop through the env
	and per index make linked list from it?

*/