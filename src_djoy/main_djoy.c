/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   main_djoy.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/24 19:24:05 by smclacke      #+#    #+#                 */
/*   Updated: 2023/08/03 17:22:34 by dreijans      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "../include/djoyke.h"

/* checking the edge cases for this one */
int	main(int argc, char **argv, char **envp)
{
	char		*input;
	t_lexer		*tokens;
	t_parser	*parser_struct;

	(void) argc;
	(void) argv;

	tokens = NULL;
	parser_struct = NULL;
	while (1)
	{
		input = readline(PROMPT);
		add_history(input);
		tokens = lexer(input);
		if (!tokens)
			continue ;
		print_lexer(tokens);
		parser_struct = parser(tokens);
		if (!parser_struct)
			continue ;
		// expand(mini->tokens) // tokens from s_parser struct, 
		//	check built-in, check meta char, check quotes.
		if (check_for_builtin(parser_struct))//will be a expand funct
			printf("there's a builtin whoop\n");
		// execution // make env_list, create child processes, execve
		ft_execute(envp, parser_struct);
		// free input (readline needs to be fred at end)	
	}
	return (0);
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

//ctrl d exits where it's in


//als 1 input heeft echo hi geen childprocess anders wel ofcourse haha


// exit in de pipeline 

// bash-3.2$ cd desktop | echo hi
// hi
// bash-3.2$ pwd
// /Users/dreijans
// bash-3.2$

// cd word uitgevoerd maar 2nd child doet er niks mee dus alleen hi als output


// maybe functie voor single command of pipeline. 