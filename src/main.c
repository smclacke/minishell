/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: dreijans <dreijans@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/10/25 17:34:44 by smclacke      #+#    #+#                 */
/*   Updated: 2023/12/11 18:33:59 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/shelly.h"

// void	print_new_parser(t_process *proc)
// {
// 	int		i = 0;
// 	int		j = 0;

// 	while (i < proc->parser->proc_id)
// 	{
// 		printf("[%i]\t", proc->parser->proc_id);
// 		while ()
// 		printf("input = %s\n", proc->parser->input);
// 		// printf("cmd = [%s]\t", procs->cmd);
// 		// printf("str = [%s]\t\n", procs->str);
// 		i++;
// 	}
// }

void	lexing(t_process *data, char *input)
{
	if (!input)
		exit(0);
	if (!is_space(input))
		add_history(input);
	data->parser = lexer(input);
	free(input);
	// return (tokens);
}

void	print_parser(t_process *data)
{
	
}

int	main(int argc, char **argv, char **envp)
{
	t_process	data;
	char		*input;
	// t_lexer		*tokens;
	// t_parser	*procs;
	// t_env		*env;
	int			og_stdout;
	int			og_stdin;

	(void) argc;
	(void) argv;
	(void) envp;
	// env = NULL;
	// env = env_list(envp, env);
	og_stdout = dup(STDOUT_FILENO);
	og_stdin = dup(STDIN_FILENO);
	while (1)
	{
		handle_signals(PARENT);
		input = readline(PROMPT);
		lexing(&data, input); // add wrapper protection
		shelly_print_list(data.parser);
		parser(&data); // add wrapper
		print_parser(&data);
		// if (!procs)
		// 	continue ;
		// print_new_parser(&data);
		exit(EXIT_SUCCESS);
		// print_the_full_thing(tokens);
		// execute(&env, tokens);
		// free_tokens(tokens);
		dup2(og_stdout, STDOUT_FILENO);
		dup2(og_stdin, STDIN_FILENO);
	}
	return (0);
}
