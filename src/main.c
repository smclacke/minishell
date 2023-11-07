/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/25 17:34:44 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/07 18:55:21 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shelly.h"

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_parser	*lexer_tokens;
	t_parser	*parser_tokens;
	t_env		*env;


	(void) argc;
	(void) argv;
	env = NULL;
	env = env_list(envp, env);
	lexer_tokens = NULL;
	parser_tokens = NULL;

	int	og_stdout = dup(STDOUT_FILENO);
	int	og_stdin = dup(STDIN_FILENO);
	while (1)
	{
		handle_signals(PARENT);
		input = readline(PROMPT);
		if (!input)
			exit(EXIT_FAILURE);
		add_history(input);

		lexer_tokens = lexer(input);
		free(input);
		if (!lexer_tokens)
			continue ;

		parser_tokens = parser(lexer_tokens);
		if (!parser_tokens)
			continue ;

		execute(&env, parser_tokens);
		free_tokens(parser_tokens);

		dup2(og_stdout, STDOUT_FILENO);
		dup2(og_stdin, STDIN_FILENO);

	}
	return (0);
}
