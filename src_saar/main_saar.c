/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_saar.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/24 19:23:45 by smclacke      #+#    #+#                 */
/*   Updated: 2023/06/30 12:43:25 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sarah.h"

void	ft_prompt(void)
{
	printf(PROMPT);
}

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	// (void) argv;
	(void) envp;
	
	char	*input;

	while(1)
	{
		ft_prompt();
		input = readline(NULL);
		check_empty(&argv[1][1]);
	}
}
