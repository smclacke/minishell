/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils_one.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/08/03 16:47:04 by dreijans      #+#    #+#                 */
/*   Updated: 2024/02/06 20:12:32 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

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
	data->count = 0;
	data->error = true;
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

/**
 * @param str string to be freed
 * @param str2 string to be freed
 * @brief frees strings
 * @todo can this be char *str as param?
 * added pointer to param of ft_split
 * @note changes ft_split
*/
char	**null_check(char *str, t_parser *temp)
{
	char		**words;
	int			i;

	i = 0;

	words = NULL;
	words = mini_split(str, '=');
	// while(words[i] != NULL)
	// {
	// 	printf("word = %s\n", words[i]);
	// 	i++;
	// }
	if (words == NULL)
		mini_error(E_GENERAL, temp);
	if (words[0] == NULL)
	{
		ft_free_arr(words);
		return (NULL);
	}
	return (words);
}
