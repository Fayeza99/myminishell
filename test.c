#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// fd_in fd_out cmd .....

static int	wordcount(const char *str, char c)
{
	int	words;

	words = 0;
	while (str && *str)
	{
		while (*str && *str == c)
			str++;
		if (*str && *str != c)
			words++;
		while (*str && *str != c)
			str++;
	}
	return (words);
}

static char	*ft_copy(const char *str, char c)
{
	int		i;
	char	*s;

	i = 0;
	while (str && str[i] && str[i] != c)
		i++;
	s = (char *)malloc(sizeof(char) * (i + 1));
	if (!s)
		return (NULL);
	i = 0;
	while (str && *str && *str != c)
		s[i++] = *str++;
	s[i] = '\0';
	return (s);
}
size_t	ft_strlen(const char *s1)
{
	int	i;

	i = 0;
	while (s1 && s1[i])
		i++;
	return (i);
}

void	*free_all(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		strs[i++] = NULL;
	}
	free(strs);
	return (NULL);
}

char	**ft_split(const char *str, char c)
{
	char	**strs;
	int		v[2];

	v[0] = wordcount(str, c);
	strs = (char **)malloc(sizeof(char *) * (v[0] + 1));
	if (!strs)
		return (NULL);
	v[1] = 0;
	while (v[1] < v[0])
	{
		while (str && *str && *str == c)
			str++;
		strs[v[1]++] = ft_copy(str, c);
		if (!strs[v[1] - 1])
			return ((char **)free_all(strs));
		while (str && *str && *str != c)
			str++;
	}
	strs[v[1]] = NULL;
	return (strs);
}


// typedef struct s_cmd
// {
// 	char			**argv;
// 	int				fd_in;
// 	int				fd_out;
// }	t_cmd;

// int main(int argc, char *argv[], char **env)
// {
// 	t_cmd cmd;


// 	cmd.fd_in = open(argv[1], O_RDONLY);
// 	cmd.fd_out = open(argv[2], O_WRONLY);
// 	cmd.argv = &argv[3];

// 	if (!fork())
// 	{
// 		if (cmd.fd_in != -1)
// 			dup2(cmd.fd_in, STDIN_FILENO);
// 		if (cmd.fd_out != -1)
// 			dup2(cmd.fd_out, STDOUT_FILENO);
// 		dprintf(2,"test\n");
// 		execve(cmd.argv[0], cmd.argv, env);
// 	}
// 	return 0;
// }

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	dlen;
	size_t	slen;
	size_t	i;

	i = 0;
	dlen = strlen(dst);
	slen = strlen(src);
	if (dstsize == 0)
		return (slen);
	if (dstsize <= dlen)
		slen += dstsize;
	else
		slen += dlen;
	while (src[i] != 0 && dlen + 1 < dstsize)
	{
		dst[dlen++] = src[i++];
	}
	dst[dlen] = 0;
	return (slen);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		i;
	char	*s3;

	i = 0;
	if (s1)
		i += strlen(s1);
	if (s2)
		i += strlen(s2);
	i++;
	s3 = malloc (sizeof(char) * i);
	if (s3 == 0)
		return (0);
	s3[0] = '\0';
	if (s1 && s1[0] != 0)
		ft_strlcat(s3, s1, i);
	if (s2 && s2[0] != 0)
		ft_strlcat(s3, s2, i);
	return (s3);
}

////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////

char *find_path(char *s)
{
	char	*path;
	char	**all_path;
	char	*cmd;
	int		i;
	char	*tmp;
	
	path = getenv("PATH");
	all_path = ft_split(path, ':');
	i = 0;
	tmp = ft_strjoin("/", s);
	while (all_path[i])
	{
		cmd = ft_strjoin(all_path[i], tmp);
		if (access(cmd, X_OK) == 0)
			break;
		free (cmd);
		i++;
	}
	return (cmd);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("Usage: %s <executable_name>\n", argv[0]);
        return 1;
    }

    char *executable_name = argv[1];
    char *path_to_executable = find_path(executable_name);

    if (path_to_executable == NULL) {
        printf("Executable '%s' not found in PATH\n", executable_name);
    } else {
        printf("Path to executable '%s': %s\n", executable_name, path_to_executable);
    }

    return 0;
}
