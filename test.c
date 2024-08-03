#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <readline/history.h>
#include <readline/readline.h>

// #include <stdio.h>
// #include <process.h>

int     single_qoutes(char *str)
{
    int i;

    i = 0;
    str++;
    while (*str)
    {
        if (*str == '\'')
        {
            i++;
            return (i);
        }
        i++;
        str++;
    }
    return (-1);
}
int     double_qoutes(char *str)
{
    int i;

    i = 0;
    str++;
    while (*str)
    {
        if (*str == '\"')
        {
            i++;
            return (i);
        }
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
		if (str[i] == '\"')
            n = double_qoutes(&str[i]);
		else if (str[i] == '\'')
            n = single_qoutes(&str[i]);
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
    
    str = "hallo";
    i = check_qoutes(str);
    printf("%d\n", i);
}
