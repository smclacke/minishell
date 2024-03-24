
![shelly'](https://github.com/smclacke/minishell/assets/115113929/dd8ced59-ea7f-4502-a716-2b6bb1e52671)

Image: https://www.caseashells.com/

# Minishell

*As beautiful as a shell*

Collaborative work with https://github.com/DjoykeAbyah

This is a basic shell created using Bash as a reference.

Built in commands include:

 - echo (-n)
 - cd (relative or absolute path)
 - pwd
 - export
 - unset
 - env
 - exit

- Unclosed quotes are not handled
- Single quotes prevent the shell from interpreting the meta-characters
- Double quotes prevent the shell from interpreting meta-characters except for dollar ($)
- Signals include ctrl -C ctrl -D ctrl -\
- Environment variables can be expanded to there values including $? giving the most recent exit status
- Pipes (|) output each command in the pipeline, connecting to the input of the next command via pipe
- Redirections include infile (<) outfile (>) here_doc delimiter (<<) output in append mode (>>)
- 
