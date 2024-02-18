/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/25 17:34:44 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/18 16:39:54 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shelly.h"

int	run_minishell(t_env *env, char *input)
{
	t_parser	*procs;

	procs = NULL;
	procs = parse_input(procs, input);
	if (!procs)
		return (0);
	prpr(procs);
	execute(&env, procs);
	// clean_funct(&data);
	free_parser(procs);
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	int			og_stdout;
	int			og_stdin;
	char		*input;
	t_env		*env;

	(void) argc;
	(void) argv;
	env = NULL;
	og_stdout = dup(STDOUT_FILENO);
	og_stdin = dup(STDIN_FILENO);
	env = env_list(envp, env);
	while (1)
	{
		handle_signals(PARENT);
		input = readline(PROMPT);
		if (input == NULL)
			exit(EXIT_SUCCESS);
		if (!run_minishell(env, input))
			continue ;
		dup2(og_stdout, STDOUT_FILENO);
		dup2(og_stdin, STDIN_FILENO);
	}
	return (0);
}
