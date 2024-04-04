
// int	count_var_arr(char *str, char **env)
// {
// 	int	count;

// 	count = 0;
// 	while (str && *str)
// 	{
// 		if (*str == '$')
// 		{
// 			str++;
// 			if (*str && !is_whitespace(*str) && !in_env(var_name(str), env, 1))
// 				str++;
// 			else
// 				count++;
// 			if (*str == '$')
// 				str++;
// 			else
// 			{
// 				if (valid_var(*str, 0))
// 					str++;
// 				while (valid_var(*str, 1))
// 					str++;
// 			}
// 			if (*str)
// 				count++;
// 		}
// 		else
// 			str++;
// 	}
// 	return (count);
// }

// // get the total len after replacing all $
// int	var_len(char **env, char *str)
// {
// 	char	*var;
// 	char	*name;
// 	int		i;
// 	int		len;

// 	len = 0;
// 	i = 0;
// 	while (str && str[i])
// 	{
// 		if (str[i] == '$' && inside_quote(str, i) != 1)
// 		{
// 			name = var_name(&str[++i]);
// 			var = ft_getenv(name, env);
// 			if (!var)
// 				continue ;
// 			len += ft_strlen(var);
// 			i += ft_strlen(name);
// 			free(name);
// 			continue ;
// 		}
// 		i++;
// 		len++;
// 	}
// 	return (len);
// }

// // concatenates the 'name' variable to 'new'
// int	var_cat(char **env, char **new, char *name, int max_len)
// {
// 	char	*var;
// 	int		skip;

// 	var = ft_getenv(name, env);
// 	if (!var)
// 		return (free(name), -1);
// 	ft_strlcat(*new, var, max_len);
// 	skip = ft_strlen(name);
// 	free(name);
// 	// free(var);
// 	return (skip);
// }

// int	main(int argc, char **argv, char **env)
// {
// 	(void)argc;
// 	(void)argv;
// 	char **new_env = ft_arrdup(env);
// 	// char *new = add_variables(new_env, "\"\'$USER$USER\'\"");
// 	// printf("--%s--\n", new);
// 	printf("--%d--\n", count_var_arr("heyyyyyy", new_env));
// 	return 0;
// }
