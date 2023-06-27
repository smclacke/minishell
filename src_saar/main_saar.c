/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_saar.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/24 19:23:45 by smclacke      #+#    #+#                 */
/*   Updated: 2023/06/27 13:22:35 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sarah.h"

// use struct as global?

// write test script

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
}
