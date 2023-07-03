/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_saar.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/24 19:23:45 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/03 15:10:01 by smclacke      ########   odam.nl         */
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
	// char	*input;
	t_lexer	*token;

	// while(1)
	// {
	// 	ft_prompt();
	// 	input = readline(NULL);
	token = lexer(*argv);
	ft_print_tokens(token);
	// }
}
