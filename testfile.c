#include <unistd.h>
// #include "./include/libft/libft.h"

int main(void)
{
	// char *str = ft_itoa(getpid());
	// printf("%d\n\n", getpid());
	write(1, "hello world\n", 12);
	// ft_putendl_fd(str, 2);
	return (0);
}
