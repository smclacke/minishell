/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   idfk.c                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: smclacke <smclacke@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2024/01/23 13:25:46 by smclacke      #+#    #+#                 */
/*   Updated: 2024/01/24 19:25:35 by smclacke      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

/////

/**
 * while tokens + !pipe
 * get process tokens !start----------end!
 * make array[i] filled with those tokens
 * tokens[i]++ if pipe, move over
 * array[i] ++ move to next process
 * do again
 * 
 * proc_arr[i]
	* get proc tokens...
	* add to proc_arr[i][j++]
 * proc_arr[i++]
	* skip pipe
	* get proc tokens...
	* add to proc_arr[i][j++]
 * ........................
*/

/**
 * @todo	maybe norm?
 * @todo	error handling
 * @todo	memory handling - add malloc protection back when it works
 * @todo	remove print statements when everything works
*/
	// if (!proc->proc_arrs)
	// {
	// 	printf("maloc fucked proc_arrs\n");
	// 	return (1);
	// }
				// if (!proc->proc_arrs[proc_i])
				// {
				// 	printf("maloc fucked proc_arrs\n");
				// 	return (1);
				// }
					// if (!proc->proc_arrs[proc_i][proc_j])
					// {
					// 	printf("maloc fucked proc_arrs\n");
					// 	return (1);
					// }


// static void	get_procs(t_parser *proc)
// {
// 	int		i;
// 	int		proc_i;
// 	int		proc_j;

// 	i = 0;
// 	proc_i = 0;
// 	proc->proc_arrs = (char ***)malloc(sizeof(char **) * (proc->proc_count + 1));
// 	printf("proc->proc_count = %i\n", proc->proc_count);
// 	while (proc->tokens[i])
// 	{
// 		while (proc->tokens[i] && !is_pipe(proc->tokens[i]))
// 		{
// 			if (proc->tokens[i + 1] == NULL || is_pipe(proc->tokens[i + 1]))
// 			{
// 				proc->proc_size = (i - proc->start) + 1;
// 				// make array ..
// 				make_proc_array(proc);
// 				printf("proc->proc_size = %i\n", proc->proc_size);
// 				proc->proc_arrs[proc_i] = (char **)malloc(sizeof(char *) * (proc->proc_size + 1));
// 				while (proc_i <proc->proc_size)
// 				proc_j = 0;
// 				printf("proc->start = %i\n", proc->start);
// 				printf("pos i = %i\n", i);
// 				while (proc->start <= i)
// 				{
// 					proc->token_size = ft_strlen(proc->tokens[proc->start]);
// 					printf("proc->token_size = %i\n", proc->token_size);
// 					proc->proc_arrs[proc_i][proc_j] = (char *)malloc(sizeof(char) * (proc->token_size + 1));
// 					while (proc_j <= proc->token_size)
// 					{
// 						printf("where break?\n");
// 						ft_strcpy(proc->proc_arrs[proc_i][proc_j], proc->tokens[proc->start]);
// 						printf("proc->arr[%i][%i] = %s\n", proc_i, proc_j, proc->proc_arrs[proc_i][proc_j]);
// 						proc_j++;
// 					}
// 					proc->start++;
// 				}
// 			}
// 			i++;
// 		}
// 		proc_i++;
// 		if (is_pipe(proc->tokens[i]))
// 		{
// 			printf("proc->start = %i\n", proc->start);
// 			proc->start = i;
// 			i++;
// 			printf("im here\n");
// 			exit (EXIT_SUCCESS);
// 			// proc->proc_arrs[proc_i][proc_j] = NULL;
// 			// // proc_j = 0;
// 			// printf("start = %i\n", proc->start);
// 		}
// 	}
// }


// static	t_parser	*make_parser_list(t_parser *procs, t_parser *proc_list, int proc_count)
// {
// 	t_parser	*new_list;
// 	t_parser	*node;
// 	int			i;
// 	(void) proc_count;

// 	new_list = NULL;
// 	i = 0;
// 	// if (proc_count == 1)
// 	// 	new_list = one_proc(procs);
// 	// else
// 	// {
// 		while (i < procs->proc_count)
// 		{
// 			node = parser_listnew(procs->proc_arrs[i]);
// 			parser_listadd_back(&new_list, node);
// 			i++;
// 		}
// 	// }
// 	proc_list = new_list;
// 	return (proc_list);
// }

