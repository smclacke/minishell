static	int	make_proc_arr(t_parser *proc, int proc_i, int proc_size)
{
	int		proc_j;
	int		token_size;

	proc_j = 0;
	token_size = 0;
	while (proc_j < proc_size)
	{
		if (!proc->tokens[proc->start])
		{
			free(proc->tokens);
			free(proc);
			return (0); // errrrror
		}
		token_size = ft_strlen(proc->tokens[proc->start]);
		proc->proc_arrs[proc_i][proc_j] = ft_strdup(proc->tokens[proc->start]);
		if (!proc->proc_arrs[proc_i][proc_j])
		{
			free(proc->tokens[proc_i]);
			free(proc->tokens);
			free(proc->proc_arrs);
			free(proc);
			return (0); // malloc error
		}
		proc_j++;
		proc->start++;
	}
	return (1);
}

/**
 * normynorm
 */
static	int	get_procs(t_parser *proc)
{
	int	i;
	int	proc_i;
	int	proc_size;

	i = 0;
	proc_i = 0;
	proc_size = 0;
	proc->proc_arrs = (char ***)malloc(sizeof(char **) * (proc->proc_count + 1));
	if (!proc->proc_arrs)
	{
		free (proc);
		return (0); // malloc error
	}
	while (proc->tokens[i])
	{
		proc->start = i;
		while (proc->tokens[i] && !is_pipe(proc->tokens[i]))
			i++;
		proc_size = (i - proc->start);
		proc->proc_arrs[proc_i] = (char **)malloc(sizeof(char *) * (proc_size + 1));
		if (!proc->proc_arrs)
		{
			free(proc->proc_arrs);
			free(proc);
			return (0); // malloc error
		}
		if (!make_proc_arr(proc, proc_i, proc_size))
			return (0); // error
		proc->proc_arrs[proc_i][proc_size] = NULL;
		if (proc->tokens[i] && is_pipe(proc->tokens[i]))
		{
			i++;
			proc_i++;
		}
	}
	return (1);
}