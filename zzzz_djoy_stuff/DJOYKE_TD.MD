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
    ◦ ctrl-D exits the shell.

2) 
    check all the to do's in code

3) 
    static void	build(t_parser *lst, t_env **env, t_execute *data)
     * check the last while(wait(NULL) != -1) loop

4) 
    find solid evidence for allowing dprintf, if not just change it you lazy bum

5) 
    handle exit codes

6) 

minishell 🍌cd src
minishell 🍌pwd
Current working directory: /home/dreijans/Documents/rank3/minishell/src
minishell 🍌cd ,.
minishell: cd: ,.: No such file or directory
minishell 🍌cd ..
minishell 🍌exit

Direct leak of 41 byte(s) in 1 object(s) allocated from:
    #0 0x49a5c9 in realloc (/home/dreijans/Documents/rank3/minishell/minishell+0x49a5c9)
    #1 0x7ff06bbdc9ac in getcwd io/../sysdeps/unix/sysv/linux/getcwd.c:86:8
    #2 0x4d38e2 in ft_cd /home/dreijans/Documents/rank3/minishell/src/builtin/cd.c:188:18
    #3 0x4d5b00 in do_builtin /home/dreijans/Documents/rank3/minishell/src/builtin/builtin_utils_one.c:41:3
    #4 0x4d8498 in single_builtin_cmd /home/dreijans/Documents/rank3/minishell/src/executor/execute_utils_two.c:36:4
    #5 0x4d6f1b in build /home/dreijans/Documents/rank3/minishell/src/executor/execute.c:128:6
    #6 0x4d6e75 in execute /home/dreijans/Documents/rank3/minishell/src/executor/execute.c:151:2
    #7 0x4cb4f0 in main /home/dreijans/Documents/rank3/minishell/src/main.c:65:3
    #8 0x7ff06baf0d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16