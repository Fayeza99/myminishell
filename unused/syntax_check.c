// 0 - none | 1 - s_quote open | 2 - d_quote open
// int	open_quotes(char *str)
// {
// 	int	d_quote;
// 	int	s_quote;

// 	s_quote = 0;
// 	d_quote = 0;
// 	while (str && *str)
// 	{
// 		if (*str == '\"' && d_quote)
// 			d_quote = 0;
// 		else if (*str == '\"' && !d_quote && !s_quote)
// 			d_quote = 1;
// 		else if (*str == '\'' && s_quote)
// 			s_quote = 0;
// 		else if (*str == '\'' && !s_quote && !d_quote)
// 			s_quote = 1;
// 		str++;
// 	}
// 	if (s_quote)
// 		return (1);
// 	if (d_quote)
// 		return (2);
// 	return (0);
// }

// // 0 - ok | 1 - incomplete(prompt again) | 2 - empty pipe(error)
// // flag: 1 is s_quote, 2 is d_quote, 4 is pipe
// int	open_pipe(char *str)
// {
// 	int	flag;

// 	flag = 0;
// 	while (str && *str && is_whitespace(*str))
// 		str++;
// 	if (str && *str && *str == '|')
// 		return (2);
// 	while (str && *str)
// 	{
// 		if (*str == '\'' && !(flag & 2))
// 			flag ^= 1;
// 		else if (*str == '\"' && !(flag & 1))
// 			flag ^= 2;
// 		else if ((flag & 4) && *str == '|' && !(flag & 2 || flag & 1))
// 			return (2);
// 		else if ((flag & 4) && !is_whitespace(*str) && !(flag & 2 || flag & 1))
// 			flag ^= 4;
// 		else if (*str == '|' && !(flag & 2 || flag & 1))
// 			flag |= 4;
// 		str++;
// 	}
// 	if (flag & 4)
// 		return (1);
// 	return (0);
// }
