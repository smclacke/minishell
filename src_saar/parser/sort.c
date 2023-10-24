/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sort.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/24 20:02:42 by smclacke      #+#    #+#                 */
/*   Updated: 2023/10/24 20:25:03 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/shelly.h"

// sort

/***
 * cmd = first, i = 0 or i + 1 after pipe
 * 
 * 
 * 
 * 
 * while lst
 * 
 * if cmd + i != 0, pipe? is cmd pipe i + 1?
 * 
 *  
*/

/**
 * void	ft_swap(t_stack **stack)
{
	t_stack	*swap;

	if (!*stack || !(*stack)->next)
		return ;
	swap = (*stack)->next;
	(*stack)->next = swap->next;
	swap->next = *stack;
	*stack = swap;
}
*/


// t_parser	*sort_list(t_parser *tokens)
// {
// 	int	i = 0;
// 	int	j = 0;
// 	t_parser	*head;
// 	t_parser	*tmp;

// 	head = tokens;
// 	tmp = tokens;
// 	while (tmp)
// 	{
// 		while (tmp->cmd == NULL)
// 			i++;
// 		tmp->cmd = head;
// 		head = head->next;
// 		tmp = tmp->next;
	
		
		
// 		// i += 1;
// 		// j = i;
// 		// while (tmp)
		

// 	}
// 	return (tokens);
// }
