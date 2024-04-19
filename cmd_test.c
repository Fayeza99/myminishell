# include <stdio.h>
# include <stdlib.h>
# include <readline/history.h>
# include <readline/readline.h>

int	is_whitespace(char c)
{
	return ((c >= 9 && c < 14) || c == 32);
}


// 0 - ok | 1 - incomplete(prompt again) | 2 - empty pipe(error)
// int	open_pipe_old(char *str)
// {
// 	int	open;
// 	int	i;

// 	open = 0;
// 	i = 0;
// 	while (str && str[i] && is_whitespace(str[i]))
// 		i++;
// 	if (str[i] && str[i] == '|')
// 		return (2);
// 	while (str && str[i])
// 	{
// 		if (open && str[i] == '|' && !inside_quote(str, i))
// 			return (2);
// 		else if (open && !is_whitespace(str[i]) && !inside_quote(str, i))
// 			open = 0;
// 		else if (str[i] == '|' && !inside_quote(str, i))
// 			open = 1;
// 		i++;
// 	}
// 	return (open);
// }

// 0 - ok | 1 - incomplete(prompt again) | 2 - empty pipe(error)
// flag: 1 is s_quote, 2 is d_quote, 4 is pipe
int	open_pipe(char *str)
{
	int	flag;

	flag = 0;
	while (str && *str && is_whitespace(*str))
		str++;
	if (str && *str && *str == '|')
		return (2);
	while (str && *str)
	{
		if (*str == '\'' && !(flag & ))
			flag ^= 1;
		else if (*str == '\"' && !(flag & 1))
			flag ^= 2;
		else if ((flag & 4) && *str == '|' && !(flag & 2 || flag & 1))
			return (2);
		else if ((flag & 4) && !is_whitespace(*str) && !(flag & 2 || flag & 1))
			flag ^= 4;
		else if (*str == '|' && !(flag & 2 || flag & 1))
			flag |= 4;
		str++;
	}
	if (flag & 4)
		return (1);
	return (0);
}

int main(int argc, char const *argv[])
{
	char *str = readline("> ");
	printf("%d\n", open_pipe(str));
	free(str);
	return 0;
}
