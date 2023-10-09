/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_echo.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 10:11:39 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/05 18:09:27 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

/**
 * @param node string to echo
 * @brief writes node after command on standart output followed by /n char
 * -n TBA that eliminates the endline char in output 
 * @return The echo utility exits 0 on success, and > 0 if an error occurs.
 * @todo 
 * bash-3.2$ echo -nnnnnnn hi
 * hibash-3.2$ echo -----n hi
 * -----n hi
 * bash-3.2$ echo hi -n
 * hi -n
 * bash-3.2$ echo "hi" -n
 * hi -n
 * fix it!!!!!!!!!
 * make a part that when it encouters $random_name to go in 
 * env and take whats after the random_name = sign
*/
void	ft_echo(t_parser *lst)
{
	int	i;
	int	is_flag;


	i = 0;
	is_flag = 0;
	if (!lst->cmd)
		mini_error("lst->cmd", errno);
	if (!lst->next)
	{
		printf("\n");
		return ;
	}
	lst = lst->next;
	if (!lst->str)
	{
		// 1) check if the next one is a meta, 
		//    | >> etc to see if you need to echo into something
		// 2) or to just put the newline on the terminal
		printf("\n");
	}
	while (lst)
	{
		if (lst->str)
		{
			if (ft_strcmp(lst->str, "-n") == 0)
			{
				is_flag++;
				i++;
			}
			else
			{
				printf("%s ", lst->str);
				i++;
			}
		}
		lst = lst->next;
	}
	if (is_flag == 0)
		printf("\n");
}
