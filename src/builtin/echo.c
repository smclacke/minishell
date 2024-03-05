/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 21:15:58 by dreijans      #+#    #+#                 */
/*   Updated: 2024/03/05 14:23:03 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param temp t_parser linked list
 * @brief checks for '-' and 'n' in sequence in string
 * @return returns true if sequence is -n(or multiple n)
 * returns false if [0] is not '-' and sequence is not 'n'
*/
static bool	is_all_n(char *str)
{
	int	j;

	j = 1;
	if (str[0] != '-')
		return (false);
	if (str && str[1] != 'n')
		return (false);
	while (str[j] != '\0')
	{
		if (str[j] != 'n')
			return (false);
		j++;
	}
	return (true);
}

/**
 * @param temp t_parser linked list
 * @brief writes string and space to the terminal
*/
static void	write_line(t_procs *temp, int i, int is_flag)
{
	int	count;

	count = temp->str_count;
	if (is_flag != 0)
	{
		while (is_flag < temp->str_count)
		{
			write(1, temp->str[is_flag], ft_strlen(temp->str[is_flag]));
			if (is_flag < (temp->str_count -1))
				write(1, " ", 1);
			is_flag++;
		}
		return ;
	}
	while (i < temp->str_count)
	{
		if (temp->str[i])
			write(1, temp->str[i], ft_strlen(temp->str[i]));
		if (i < (temp->str_count - 1))
			write(1, " ", 1);
		i++;
	}
}

/**
 * @param lst t_parser linked list
 * @param env environment linked list
 * @brief checks if str is "~" replaces it by HOME str
*/
static void	home_check(t_procs *lst, t_env **env)
{
	char		*new_str;

	if (lst->tilde == TRUE)
		return ;
	if (mini_strcmp(lst->str[0], "~") == 0)
	{
		new_str = ft_getenv(*env, "HOME");
		free(lst->str[0]);
		lst->str[0] = ft_strdup(new_str);
		if (!lst->str[0])
			malloc_error(NULL, lst, NULL, E_MALLOC);
	}
}

/**
 * @param lst t_parser linked list
 * @brief checks if cmd exist, and if there is a str input after it
*/
static bool	input_check(t_procs *lst)
{
	if (lst->str_count == 0)
	{
		write(1, "\n", 1);
		return (false);
	}
	return (true);
}

/**
 * @param lst t_parser linked list
 * @brief writes node after command on standart output followed by /n char
 * -n that eliminates the endline char in output
*/
void	ft_echo(t_parser *lst, t_env **env)
{
	int			is_flag;
	int			i;

	is_flag = 0;
	i = 0;
	if (input_check(lst->proc) == false)
		return ;
	home_check(lst->proc, env);
	if (is_all_n(lst->proc->str[0]))
	{
		is_flag++;
		i++;
		while (i < lst->proc->str_count)
		{
			if (!is_all_n(lst->proc->str[i]))
				break ;
			i++;
			is_flag++;
		}
	}
	if (is_flag != 0 && lst->proc->str_count == 1)
		return ;
	write_line(lst->proc, i, is_flag);
	if (is_flag == 0)
		write(1, "\n", 1);
}
