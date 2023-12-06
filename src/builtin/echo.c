/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 21:15:58 by dreijans      #+#    #+#                 */
/*   Updated: 2023/12/06 19:45:16 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

/**
 * @param temp t_parser linked list
 * @brief checks for '-' and 'n' in sequence in string
 * @return returns true if sequence is -n(or multiple n)
 * returns false if [0] is not '-' and sequence is not 'n'
*/
static bool	is_all_n(t_parser *temp)
{
	int	j;

	j = 1;
	if (temp->str[0] != '-')
		return (false);
	while (temp && temp->str[0] == '-' && temp->str[j] != '\0')
	{
		if (temp->str[j] != 'n')
			return (false);
		j++;
	}
	return (true);
}

/**
 * @param temp t_parser linked list
 * @brief writes string and space to the terminal
*/
static void	write_line(t_parser *temp)
{
	while (temp && temp->str)
	{
		if (temp->str)
			write(1, temp->str, ft_strlen(temp->str));
		if (temp->next)
			write(1, " ", 1);
		temp = temp->next;
	}
}

/**
 * @param lst t_parser linked list
 * @param env environment linked list
 * @brief checks if str is "~" replaces it by HOME str
*/
static void	home_check(t_parser *lst, t_env **env)
{
	char		*new_str;

	if (mini_strcmp(lst->next->str, "~") == 0)
	{
		new_str = ft_getenv(*env, "HOME");
		lst->next->str = new_str;
	}
}

/**
 * @param lst t_parser linked list
 * @brief checks if cmd exist, and if there is a str input after it
 * @todo check error
*/
static bool	input_check(t_parser *lst)
{
	t_parser	*temp;

	temp = lst;
	if (!temp->cmd)
	{
		// mini_error("temp->cmd", E_USAGE, lst);
		mini_error(E_USAGE, lst);
		return (false);
	}
	if (!temp->next || temp->next->meta)
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
 * @todo error code, check if input function actually works
*/
void	ft_echo(t_parser *lst, t_env **env)
{
	t_parser	*temp;
	int			is_flag;

	temp = lst;
	is_flag = 0;
	if (!input_check(lst))
		return ;
	home_check(temp, env);
	temp = temp->next;
	while (temp && is_all_n(temp))
	{
		temp = temp->next;
		is_flag++;
	}
	write_line(temp);
	if (is_flag != 0)
	{
		lst->exit_code = E_USAGE;
		return ;
	}
	if (is_flag == 0 || !temp->str)
		write(1, "\n", 1);
	lst->exit_code = E_USAGE;
}
