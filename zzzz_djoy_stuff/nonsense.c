// /**
//  * @param env environment stored in linked list
//  * @brief prints linked list containing env key or value
// */
// void	print_env_list(t_env *lst)
// {
// 	int	i;

// 	i = 0;
// 	while (lst != NULL)
// 	{
// 		printf("iterations [%d]\n", i);
// 		i++;
// 		lst = lst->next;
// 	}
// }

// /**
//  * @param env environment stored in linked list
//  * @brief prints linked list containing env full
// */
// void	print_list_full(t_env *env)
// {
// 	while (env != NULL)
// 	{
// 		printf("%s\n", env->full);
// 		env = env->next;
// 	}
// }

// /**
//  * @param env environment stored in linked list
//  * @brief prints linked list containing env key or value
// */
// void	print_parser_list(t_parser *lst)
// {
// 	int i;

// 	i = 0;
// 	while (lst != NULL)
// 	{
// 		printf("||\n");
// 		printf("index = [%d], cmd = [%s]\n", i, lst->cmd);
// 		printf("index = [%d], str = [%s]\n", i, lst->str);
// 		// printf("index = [%d], meta = [%s]\n", i, lst->redirect_list->meta);
// 		// printf("next node\n");
// 		if (lst->next == NULL)
// 			printf("NULL\n");
// 		lst = lst->next;
// 		i++;
// 	}
// }

// /**
//  * @param lst environment in linked list
//  * @param env parsed linked list
//  * @param opwd string containing old working directory
//  * @param cwd string containing new working directory
//  * @brief checks acces of lst->str, changes directory
//  * changes enviroment PWD and OLDPWD.
//  * gives custom error if access not found
//  * cd: no such file or directory: %s\n", lst->str
//  * @todo fix cd | cd error message shouldnt display
// */
// static void	access_change(t_env **env, t_parser *lst)
// {
// 	char		cwd[PATH_MAX];

// 	getcwd(cwd, PATH_MAX);
// 	if (!lst || mini_strcmp(lst->str, "~") == 0)
// 		home_dir(lst, env);
// 	else if (mini_strcmp(lst->str, "-") == 0)
// 		old_pwd(lst, env);
// 	else if (access(lst->str, F_OK) == 0)
// 	{
// 		if (chdir(lst->str) == -1)
// 			no_such_file(lst);
// 	}
// 	else if (lst->str != NULL)
// 		no_such_file(lst);
// 	update_env(env, cwd, "OLDPWD");
// 	getcwd(cwd, PATH_MAX);
// 	update_env(env, cwd, "PWD");
// }

// /**
//  * @param env environment stored in linked list
//  * @brief prints linked list containing env key or value
// */
// void	print_parser_list(t_parser *lst)
// {
// 	int i;

// 	i = 0;
// 	while (lst != NULL)
// 	{
// 		printf("||\n");
// 		printf("index = [%d], cmd = [%s]\n", i, lst->cmd);
// 		printf("index = [%d], str = [%s]\n", i, lst->str);
// 		printf("index = [%d], meta = [%s]\n", i, lst->meta);
// 		printf("next node\n");
// 		if (lst->next == NULL)
// 			printf("NULL\n");
// 		lst = lst->next;
// 		i++;
// 	}
// }



// int	main(int argc, char **argv, char **envp)
// {
// 	char		*input;
// 	t_parser	*tokens;
// 	t_env		*env;
// 	int			og_stdout;
// 	int			og_stdin;


// 	(void) argc;
// 	(void) argv;
// 	env = NULL;
// 	env = env_list(envp, env);
// 	og_stdout = dup(STDOUT_FILENO);
// 	og_stdin = dup(STDIN_FILENO);
// 	while (1)
// 	{
// 		handle_signals(PARENT);
// 		input = readline(PROMPT);
// 		tokens = lexing(input);
// 		if (!input)
// 			exit(0);
// 		if (!is_space(input))
// 			add_history(input);
// 		tokens = lexer(input);
// 		free(input);
// 		if (!tokens)
// 			continue ;
// 		tokens = parser(tokens);
// 		if (!tokens)
// 			continue ;
// 		execute(&env, tokens);
// 		free_tokens(tokens);
// 		dup2(og_stdout, STDOUT_FILENO);
// 		dup2(og_stdin, STDIN_FILENO);
// 	}
// 	return (0);
// }



/*
echo code instead of input check
*/

	// if (!temp->cmd)
	// 	mini_error("temp->cmd", E_USAGE, lst);
	// if (!temp->next || temp->next->meta)
	// {
	// 	write(1, "\n", 1);
	// 	lst->exit_code = E_USAGE;
	// 	return ;
	// }