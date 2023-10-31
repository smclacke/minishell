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
    review the checking of the builtins because its case sensitive

    cd:

    * relative: cd src
    * absolute: cd src/bin/pannekoek/whatever TESTT!!!
    * 				cd alone gives prompt back
    * 				cd jfhjvhs gives: cd: no such file or directory: jfhjvhs
    * line 66: check if needs error message with exit
    * 			give prompt back, and endline?

    export, cd , exit, unset before childprocess because you need the environment. and exit needs to exit the whole program.
    rest in the child proces.

4) 
    check all the to do's in code

5) 
    ls |
    multiple times? does that fail?

6) 
    static void	build(t_parser *lst, t_env **env, t_execute *data)
     * check the last while(wait(NULL) != -1) loop

7) 
    fix double free in unset

8) 
    cd ""
    cd ''
    is equivalent of cd_. (cd .)