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


// /**
//  * @param node pointer to node in list given in the form of a string
//  * @param env pointer to linked list
//  * @brief export with no options, learned that double free 
//  * with freeing in an unrelated spot 
//  * might be overwriting a pointer and not allocating a new string.
//  * @todo 
//  * env does show the expanded version.
//  * Norm it!
//  * has_value doesnt work anymore, when has no value it still prints equal sign
//  * and it also prints in env which shouldnt happen, refer to old before push
// */
// void	ft_export(t_parser *node, t_env **env)
// {
// 	int		i;
// 	char	*str;
// 	char	*key;
// 	char	*value;
// 	int		has_value;

// 	key = 0;
// 	value = 0;
// 	i = 0;
// 	if (node->proc->str_count == 0)
// 	{
// 		export_print(*env);
// 		return ;
// 	}
// 	while (i < node->proc->str_count)
// 	{
// 		str = node->proc->str[i];
// 		while (str[i] && str[i] != '=')
// 			i++;
// 		has_value = get_key_value(str, &key, &value);
// 		// key = ft_substr(str, 0, i);
// 		// value = ft_substr(str, i + 1, ft_strlen(str + i) + 1);
// 		if (word_check(node, key, value) == true)
// 			return ;
// 		if (reassign_env(env, str, key, value) == true)
// 			return ;
// 		make_node(str, env, key, value);
// 		node->exit_code = E_USAGE;
// 		i++;
// 	}
// }

// /**
//  * @param temp linked list
//  * @param words 2D array with seperate words key and value
//  * @param cmd string containing command
//  * @brief checks if key and value are alphanumeric
//  * @return 1 if not alphanumeric, 0 is alphanumeric
// */
// static bool	is_valid_key(t_parser *temp, char *key, char *cmd)
// {
// 	int	i;
// 	printf("key = %s\n", key);

// 	if ((ft_isalpha(key[0]) == 0) && key[0] != '_')
// 	{
// 		put_custom_error(temp, cmd);
// 		return false;
// 	}
// 	i = 1;
// 	while (key[i])
// 	{
// 		if (key[i] != '_' && ft_isalnum(key[i]) == 0)
// 		{
// 			put_custom_error(temp, cmd);
// 			return false;
// 		}
// 		i++;
// 	}
// 	return true;
// }

// /**
//  * @param lst linked list
//  * @brief checks if the words are export and unset norm
//  * proof.
//  * key (word) first letter has:
//  * capital (H), lowercase (h), underscore (_) as first letter 
//  * else give error if given 99=djoyke as key
//  * minishell: export: `99=djoyke': not a valid identifier
//  * rest of word can only have numbers, letters and underscore.
//  * else give error export d@@=haha
//  * minishell: export: `d@@=haha': not a valid identifier
//  * same for unset
//  * @return true if wrong found with the words
//  * @todo the !word error part is for this edge case :
//  * export "" test=a
//  * 
//  * but comprimises this edge case which didnt work before
//  * but now doesnt work in a different way:
//  * export var=a
//  * export $var=test
//  * echo $var $a
//  * @todo why do I need list and value and what do my errors do?
//  * better way to do this
//  * 	words = null_check(str, lst);
// 	if (!words)
// 	{
// 		put_custom_error(lst, "export");
// 		mini_error(E_GENERAL, lst);
// 		return (true);
// 	}
// 	if ((mini_strcmp(cmd, "unset") == 0) && words[1])
// 	{
// 		put_custom_error(temp, cmd);
// 		return (true);
// 	}
// 	if (key_value_check(lst, words, "export") == 1)
// 	{
// 		ft_free_arr(words);
// 		return (true);
// 	}
// */
// bool	word_check(t_parser *lst, char *key, char *value)
// {
// 	t_parser	*temp;
// 	char		*cmd;

