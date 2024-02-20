/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 21:15:58 by dreijans      #+#    #+#                 */
/*   Updated: 2024/02/20 20:05:03 by smclacke      ########   odam.nl         */
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
static void	write_line(t_procs *temp, int i)
{
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

	if (mini_strcmp(lst->str[0], "~") == 0)
	{
		new_str = ft_getenv(*env, "HOME");
		lst->str[0] = new_str;
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
 * @return The echo utility exits 0 on success, and > 0 if an error occurs.
 * @todo error code
*/
void	ft_echo(t_parser *lst, t_env **env)
{
	t_parser	*temp;
	int			is_flag;
	int			i;

	temp = lst;
	is_flag = 0;
	i = 0;
	if (input_check(temp->proc) == false)
		return ;
	home_check(temp->proc, env);
	if (is_all_n(temp->proc->str[0]))
	{
		i++;
		is_flag++;
	}
	if (is_flag != 0 && temp->proc->str_count == 0)
	{
		lst->exit_code = E_USAGE;
		return ;
	}
	write_line(temp->proc, i);
	if (is_flag == 0)
		write(1, "\n", 1);
	lst->exit_code = E_USAGE;
}
