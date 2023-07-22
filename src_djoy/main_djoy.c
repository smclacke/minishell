/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_djoy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/24 19:24:05 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/22 17:00:09 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/djoyke.h"

/* checking the edge cases for this one */

int	main(int argc, char **argv, char **envp)
{
	t_env		*env;
	t_command	*fake_command;
	char		*input;

	(void) argv;
	(void) argc;
	while (1)
	{
		input = readline(PROMPT);
		add_history(input);
		env = env_list(envp);
		fake_command = init_command();
		print_command(fake_command);
		ft_execute(fake_command);
		// print_list_command(fake_command);
		// check_for_builtin(test, env);
		// print_list(env);
	}
}

/*

• Your shell must implement the following builtins:
◦ echo with option -n
◦ cd with only a relative or absolute path
◦ pwd with no options
◦ export with no options
◦ unset with no options
◦ env with no options or arguments
◦ exit with no options (closes terminal?, closes bash)

*/

/*
	expanding:
	executing:
	built-in: 	compare the string to built-in name
				make function that does the same as built-in
-----------------------------------------------------------------------------

	will get the structs and based on how many I need to fork.
	needs to inherit all the basics.
	open all pipes and fd's in here

	Start by creating a new process for each command in the pipeline 
	and making the parent wait for the last command. 
	This will allow running simple commands such as “ls ­al”.

	{
		taking whatever from a struct();
		{
			error check;
		}
		function that scales the pipes based on the amount of commands()
		{
			{
				//make macro's for the read and write end in header file;
				opening the pipes();
			}
		error check
		function that forks x commands();
		waitstatus();
	}
	
*/

//pointer refreshing knowledge
//make exit staus at every built in
//make own error messages

//& gives * and &bla[1] gives **..... wellll

//ctrl d exits everything (shell), when the INPUT = NULL you exit
//just an if statement no signals please not neccerairy
