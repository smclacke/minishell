/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/25 17:34:44 by smclacke      #+#    #+#                 */
/*   Updated: 2024/02/06 17:33:31 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */


#include "../include/shelly.h"

int	main(int argc, char **argv, char **envp)
{
	int			og_stdout;
	int			og_stdin;
	char		*input;
	t_parser	*procs;
	t_env		*env;

	(void) argc;
	(void) argv;
	procs = NULL;
	env = NULL;
	env = env_list(envp, env);
	og_stdout = dup(STDOUT_FILENO);
	og_stdin = dup(STDIN_FILENO);
	while (1)
	{
		handle_signals(PARENT);
		input = readline(PROMPT);

		procs = parse_input(procs, input);
		if (procs)
		{	
			execute(&env, procs);
			free_parser(procs);
		}
			continue ;

		// prpr(procs);



		dup2(og_stdout, STDOUT_FILENO);
		dup2(og_stdin, STDIN_FILENO);
		
		printf("success\n");
		exit(EXIT_SUCCESS);
	}
	return (0);
}
