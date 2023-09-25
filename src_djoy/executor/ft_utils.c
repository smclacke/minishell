/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_utils.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 16:47:04 by dreijans      #+#    #+#                 */
/*   Updated: 2023/09/14 14:56:41 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

/**
 * @param string argument given to perror
 * @param error int errno given to exit
 * @brief provides correct error message and exits
*/
void	mini_error(char *string, int error)
{
	perror(string);
	exit(error);
}

/**
 * @param s1 string to compare
 * @param s1 string or char to compare with
 * @brief compares 2 strings replace by the libft version without -n
 * @return difference if different or 0
 * old function:
*/
int	mini_strcmp(char *s1, char *s2)
{
	size_t	i;

	i = 0;
	if (!s1 || !s2)
		return (1);
	while (s1[i] || s2[i])
	{
		if ((unsigned char)(s1)[i] != (unsigned char)(s2)[i])
			return ((unsigned char)(s1)[i] - (unsigned char)(s2)[i]);
		i++;
	}
	return (0);
}

/**
 * @param data struct to be updated with fd's and 2d arrays for later use
 * @param env 
 * @brief intitializes struct before further use
*/
void	init_execute_struct(t_execute *data, t_env *env)
{
	data->fd_in = 0;
	data->fork_pid = 0;
	data->pipe_fd[READ] = 0;
	data->pipe_fd[WRITE] = 0;
	data->path = NULL;
	data->env_array = list_to_string(env);
}

/**
 * @param node node from parser linked list
 * @brief checks node->abso if it's an absolute path
 * @return true is absolute path
 * false if no absolute path
*/
bool	absolute_check(t_parser *node)
{
	if (!node->data->cmd)
		return (false);
	if (!ft_strncmp(node->data->cmd, "/", 1)
		&& access(node->data->cmd, F_OK) == 0)
		return (true);
	if (!ft_strncmp(node->data->cmd, "./", 2)
		&& access(node->data->cmd, F_OK) == 0)
		return (true);
	if (!ft_strncmp(node->data->cmd, "../", 3)
		&& access(node->data->cmd, F_OK) == 0)
		return (true);
	return (false);
}
