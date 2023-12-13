
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


