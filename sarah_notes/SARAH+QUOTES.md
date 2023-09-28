**Quote Expansion**

bash = 

echo "something << hello >in"
something << hello >in



- **SINGLE QUOTES**

    - preserves literal value of each character
    - a single quote may not occur between single quotes, even when 	preceded by a backslash GOOD

- **DOUBLE QUOTES**

    - double quote can be quoted within double quotes by preceding it with a backslash DON'T HANDLE THIS
    - preserve the literal value of all characters within the quotes
    - EXCEPT FOR ‘$’
        - BUT subject = Handle " (double quote) which should prevent the shell from interpreting the meta characters in the quoted sequence except for $ (dollar sign).

meta characters have special meaning and need to be quoted if representing itself