// 	cmd = lst->proc->cmd;
// 	temp = lst;
// 	if ((mini_strcmp(cmd, "unset") == 0) && value)
// 	{
// 		put_custom_error(temp, cmd);
// 		return (true);
// 	}
// 	if (is_valid_key(lst, key, "export") == false)
// 	{
// 		free(key);
// 		free(value);
// 		return (true);
// 	}
// 	return (false);
// }

// word check nonsense
//  * 	words = null_check(str, lst);
// 	if (!words)
// 	{
// 		put_custom_error(lst, "export");
// 		mini_error(E_GENERAL, lst);
// 		return (true);
// 	}
// 	if ((mini_strcmp(cmd, "unset") == 0) && words[1])
// 	{
// 		put_custom_error(temp, cmd);
// 		return (true);
// 	}
// 	if (key_value_check(lst, words, "export") == 1)
// 	{
// 		ft_free_arr(words);
// 		return (true);
// 	}


// /**
//  * @param node node in linked list
//  * @param cmd either unset or export
//  * @brief puts custom error message on STDOUT_FILENO
//  * @todo is index[0] okay?
// */
// void	put_custom_error(t_parser *node, char *cmd)
// {
// 	if (mini_strcmp(cmd, "export") == 0)
// 	{
// 		ft_putstr_fd("minishell: export: `", STDOUT_FILENO);
// 		ft_putstr_fd(node->proc->str[0], STDOUT_FILENO);
// 		ft_putstr_fd("': not a valid identifier\n", STDOUT_FILENO);
// 	}
// 	// else if (mini_strcmp(cmd, "unset") == 0)
// 	// {
// 	// 	ft_putstr_fd("minishell: unset: `", STDOUT_FILENO);
// 	// 	ft_putstr_fd(node->proc->str[0], STDOUT_FILENO);
// 	// 	ft_putstr_fd("': not a valid identifier\n", STDOUT_FILENO);
// 	// }
// 	else if (mini_strcmp(cmd, "exit") == 0)
// 	{
// 		ft_putstr_fd("exit\n", STDOUT_FILENO);
// 		ft_putstr_fd("minishell: exit: ", STDOUT_FILENO);
// 		ft_putstr_fd(node->proc->str[0], STDOUT_FILENO);
// 		ft_putstr_fd(ERROR_MESSAGE, STDOUT_FILENO);
// 	}
// }

// /**
//  * @param lst linked list
//  * @param key string containing key
//  * @param value string containing value
//  * @brief checks if the words are export and unset norm
//  * proof.
//  * key (word) first letter has:
//  * capital (H), lowercase (h), underscore (_) as first letter 
//  * else give error if given 99=djoyke as key
//  * minishell: export: `99=djoyke': not a valid identifier
//  * rest of word can only have numbers, letters and underscore.
//  * else give error export d@@=haha
//  * minishell: export: `d@@=haha': not a valid identifier
//  * same for unset
//  * @return true if wrong found with the words
//  * @todo
//  * export var=a
//  * export $var=test
//  * echo $var $a
// */
// bool	word_check(t_parser *lst, char *key, char *value)
// {
// 	t_parser	*temp;
// 	char		*cmd;

// 	cmd = lst->proc->cmd;
// 	temp = lst;
// 	// if ((mini_strcmp(cmd, "unset") == 0) && value)
// 	// {
// 	// 	put_custom_error(temp, cmd);
// 	// 	return (true);
// 	// }
// 	if (is_valid_key(lst, key, "export") == false)
// 		return (true);

// 	return (false);
// }

// /**
//  * @param argv terminal given arguments (for now)
//  * @param env pointer to environment
//  * @brief unset values by deleting nodes in env linked list
//  * @note if path is unset cant do env in bash
//  * @todo work check needs key and value now
// */
// void	ft_unset(t_parser *node, t_env **env)
// {
// 	int i;

// 	i = 0;
// 	if (node->proc->proc_count != 1)
// 		return ;
// 	// if (word_check(node->proc->str[i], env->key, env->value) == 1)
// 	// 	return ;
// 	while (node->proc->str[i])
// 	{
// 		mini_remove_env(node->proc->str[i], env);
// 		i++;
// 	}
// }