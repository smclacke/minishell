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




// /**
//  * @param node pointer to node in list given in the form of a string
//  * @param env pointer to linked list
//  * @brief export with no options, learned that double free 
//  * with freeing in an unrelated spot 
//  * might be overwriting a pointer and not allocating a new string.
// */
// void	ft_export(t_parser *node, t_env **env)
// {
// 	char	*new_key;
// 	char	*new_value;

// 	new_key = NULL;
// 	new_value = NULL;
// 	if (!node->next || node->n_cmd != 1)
// 	{
// 		export_print(*env);
// 		return ;
// 	}
// 	if (space_check(node) == 1)
// 		return ;
// 	if (word_check(node) == 1)
// 		return ;
// 	node = node->next;
// 	if (reassign_env(env, node, new_key, new_value) == 1)
// 		return ;
// 	make_node(node, env, new_key, new_value);
// }


// /**
//  * @param lst  parser linked list
//  * @brief checks if there's an space in the next node.
// */
// static int	space_check(t_parser *lst)
// {
// 	t_parser	*temp;

// 	// temp = lst->next;
// 	temp = lst;
// 	if (temp->next)
// 	{
// 		temp = temp->next;
// 		put_custom_error(temp, "export");
// 		return (1);
// 	}
// 	return (0);
// }

// /**
//  * @param lst parser linked list
//  * @brief set's linked list from cmd to next cmd to 2d array
//  * cmd at 0, plus args at 1 , 2 etc.
//  * @todo error code
//  * need to SAVE UNTIL PIPE MAYBE USE NUMBER OF CMDS
// */
// char	**get_argv(t_parser *lst)
// 	t_parser	*temp;
// 	char		**new_str;
// 	int			i;

// 	temp = lst->next;
// 	i = count_words(temp);
// 	// i = count_words(lst);
// 	// printf("i = [%d]\n", i);
// 	new_str = (char **)malloc(sizeof (char *) * (i + 2));
// 	if (new_str == NULL)
// 		mini_error(E_MALLOC, lst);
// 	// temp = lst->next;
// 	new_str[0] = lst->cmd;
// 	i = 1;
// 	new_str = fill_array(temp, new_str, i);
// 	// new_str = fill_array(lst, new_str, i);
// 	return (new_str);

// /**
//  * @param lst linked list containing commands and atributes
//  * @param env linked list containing environment
//  * @param data struct containing fd's and 2d arrays needed for execution
//  * @brief checks parser input for executable and executes with execve
//  *  replace exit int with the existatus global we pass on
//  * @todo added id !lst->cmd to stop segfault NORM IT
//  * 
// */
// void	mini_forks(t_parser *lst, t_env **env, t_execute *data)
// {
// 	char		*executable;
// 	char		**test;

// 	test = get_argv(lst);
// 	// print_array(test);
// 	data->env_array = list_to_string(*env, lst);
// 	init_pipes_child(data, lst);
// 	redirect(lst, data);
// 	if (data->error == false)
// 		exit (0);
// 	if (check_for_builtin(lst))
// 	{
// 		do_builtin(lst, env);
// 		exit (0);
// 	}
// 	if (!lst->cmd)
// 		exit (0);
// 	executable = check_access(*env, lst, data);
// 	// if (data->error == false)
// 	// 	exit (0);
// 	// if (access(executable, F_OK) == -1)
// 	// {
// 	// 	put_execute_error(lst);
// 	// 	// exit (0);
// 	// 	// return ;
// 	// }
// 	// if (access(executable, X_OK) == -1)
// 	// {
// 	// 	put_permission_error(lst);
// 	// 	// exit (0);
// 	// 	// return ;
// 	// }
// 	// if (execve(executable, get_argv(lst), data->env_array) == -1)
// 	if (execve(executable, test, data->env_array) == -1)
// 		mini_error (E_GENERAL, lst);
// 	exit (0);
// }

// /**
//  * @param lst parser linked list
//  * @param env  environment linked list
//  * @param data execute struct
//  * @brief child execution process, calls init_pipes
//  * init_forks and close_between in a while loop
//  * @todo which version if statement? remove printf statement
// */
// void	pipeline(t_parser *lst, t_env **env, t_execute *data)
// {
// 	int	count;
// 	int	i;

// 	count = lst->n_cmd;
// 	i = 0;
// 	while (lst)
// 	{
// 		// if (count >= 0)
// 		// if ((count >= 1 && lst->cmd) || (count == 0 && lst->meta))
// 		// if (count >= 1)
// 		if (count >= 1 && lst->cmd)
// 		{
// 			init_pipe(i, count, data, lst);
// 			init_fork(lst, env, data);
// 			close_between(data, lst);
// 			count--;
// 			i++;
// 		}
// 		lst = lst->next;
// 	}
// }

// /**
//  * @param env linked list with environment
//  * @param node noded from parser linked list
//  * @param data struct containing fd's and 2d arrays needed for execution
//  * @brief checks is command has access
//  * @todo exit codes
// */
// static char	*check_access(t_env *env, t_parser *node, t_execute *data)
// {
// 	char	*ok_path;
// 	char	*command;
// 	int		i;

// 	i = 0;
// 	if (!node->cmd)//
// 		return (node->cmd);//
// 	if (!absolute_check(node) && parse_path(env, data, node))
// 	{
// 		while (data->path && data->path[i] != NULL)
// 		{
// 			command = ft_strjoin("/", node->cmd);
// 			if (command == NULL)
// 				mini_error (E_MALLOC, node);
// 			ok_path = ft_strjoin(data->path[i], command);
// 			if (command == NULL)
// 				mini_error (E_MALLOC, node);
// 			free(command);
// 			if (access(ok_path, F_OK) == 0)
// 				return (ok_path);
// 			free(ok_path);
// 			i++;
// 		}
// 		put_execute_error(node);
// 		data->error = false;
// 	}
// 	return (node->cmd);
// }