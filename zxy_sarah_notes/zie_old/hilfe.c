
/**
 * HERE:
 * PROBS WONT USE
*/
// static t_parser	*make_parser_list(char **tokens)
// {
// 	int			i;
// 	t_parser	*node;
// 	t_parser	*list;

// 	i = 0;
// 	list = NULL;
// 	while (tokens[i])
// 	{
// 		node = parser_listnew(tokens[i]);
// 		if (!node)
// 		{
// 			printf("aint no node!\n");
// 			free(tokens);
// 			exit(EXIT_FAILURE);
// 		}
// 		parser_listadd_back(&list, node);
// 		i++;
// 	}
// 	return (list);
// }


/*
				NOTITIES
// already in list or put first in subarrays???
//then add to token lists, then those lists become the parser nodes
// ........ try with everything already in input list first....
	list of all input in parser list
	sort nodes into token lists
	need to know 
	- how many token lists - number of processes
	- how many tokens per list (per process)
	- 
*/





// void	parse_tokens(char **tokens)
// {
// 	t_tokens	*process;
// 	// t_parser	*list;
// 	int			proc_i;
// 	int			proc_count;

// 	// if (!tokens)
// 	// 	return (NULL);
// 	if (!tokens)
// 		return ;
// 	proc_i = 0;
// 	// list = NULL;
// 	proc_count = count_procs(tokens);
// 	process = (t_tokens *)malloc(sizeof(t_tokens) * proc_count);
// 	printf("proc_count = %i\n", proc_count);
// 	// shelly_input_print(list);
// 	while (proc_count > 0)
// 	{
// 		// list = make_parser_list(proc_count);
// 		*process = make_token_lists(tokens, proc_i);
// 		proc_count--;
// 		// proc_i++;
// 	}
// 	// while (proc_count >= 0)
// 	// {
// 	// 	// list = make_parser_list(proc_count);
// 	// 	process[proc_i] = make_token_lists(tokens, proc_i);
// 	// 	proc_count--;
// 	// 	proc_i++;
// 	// }
// 	// list = make_parser_list(process);
// 	// return (list);
// // }

