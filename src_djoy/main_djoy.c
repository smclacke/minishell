/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_djoy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/24 19:24:05 by smclacke      #+#    #+#                 */
/*   Updated: 2023/07/01 17:54:01 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/djoyke.h"

int	main(int argc, char **argv, char **envp)
{
	t_env	*env;

	env = NULL;
	if (argc <= 1)//needs to give prompt back
		exit(EXIT_FAILURE);//only for testing purpose
	list_env(envp, &env);
	// print_list(env);
	check_for_builtin(argv, argc);
}
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
