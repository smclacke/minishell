/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   builtin_utils_two.c                                :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/09 19:27:49 by dreijans      #+#    #+#                 */
/*   Updated: 2023/11/02 17:06:46 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

/**
 * @param temp temporary placeholder
 * @param str old working directory string
 * @param env environment in linked list
 * @brief replaces the value of set key in the environment
 * @todo 
 * this you?
 * fix after sarah fixed leaks
 * Direct leak of 57 byte(s) in 1 object(s) allocated from:
    #0 0x49a26d in malloc (/home/dreijans/Documents/rank3/minishell/djoyke+0x49a26d)
    #1 0x4dd492 in ft_substr (/home/dreijans/Documents/rank3/minishell/djoyke+0x4dd492)
    #2 0x4d0cb0 in get_key_value /home/dreijans/Documents/rank3/minishell/src_djoy/executor/make_env.c:56:12
    #3 0x4d1007 in env_list /home/dreijans/Documents/rank3/minishell/src_djoy/executor/make_env.c:103:15
    #4 0x4d498f in main /home/dreijans/Documents/rank3/minishell/src_saar/main_saar.c:46:8
    #5 0x7f05ce167d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16
*/
void	reasing_value(char *temp, char *str, t_env *env)
{
	temp = env->value;
	env->value = str;
	// free(temp);
}

char	*ft_getenv(t_env *env, char *str)
{
	while (env)
	{
		if (mini_strcmp(str, env->key) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

/**
 * @param lst parser linked list
 * @brief returns list size
*/
int	list_iter(t_parser *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}

/**
 * @param node node in linked list
 * @param cmd either unset or export
 * @brief puts custom error message on STDOUT_FILENO
*/
void	put_execute_error(t_parser *node)
{
	ft_putstr_fd(node->cmd, STDERR_FILENO);
	ft_putstr_fd(": command not found\n", STDERR_FILENO);
}

/**
 * @param node node in linked list
 * @param cmd either unset or export
 * @brief puts custom error message on STDOUT_FILENO
*/
void	put_permission_error(t_parser *node)
{
	ft_putstr_fd(node->cmd, STDERR_FILENO);
	ft_putstr_fd(": permission denied\n", STDERR_FILENO);
}
