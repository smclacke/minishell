/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/25 17:34:44 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/10 18:22:10 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shelly.h"

t_parser	*lexing(char *input)
{
	t_parser	*tokens;

	if (!input)
		exit(0);
	if (!is_space(input))
		add_history(input);
	tokens = lexer(input);
	free(input);
	return (tokens);
}

int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_parser	*tokens;
	t_env		*env;
	int			og_stdout;
	int			og_stdin;

	(void) argc;
	(void) argv;
	env = NULL;
	env = env_list(envp, env);
	og_stdout = dup(STDOUT_FILENO);
	og_stdin = dup(STDIN_FILENO);
	while (1)
	{
		handle_signals(PARENT);
		input = readline(PROMPT);
		tokens = lexing(input);
		if (!tokens)
			continue ;
		tokens = parser(tokens);
		if (!tokens)
			continue ;
		// print_the_full_thing(tokens);
		execute(&env, tokens);
		free_tokens(tokens);
		dup2(og_stdout, STDOUT_FILENO);
		dup2(og_stdin, STDIN_FILENO);
	}
	return (0);
}
