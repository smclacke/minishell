/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/25 17:34:44 by smclacke      #+#    #+#                 */
<<<<<<< HEAD
/*   Updated: 2024/02/19 21:17:10 by dreijans      ########   odam.nl         */
=======
/*   Updated: 2024/02/19 21:56:23 by smclacke      ########   odam.nl         */
>>>>>>> sarah
/*                                                                            */
/* ************************************************************************** */

#include "../include/shelly.h"

int	run_minishell(t_env *env, char *input, int exit_c)
{
	t_parser	*procs;

	procs = NULL;
	procs = parse_input(procs, input);
	if (!procs)
<<<<<<< HEAD
		return (0);
	// prpr(procs);
=======
		return (42);
	// prpr(procs); //
	procs->exit_code = exit_c;
>>>>>>> sarah
	execute(&env, procs);
	exit_c = procs->exit_code;
	free_parser(procs);
	return (exit_c);
}

int	main(int argc, char **argv, char **envp)
{
	int			og_stdout;
	int			og_stdin;
	char		*input;
	t_env		*env;
	int			exit_c;

	(void) argc;
	(void) argv;
	env = NULL;
	exit_c = 0;
	og_stdout = dup(STDOUT_FILENO);
	og_stdin = dup(STDIN_FILENO);
	env = env_list(envp, env);
	while (1)
	{
		handle_signals(PARENT);
		input = readline(PROMPT);
		if (input == NULL)
			exit(EXIT_SUCCESS);
		exit_c = run_minishell(env, input, exit_c);
		dup2(og_stdout, STDOUT_FILENO);
		dup2(og_stdin, STDIN_FILENO);
	}
	return (0);
}
