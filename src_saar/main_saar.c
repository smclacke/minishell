/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_saar.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/24 19:23:45 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/11 19:51:08 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/sarah.h"

int	main(int argc, char **argv, char **envp)
{
	(void) argc;
	(void) envp;
	char	*input;
	t_list	*token;
	int		i;

	while(1)
	{
		i = 0;
		input = readline(PROMPT);
		add_history(input);
		argv = ft_split(input, ' ');
		if (!argv)
			return (EXIT_FAILURE);
		while (argv[i])
		{
			token = lexer(argv[i]);
			ft_print_tokens(token);
			i++;
		}
	}
}
