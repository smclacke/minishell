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
    check all the to do's in code

2) 
    static void	build(t_parser *lst, t_env **env, t_execute *data)
     * check the last while(wait(NULL) != -1) loop

3) 
    find solid evidence for allowing dprintf, if not just change it you lazy bum

4) 
    handle exit codes

5) 

minishell 🍌cd src
minishell 🍌pwd
Current working directory: /home/dreijans/Documents/rank3/minishell/src
minishell 🍌cd ,.
minishell: cd: ,.: No such file or directory
minishell 🍌cd ..
minishell 🍌exit

==4119028==ERROR: AddressSanitizer: attempting double-free on 0x604000001b90 in thread T0:
    #0 0x49a042 in free (/home/dreijans/Documents/rank3/minishell/minishell+0x49a042)
    #1 0x4d62ed in reasing_value /home/dreijans/Documents/rank3/minishell/src/builtin/builtin_utils_two.c:24:2
    #2 0x4d3db0 in change_old_dir /home/dreijans/Documents/rank3/minishell/src/builtin/cd.c:105:2
    #3 0x4d3bfa in access_change /home/dreijans/Documents/rank3/minishell/src/builtin/cd.c:148:4
    #4 0x4d3933 in ft_cd /home/dreijans/Documents/rank3/minishell/src/builtin/cd.c:192:4
    #5 0x4d5b80 in do_builtin /home/dreijans/Documents/rank3/minishell/src/builtin/builtin_utils_one.c:41:3
    #6 0x4d8518 in single_builtin_cmd /home/dreijans/Documents/rank3/minishell/src/executor/execute_utils_two.c:36:4
    #7 0x4d6f9b in build /home/dreijans/Documents/rank3/minishell/src/executor/execute.c:128:6
    #8 0x4d6ef5 in execute /home/dreijans/Documents/rank3/minishell/src/executor/execute.c:151:2
    #9 0x4cb4f0 in main /home/dreijans/Documents/rank3/minishell/src/main.c:65:3
    #10 0x7f150af11d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16
    #11 0x7f150af11e3f in __libc_start_main csu/../csu/libc-start.c:392:3
    #12 0x41f3e4 in _start (/home/dreijans/Documents/rank3/minishell/minishell+0x41f3e4)

0x604000001b90 is located 0 bytes inside of 41-byte region [0x604000001b90,0x604000001bb9)
freed by thread T0 here:
    #0 0x49a042 in free (/home/dreijans/Documents/rank3/minishell/minishell+0x49a042)
    #1 0x4d3c85 in access_change /home/dreijans/Documents/rank3/minishell/src/builtin/cd.c:155:2
    #2 0x4d3933 in ft_cd /home/dreijans/Documents/rank3/minishell/src/builtin/cd.c:192:4
    #3 0x4d5b80 in do_builtin /home/dreijans/Documents/rank3/minishell/src/builtin/builtin_utils_one.c:41:3
    #4 0x4d8518 in single_builtin_cmd /home/dreijans/Documents/rank3/minishell/src/executor/execute_utils_two.c:36:4
    #5 0x4d6f9b in build /home/dreijans/Documents/rank3/minishell/src/executor/execute.c:128:6
    #6 0x4d6ef5 in execute /home/dreijans/Documents/rank3/minishell/src/executor/execute.c:151:2
    #7 0x4cb4f0 in main /home/dreijans/Documents/rank3/minishell/src/main.c:65:3
    #8 0x7f150af11d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16

previously allocated by thread T0 here:
    #0 0x49a5c9 in realloc (/home/dreijans/Documents/rank3/minishell/minishell+0x49a5c9)
    #1 0x7f150affd9ac in getcwd io/../sysdeps/unix/sysv/linux/getcwd.c:86:8
    #2 0x4d390f in ft_cd /home/dreijans/Documents/rank3/minishell/src/builtin/cd.c:189:18
    #3 0x4d5b80 in do_builtin /home/dreijans/Documents/rank3/minishell/src/builtin/builtin_utils_one.c:41:3
    #4 0x4d8518 in single_builtin_cmd /home/dreijans/Documents/rank3/minishell/src/executor/execute_utils_two.c:36:4
    #5 0x4d6f9b in build /home/dreijans/Documents/rank3/minishell/src/executor/execute.c:128:6
    #6 0x4d6ef5 in execute /home/dreijans/Documents/rank3/minishell/src/executor/execute.c:151:2
    #7 0x4cb4f0 in main /home/dreijans/Documents/rank3/minishell/src/main.c:65:3
    #8 0x7f150af11d8f in __libc_start_call_main csu/../sysdeps/nptl/libc_start_call_main.h:58:16

SUMMARY: AddressSanitizer: double-free (/home/dreijans/Documents/rank3/minishell/minishell+0x49a042) in free
==4119028==ABORTING
make: *** [Makefile:90: run] Error 1