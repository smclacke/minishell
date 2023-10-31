/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 21:15:58 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/31 18:13:34 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

static bool	is_all_n(t_parser *temp)
{
	int	j;

	j = 1;
	if (temp->str[0] != '-')
		return (false);
	while (temp && temp->str[0] == '-' && temp->str[j] != '\0')
	{
		if (temp->str[j] != 'n')
		{
			// printf("helloi?\n");
			return (false);
		}
		j++;
	}
	return (true);
}

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
 * @param node string to echo
 * @brief writes node after command on standart output followed by /n char
 * -n TBA that eliminates the endline char in output 
 * @return The echo utility exits 0 on success, and > 0 if an error occurs.
 * @todo 
 * bash-3.2$ echo -nnnnnnn hi WORKS
 * hibash-3.2$ echo -----n hi WORKS
 * -----n hi WORKS
 * dreijans@f0r1s3:~$ echo -n-n hi WORKS
 * -n-n hi WORKS
 * bash-3.2$ echo hi -n
 * hi -n
 * bash-3.2$ echo "hi" -n
 * hi -n
 * dreijans@f0r1s3:~$ echo -nnnnnnnann hi WORKS
 * -nnnnnnnann hi WORKS
 * dreijans@f0r1s3:~$ echo -h hi WORKS
 * -h hi WORKS
 * ????????????make a part that when it encouters $random_name to go in 
 * env and take whats after the random_name = sign???????????
 * 		// 1) check if the next is str
		// 2)check if the [0] = '-'
			// 2.1) if the rest of that str = n print the string without -n in it without \n
			// 2.2) else print all the strings entirely with \n
		// 3) print all the strings with \n
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
	if (!temp->str)
	{
		write(1, "\n", 1);
		return ;
	}
	while (temp && is_all_n(temp))
	{
		temp = temp->next;
		is_flag++;
	}
	write_line(temp);
	if (temp)
	if (is_flag == 0)
		write(1, "\n", 1);
}
