/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_echo.c                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/07/03 10:11:39 by dreijans      #+#    #+#                 */
/*   Updated: 2023/09/04 21:37:40 by smclacke      ########   odam.nl         */
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
 * 		env and take whats after the random_name = sign
*/
void	ft_echo(t_parser *lst)
{
	int	i;
	int	is_flag;

	i = 0;
	is_flag = 0;
	if (!lst->cmd_list)
		mini_error("cmd_list", errno);
	lst = lst->next;
	printf("what are you ? = [%s]\n", lst->cmd_list->strs);
	while (lst)
	{
		if (ft_strcmp(&lst->cmd_list->strs[i], "-n") == 0)
		{
			++is_flag;
			i++;
		}
		else
		{
			printf("%s ", lst->cmd_list->strs);
			i++;
		}
		lst = lst->next;
	}
	if (is_flag != 0)
		printf("\n");
}
