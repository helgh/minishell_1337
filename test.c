#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/history.h>
#include <readline/readline.h>

// #include <stdio.h>
// #include <process.h>

int     s_d_qoutes(char *str)
{
    int i;

    i = 0;
    str++;
    while (*str)
    {
        if (*str == '\'')
            return (++i);
        i++;
        str++;
    }
    return (-1);
}

int		check_qoutes(char *str)
{
	int 	n;
	int 	i;
	int 	flag;
	char 	c;

    i = -1;
    n = 0;
    flag = 0;
	while (str[++i])
    {
		if (str[i] == '\"' || str[i] == '\'')
            n = s_d_qoutes(&str[i]);
        if (n == -1)
            return (-1);
        else
            i += n;
    }
	return (0);
}

int main() {

    char *str;
    int    i = 0;
    
    str = "\"\'\"\'hell\'o\'\"\'";
    i = check_qoutes(str);
    printf("%d\n", i);
}
