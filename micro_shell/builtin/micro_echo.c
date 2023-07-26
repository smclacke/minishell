/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   micro_echo.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 10:11:39 by dreijans      #+#    #+#                 */
/*   Updated: 2023/07/26 17:19:27 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @param node string to echo
 * @brief writes node after command on standart output followed by /n char
 * -n TBA that eliminates the endline char in output 
 * @return The echo utility exits 0 on success, and > 0 if an error occurs.
*/
void	*micro_echo(t_parser **node)//for now index 1
{
	int	i;
	int	is_flag;

	i = 1;
	is_flag = 0;
	while (node->str != NULL)
	{
		if (ft_strcmp(node->str, "-n") == 0)
		{
			node = node->next;
			++is_flag;
		}
		else
		{
			printf("%s", node->str);
			node = node->next;
		}
	}
	if (is_flag != 0)
		printf("\n");
	exit(EXIT_SUCCESS);
}
