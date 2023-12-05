------------------------------TO DO----------------------------

1) 
    static void	build(t_parser *lst, t_env **env, t_execute *data)
     * check the last while(wait(NULL) != -1) loop

2) 
    find solid evidence for allowing dprintf, if not just change it you lazy bum

3) 
    handle exit codes



for sarah

	if (!temp->cmd)
		mini_error("temp->cmd", E_USAGE, lst);
	if (!temp->next || temp->next->meta)
	{
		write(1, "\n", 1);
		lst->exit_code = E_USAGE;
		return ;
	}