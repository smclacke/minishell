/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_echo.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 10:11:39 by dreijans      #+#    #+#                 */
/*   Updated: 2023/08/17 17:23:28 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/djoyke.h"

/**
 * @param node string to echo
 * @brief writes node after command on standart output followed by /n char
 * -n TBA that eliminates the endline char in output 
 * @return The echo utility exits 0 on success, and > 0 if an error occurs.
*/
void	ft_echo(t_parser *lst)
{
	int	i;
	int	is_flag;

	i = 0;
	is_flag = 0;
	if (!lst->cmd)
		mini_error("node->str", errno);
	else
		lst = lst->next;
	while (lst)
	{
		if (ft_strcmp(&lst->str[i], "-n") == 0)
		{
			++is_flag;
			i++;
		}
		else
		{
			printf("%s\n", lst->str);
			i++;
		}
		lst = lst->next;
	}
	if (is_flag != 0)
		printf("\n");
}
