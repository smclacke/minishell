/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_saar.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/24 19:23:45 by smclacke      #+#    #+#                 */
/*   Updated: 2023/06/27 11:51:52 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sarah.h"

// use struct as global?

// only use ./djoyke and ./sarah for the start, get used to branches, 
// then only focus on ./minishell, use these spaces for comments and tests

// write test script (!)

void	ft_prompt(void)
{
	printf(PROMPT);
}

int	main()
{
	char	*input;

	while(1)
	{
		ft_prompt();
		input = readline(NULL);
	}
	// printf("I'm Sarah's dummy main\n");
}
