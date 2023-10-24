/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_one.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 16:47:04 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/24 17:32:19 by dreijans      ########   odam.nl         */
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
void	init_execute_struct(t_execute *data)
{
	data->fork_pid = -1;
	data->pipe_left[READ] = -1;
	data->pipe_left[WRITE] = -1;
	data->pipe_right[READ] = -1;
	data->pipe_right[WRITE] = -1;
	data->path = NULL;
	data->env_array = NULL;
	data->in = -1;
	data->out = -1;
	data->hdoc_fd = -1;
}

/**
 * @param str string to be freed
 * @param str2 string to be freed
 * @brief frees strings 
*/
void	free_strs(char *str, char *str2)
{
	free (str);
	free (str2);
}
