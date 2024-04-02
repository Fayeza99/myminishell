#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

// fd_in fd_out cmd .....


typedef struct s_cmd
{
	char			**argv;
	int				fd_in;
	int				fd_out;
}	t_cmd;

int main(int argc, char *argv[], char **env)
{
	t_cmd cmd;


	cmd.fd_in = open(argv[1], O_RDONLY);
	cmd.fd_out = open(argv[2], O_WRONLY);
	cmd.argv = &argv[3];

	if (!fork())
	{
		if (cmd.fd_in != -1)
			dup2(cmd.fd_in, STDIN_FILENO);
		if (cmd.fd_out != -1)
			dup2(cmd.fd_out, STDOUT_FILENO);
		dprintf(2,"test\n");
		execve(cmd.argv[0], cmd.argv, env);
	}
	return 0;
}