// static	t_parser	*one_proc(t_procs *proc)
// {
// 	t_parser	*new_list;
// 	t_parser	*node;
// 	int			i;

// 	new_list = NULL;
// 	i = 0;
// 	node = parser_listnew(proc);
// 	parser_listadd_back(&new_list, node);
// 	return (new_list);
// }



// static void	sort_proc(t_procs *proc)
// {
// 	int		cmd_flag;

// 	cmd_flag = 0;
// 	while (proc->input)
// 	{
// 		printf("here\n");
// 		exit(EXIT_FAILURE);
// 		if (proc_redir(proc->input))
// 		{
// 			proc->input = proc->meta;
// 			proc->input = proc->next;
// 			proc->input = proc->file;
// 		}
// 		else if (cmd_flag == 0)
// 		{
// 			cmd_flag = 1;
// 			proc->input = proc->cmd;
// 		}
// 		// else if (cmd_flag != 0)
// 		// 	proc->input = proc->str;
// 		proc->input = proc->next;
// 	}
// }






// FREEING FUNCS I DON'T KNOW IF I NEED THESE OR NOT

// void	free_parser(t_parser *tokens)
// {
// 	t_parser	*tmp;

// 	while (tokens)
// 	{
// 		tmp = tokens->next;
// 		free (tokens);
// 		tokens = tmp;
// 	}
// }

// void	free_tokens(t_tokens *tokens)
// {
// 	t_tokens	*tmp;

// 	while (tokens)
// 	{
// 		tmp = tokens->next;
// 		free (tokens);
// 		tokens = tmp;
// 	}
// }

	









	// int			proc_i;
	// int			proc_count;
	// int			i;

	// if (!tokens)
	// 	return (NULL);
	// proc_count = count_procs(tokens);
	// procs = (t_tokens **)malloc(sizeof(t_tokens *) * (proc_count + 1));
	// if (!procs)
	// {
	// 	printf("malloc error parser\n");
	// 	return (NULL);
	// }

	// proc_i = 0;
	// // make mini proc arrays, then sort per var, then add into token list (one proc)
	// // which will become node in parser list.. 
	// while (proc_i <= proc_count)
	// {
	// 	proc_arr[proc_i] = get_procs(tokens);
	// 	proc_i++;
	// }
	// i = 0;
	// while (tokens[i])
	// {
	// 	procs = make_token_lists(tokens[i], procs);
	// 	i++;
	// }
	// // procs = make_token_lists(tokens, procs);

	// // printing
	// i = 0;
	// while (procs[i])
	// {
	// 	shelly_tokenlst_print(procs[i]);
	// 	i++;
	// }
	// // printing

	// // short contents of proc lists per var
	


	// i = 0;
	// while (procs[i])
	// {
	// 	free_tokens(procs[i]);
	// 	i++;
	// }

		// sort contents, make 2d array, then add things to nodes,
			// straight away put into var nodes, skip input

/**
 * 		**strs - 2d array is one node in list, so as I make the list, check the content
 * 
 * 
 * 		process list = cmd **strs redir file
 * 
 * 
 * 		redir meta - just give as enum, then file, keep in order
 * 			
 * 
 * 			redir = enum	file  | 	redir = enum	file
 * 
 * 
*/
// static	t_tokens	**make_token_lists(char **tokens, t_tokens **procs)
// {
// 	t_tokens	*node;
// 	t_tokens	*token_list;
// 	int			token_count;
// 	int			i;
// 	int			proc_i;

// 	i = 0;
// 	proc_i = 0;
// 	token_list = NULL;
// 	token_count = 0;  

// 	// only one part of array being sent here, which is one process
// 	// find cmd, **str, redirs, and files, then add to list and send list back
// 	while (tokens && tokens[i])
// 	{
// 		while (tokens[i] && !is_pipe(tokens[i]))
// 		{
// 			node = token_listnew(tokens[i]);
// 			token_listadd_back(&token_list, node);
// 			i++;
// 			token_count++;
// 		}
// 		procs[proc_i] = (t_tokens *)malloc(sizeof(t_tokens) * (token_count + 1));
// 		if (!procs[proc_i])
// 		{
// 			printf("procs [i] malloc failed\n");
// 			return (NULL);
// 		}
// 		procs[proc_i] = token_list;
// 		proc_i++;
// 		token_list = NULL;
// 		token_count = 0;
// 		if (tokens[i])
// 			i++;
// 	}
// 	procs[proc_i] = 0;
// 	return (procs);
// }
