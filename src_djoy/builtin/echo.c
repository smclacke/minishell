/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 21:15:58 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/31 18:35:16 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

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
 * @brief writes node after command on standart output followed by /n char
 * -n that eliminates the endline char in output 
 * @return The echo utility exits 0 on success, and > 0 if an error occurs.
 * @todo mimic the same return values?
*/
void	ft_echo(t_parser *lst)
{
	t_parser	*temp;
	int			is_flag;

	temp = lst;
	is_flag = 0;
	if (!temp->cmd)
		mini_error("temp->cmd", errno);
	if (!temp->next)
	{
		write(1, "\n", 1);
		return ;
	}
	temp = temp->next;
	while (temp && is_all_n(temp))
	{
		temp = temp->next;
		is_flag++;
	}
	write_line(temp);
	if (is_flag == 0 || !temp->str)
		write(1, "\n", 1);
}
