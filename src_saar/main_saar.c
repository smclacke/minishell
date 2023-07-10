/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_saar.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/24 19:23:45 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/10 17:42:15 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sarah.h"

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	// (void) argv;
	(void) envp;
	char	*input;
	t_lexer	*token = NULL;
	int	i = 0;

	while(1)
	{
		input = readline(PROMPT);
		argv = ft_split(input, ' ');
		while (argv[i])
		{
			token = lexer(argv[i]);
			ft_print_tokens(token);
			i++;
		}
	}
}
