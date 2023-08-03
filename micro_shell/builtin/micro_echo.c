/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   micro_echo.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 10:11:39 by dreijans      #+#    #+#                 */
/*   Updated: 2023/08/03 15:49:05 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param node string to echo
 * @brief writes node after command on standart output followed by /n char
 * -n TBA that eliminates the endline char in output 
 * @return The echo utility exits 0 on success, and > 0 if an error occurs.
*/
void	micro_echo(t_parser *lst)
{
	// int	i;
	// int	is_flag;
	// t_expand 	*temp_lst;

	// i = 0;
	// is_flag = 0;
	// temp_lst = lst;
	// if (!temp_node->str)
	// 	micro_error("node->str", errno);
	// while (node->str[i] != '\0')
	// while (temp_node)
	// {
		// if (ft_strcmp(&node->str[i], "-n") == 0)
		// {
		// 	++is_flag;
		// 	i++;
		// }
		// else
		// {
		printf("echo prints\n");
		printf("%s", lst->str);
		// 	i++;
		// }
	// }
	// temp_node = temp_node->next;
	// if (is_flag != 0)
		printf("\n");
}
