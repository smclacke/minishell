/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   env.c                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/28 13:29:40 by dreijans      #+#    #+#                 */
/*   Updated: 2023/06/28 13:44:56 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

/* error message with perror */
void	error(char *string, int error)
{
	perror(string);
	exit(error);
}

void	list_env(char **envp)
{
	int i;
	if (envp == NULL)
		perror("env", errno);
}

/*

	ft_split the envp
	then loop through the 2d array and make linked list from it?

	or loop through the env
	and per index make linked list from it?

*/