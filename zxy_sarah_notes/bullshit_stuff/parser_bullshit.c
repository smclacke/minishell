
// static t_redirect	*handle_redirect(t_parser *tokens)
// {
// 	t_redirect	*reds;

// 	reds = (t_redirect *)malloc(sizeof(t_redirect));
// 	if (!reds)
// 		exit(EXIT_FAILURE); // fix this later
// 	init_red_struct(reds);
// 	// printf("(reds)tokens->input: [%s]\n", tokens->input);
// 	tokens->redirect_list = tokens->input;
// 	// printf("(reds)tokens->redirect_list: [%s]\n", (char *)tokens->redirect_list);
// 	reds->input = tokens->redirect_list;
// 	// printf("(reds)reds->input: [%s]\n", reds->input);
// 	reds->meta = reds->input;
// 	// printf("(reds)reds->meta: [%s]\n", reds->meta);

// 	return (reds);
// }



		
		// if (is_redirect(token_list))
		// {
		// 	// put reds in struct
		// 	reds = handle_redirect(token_list);
		// 	// printf("reds %s\n", reds->meta);
		// 	token_list->redirect_list = reds;
		// 	// printf("token->red->meta = [%s]\n", token_list->redirect_list->meta);
		// }
		// // if there was a redirect, need to check which so that if >, next node is file, 
		// // and if pipe, next is command ( don't use index anymore, just keep for first arg)
		// // so.... if (there was a sassy red and i need to do something with next node) ...
		// else
		// {
		// 	// puts rest in command struct as cmd or str
		// 	cmds = handle_commands(token_list, flag);
		// 	token_list->cmd_list = cmds;
		// }
		// printf("token->cmd->cmd = [%s]\n", token_list->cmd_list->cmd);
		// printf("token->cmd->strs = [%s]\n", token_list->cmd_list->strs);
		// printf("token->red->meta = [%s]\n", token_list->redirect_list->meta);
