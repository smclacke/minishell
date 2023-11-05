-----------------------SARAH UPDATE------------------------------

1) 
    Avoid using more than one global variable to indicate a received signal. Consider
    the implications: this approach ensures that your signal handler will not access your
    main data structures.
    Be carefull. This global variable cannot provide any other
    information or data access than the number of a received signal.
    Therefore it is forbidden to use "norm" type structures in global.

    we need to have a part in our linked list that keeps our exit codes. because we cant use the global for these.

    /**
    * @brief	specifies the different variable types of tokens from the
    * 			lexer that are parsed and then given to the executor
    * @param	cmd: first string in each process without redirect char
    * @param	meta: pipe, more, less, moremore, lessless. 
    * 			**dollar is excluded and handled as a string
    * @param	file: in and out files; after more, less and moremore chars
    * @param	str:  limiter for here_doc (string after <<) and all other input
    */
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

2) 
    minishell 🍌cat <<
    [0]      cmd = cat      file = (null)   meta = (null)   str = (null)    n_cmd = 1  hd_fd = -1
    [1]      cmd = (null)   file = (null)   meta = <<       str = (null)    n_cmd = 0  hd_fd = -1
    [1]    765848 segmentation fault (core dumped)  ./djoyke

    parser or lexer need to throw syntax errors!

3) 
    dreijans@f0r3s15:~/Documents/rank3/minishell$ cat Makefile > $bla
    bash: $bla: ambiguous redirect

    dreijans@f0r3s15:~/Documents/rank3/minishell$ cat | $bla | $bla
    dreijans@f0r3s15:~/Documents/rank3/minishell$ echo $bla (echoed empty argument)
    dreijans@f0r3s15:~/Documents/rank3/minishell$ echo $bla

    dreijans@f0r3s15:~/Documents/rank3/minishell$

    lastige zegt ruben 

------------------------------TO DO----------------------------

1) 
    Handle $? which should expand to the exit status of the most recently executed foreground pipeline. (no signals)

2) 
    Handle ctrl-C, ctrl-D and ctrl-\ which should behave like in bash.
    • In interactive mode:
    ◦ ctrl-C displays a new prompt on a new line.
    ◦ ctrl-D exits the shell.
    ◦ ctrl-\ does nothing.

3) 
    check all the to do's in code

4) 
    static void	build(t_parser *lst, t_env **env, t_execute *data)
     * check the last while(wait(NULL) != -1) loop

5) 
    fix double free in unset

6) 
    cd ""
    cd ''
    is equivalent of cd_. (cd .)

7) 
    find solid evidence for allowing dprintf, if not just change it you lazy bum

8) 
    1)  
        echi hi < infile > outfile
        check infile first
        infile does not exist so error
        no such file or directory
    2)  
        echi hi > outfile
        outfile created and stop the process
        command not found
    3) 
        echo hi < infile
        check file first
        no such file or directory
