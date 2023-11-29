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
