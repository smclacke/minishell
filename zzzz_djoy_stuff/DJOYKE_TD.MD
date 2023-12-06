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


minibleh:export var=a
minibleh:export $var=test
minibleh:echo $var
a
minibleh:echo $var=test

minibleh:echo $a

minibleh:export a=a
minibleh:export $a=b
minibleh:echo $a
a
minibleh:exit
exit

=================================================================
==1692876==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 6 byte(s) in 5 object(s) allocated from:
    #0 0x49a29d in malloc (/home/dreijans/Documents/rank3/minishell/minishell+0x49a29d)
    #1 0x4dead9 in ft_strdup (/home/dreijans/Documents/rank3/minishell/minishell+0x4dead9)
    #2 0x4d230c in expand_dollar /home/dreijans/Documents/rank3/minishell/src/expander/expand_dollar.c:115:15
    #3 0x4cfcef in ft_expand /home/dreijans/Documents/rank3/minishell/src/expander/expand.c:36:3
    #4 0x4d8c36 in execute /home/dreijans/Documents/rank3/minishell/src/executor/execute.c:154:2
    #5 0x4cb5dd in main /home/dreijans/Documents/rank3/minishell/src/main.c:66:3
    #6 0x7fd702e56d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16

SUMMARY: AddressSanitizer: 6 byte(s) leaked in 5 allocation(s).
make: *** [Makefile:93: run] Error 1