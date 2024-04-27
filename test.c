

int	ex_unset(t_mini *shell)
{
	int i = -1;
	int j = 1;
	while (shell->argv[j])
	{
		i = -1;
		while (shell->env[++i])
		{
			if (ft_strncmp(shell->env[i], shell->argv[j], ft_strchr(shell->env[i], '=') - shell->env[i]) == 0)
			{
				while (shell->env[i])
				{
					shell->env[i] = shell->env[i + 1];
					i++;
				}
			}
		}
		j++;
	}
	return (0);
}

