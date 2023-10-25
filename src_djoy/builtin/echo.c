/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   echo.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/19 21:15:58 by dreijans      #+#    #+#                 */
/*   Updated: 2023/10/25 20:37:28 by smclacke      ########   odam.nl         */
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
	t_parser	*tmp;

	i = 0;
	is_flag = 0;
	tmp = lst;
	print_the_full_thing(lst);
	// if (!lst->cmd)
	// 	mini_error("lst->cmd", errno);
	// if (!lst->next)
	// {
	// 	printf("we zijn er bijna...\n");
	// 	printf("\n"); // use write
	// 	return ;
	// }
	// lst = lst->next;
	// printf("lst->cmd = %s\n", lst->cmd);
	// printf("lst->str = %s\n", lst->str);
	// if (!lst->str)
	// {
	// 	// 1) check if the next one is a meta, 
	// 	//    | >> etc to see if you need to echo into something
	// 	// 2) or to just put the newline on the terminal
	// 	printf("\n");// use write
	// }
	while (tmp)
	{
		if (tmp->str)
		{
			if (ft_strcmp(tmp->str, "-n") == 0)
			{
				is_flag++;
				i++;
			}
			else
			{
				printf("%s ", tmp->str); // use write
				i++;
			}
		}
		tmp = tmp->next;
	}
	if (is_flag == 0)
		printf("\n");// use write
}
