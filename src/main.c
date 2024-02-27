/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/25 17:34:44 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/27 16:41:39 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shelly.h"

/**
 * @param env environment linked list
 * @param input string containing prompt input
 * @param exit_c int containing exit code
 * @brief function that runs minishell
 */
static int	run_minishell(t_env *env, char *input, int exit_c)
{
	t_parser	*procs;

	procs = NULL;
	procs = parse_input(procs, input);
	if (!procs)
		return (E_SYNTAX);
	else
		procs->exit_code = exit_c;
	execute(&env, procs);
	exit_c = procs->exit_code;
	free_parser(procs);
	return (exit_c);
}

/**
 * @param input prompt string
 * @brief checks if readline doesn't return NULL
 * if returns NULL exits accordingly
*/
static char	*readline_check(char *input, t_env *env)
{
	if (input == NULL)
	{
		free(env);
		write(STDOUT_FILENO, "exit\n", 6);
		free(input);
		exit(EXIT_SUCCESS);
	}
	return (input);
}

int	main(int argc, char **argv, char **envp)
{
	int			og_stdout;
	int			og_stdin;
	t_env		*env;
	char		*input;
	int			exit_c;

	(void) argc;
	(void) argv;
	env = NULL;
	og_stdout = dup(STDOUT_FILENO);
	og_stdin = dup(STDIN_FILENO);
	env = env_list(envp, env);
	exit_c = 0;
	while (1)
	{
		handle_signals(PARENT);
		input = readline(PROMPT);
		readline_check(input, env);
		exit_c = run_minishell(env, input, exit_c);
		dup2(og_stdout, STDOUT_FILENO);
		dup2(og_stdin, STDIN_FILENO);
	}
	return (exit_c);
}
