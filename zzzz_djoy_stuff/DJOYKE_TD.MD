-----------------------SARAH UPDATE------------------------------

1) 
    Avoid using more than one global variable to indicate a received signal. Consider
    the implications: this approach ensures that your signal handler will not access your
    main data structures.
    Be carefull. This global variable cannot provide any other
    information or data access than the number of a received signal.
    Therefore it is forbidden to use "norm" type structures in global.

    we need to have a part in our linked list that keeps our exit codes. because we cant use the global for these.

    typedef struct s_parser
    {
        void				*input;
        char				*cmd;
        char				*meta;
        char				*file;
        char				*str;
        int					n_cmd;
        --->// int					exit_code 
        --->// this will be updated after each process will happen automatically
        struct s_parser		*next;
    }				t_parser;

------------------------------TO DO----------------------------

1) 
    static void	build(t_parser *lst, t_env **env, t_execute *data)
     * check the last while(wait(NULL) != -1) loop

2) 
    find solid evidence for allowing dprintf, if not just change it you lazy bum

3) 
    handle exit codes

4) 

➜  minishell git:(djoyke) ✗ make run
 ---> Made!
minibleh:cd | cd

=================================================================
==918454==ERROR: LeakSanitizer: detected memory leaks

Direct leak of 41 byte(s) in 1 object(s) allocated from:
    #0 0x49a5c9 in realloc (/home/dreijans/Documents/rank3/minishell/minishell+0x49a5c9)
    #1 0x7f23348819ac in getcwd io/../sysdeps/unix/sysv/linux/getcwd.c:86:8
    #2 0x4d3c1d in ft_cd /home/dreijans/Documents/rank3/minishell/src/builtin/cd.c:166:18
    #3 0x4d57f0 in do_builtin /home/dreijans/Documents/rank3/minishell/src/builtin/builtin_utils_one.c:40:3
    #4 0x4d6cac in mini_forks /home/dreijans/Documents/rank3/minishell/src/executor/execute.c:99:3
    #5 0x4d8c33 in init_fork /home/dreijans/Documents/rank3/minishell/src/executor/execute_utils_two.c:56:3
    #6 0x4d8f1d in pipeline /home/dreijans/Documents/rank3/minishell/src/executor/execute_utils_two.c:100:4
    #7 0x4d738f in build /home/dreijans/Documents/rank3/minishell/src/executor/execute.c:130:2
    #8 0x4d72c2 in execute /home/dreijans/Documents/rank3/minishell/src/executor/execute.c:151:2
    #9 0x4cb4d7 in main /home/dreijans/Documents/rank3/minishell/src/main.c:61:3
    #10 0x7f2334795d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16

SUMMARY: AddressSanitizer: 41 byte(s) leaked in 1 allocation(s).
minibleh:^C
