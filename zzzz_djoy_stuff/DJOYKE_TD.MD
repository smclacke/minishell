------------------------------TO DO----------------------------

1) remove printf's

2) ERRORS TO STANDARD ERROR!

3) check to-do's

4) 
	minibleh:./fdsfdsf
	minishell: ./fdsfdsf: command not found
	dreijans@f0r3s13:~$ ./haha
	bash: ./haha: No such file or directory

5) get leak in malloc when ls | exit done twice

!!*we are not:*!!
- SHLVL
- export ls="ls -l"

REMEMBER! exit from parser when:
	- nothing after meta
	- unclosed quotes
	- pipe after pipe
	- malloc
	- if string doesnt come back exit

void	mini_forks(t_parser *lst, t_env **env, t_execute *data)
{
	char		*executable;
	char		**argv;
	int			cmd_type;

	init_pipes_child(data, lst);
	if (redirect(lst, data) == false)
		exit (lst->exit_code);
	if (data->error == false)
		exit (43);
	cmd_type = check_for_builtin(lst);
	if (cmd_type != 0)
	{
		do_builtin(lst, env, cmd_type);
		exit (lst->exit_code);
	}
	if (lst->proc->cmd == NULL)
		exit (127);
	executable = check_access(*env, lst, data);
	executable_check(lst, data, executable);
	// if (executable == NULL)
	// {
	// 	put_execute_error(lst);
	// 	exit (45);
	// }
	// if (data->error == false)
	// 	exit (lst->exit_code);
	// if (access(executable, X_OK) == -1)
	// {
	// 	put_permission_error(lst);
	// 	exit (EXIT_FAILURE);
	// }
	data->env_array = list_to_string(*env);
	argv = get_argv(lst);
	if (argv == NULL)
		exit(47);
	if (execve(executable, argv, data->env_array) == -1)
	{
		lst->exit_code = EXIT_FAILURE;
		exit(EXIT_FAILURE);
	}
}
 