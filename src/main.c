/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/25 17:34:44 by smclacke      #+#    #+#                 */
/*   Updated: 2023/11/07 15:59:43 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shelly.h"

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_parser	*tokens;
	t_env		*env;


	(void) argc;
	(void) argv;
	env = NULL;
	env = env_list(envp, env);
	tokens = NULL;

	int	og_stdout = dup(STDOUT_FILENO);
	int	og_stdin = dup(STDIN_FILENO);
	while (1)
	{
		handle_signals(PARENT);
		input = readline(PROMPT);
		if (!input)
			exit(EXIT_FAILURE);
		add_history(input);

		tokens = lexer(input);
		free(input);
		if (!tokens)
			continue ;

		tokens = parser(tokens);
		if (!tokens)
			continue ;

		execute(&env, tokens);
		free_tokens(tokens);

		dup2(og_stdout, STDOUT_FILENO);
		dup2(og_stdin, STDIN_FILENO);

	}
	return (0);
}
