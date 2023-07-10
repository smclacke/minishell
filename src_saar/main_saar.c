/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_saar.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/24 19:23:45 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/10 14:57:31 by smclacke      ########   odam.nl         */
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
	int	i = 1;

	// while(1)
	// {
	// 	ft_prompt();
	// 	input = readline(NULL);
	while (argv[i])
	{
		token = (t_lexer *)lexer(argv[i]);
		ft_print_tokens(token);
		i++;
	}
	// }
}
