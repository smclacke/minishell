**playing with here_doc in terminal:**

bash-3.2$ touch dummy
bash-3.2$ <<DJOYKE cat dummy
> hello
> some
> thing
> DJOYKE
bash-3.2$ <<DJOYKE cat >dummy
> hello
> some
> thing
> DJOYKE
bash-3.2$ <<EOF cat >dummy
> some
> things
>
bash-3.2$ <<EOF
> hello
> something
> please
> no
> deleting
> thank you
>
bash-3.2$
bash-3.2$
bash-3.2$
bash-3.2$ <<EOF cat
> some
> thing
>
bash-3.2$
bash-3.2$
bash-3.2$
bash-3.2$ <<EOF echo
> hello
>
bash-3.2$ <<EOF echo >
> hello
>
bash-3.2$ cat <<END
> some
> thigns
> in
> output
> on
> term
> END
some
thigns
in
output
on
term
bash-3.2$ | echo hello
bash: syntax error near unexpected token `|'

abc$abc

t_lexer->token->input+dollar+input



validate first token, cmd or redirect (check no more)
if good, define as which ever it is, token1->cat(cat) OR token1->HERE_DOC(<<)
typedef	struct s_lexer
{
	void				*input;
	void				*token; **t_lexer->token->cmd**
	char				*cmd;
	struct s_lexer		*next;
	t_signs				sign[8]; // do we need this and if so what do we do with it?
}	t_lexer;
