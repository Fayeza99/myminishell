/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asemsey <asemsey@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/08 15:19:57 by asemsey           #+#    #+#             */
/*   Updated: 2024/04/08 16:22:17 by asemsey          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	mini_handler(int sig, siginfo_t *info, void *context)
{
	(void)info;
	(void)context;
	if (sig == SIGINT)
	{
		printf("\n");
		fflush(stdout);
		// new prompt!!!
	}
	else if (sig == SIGQUIT)
		;
	else if (sig == SIGTERM)
	{
		printf("\n");
		// disable_raw_mode((struct termios *)context);
		exit(EXIT_SUCCESS);
	}
}

void	disable_raw_mode(struct termios *original_termios)
{
	tcsetattr(STDIN_FILENO, TCSAFLUSH, original_termios);
}

void	enable_raw_mode(struct termios *original_termios)
{
	struct termios	raw;
	tcgetattr(STDIN_FILENO, original_termios);
	raw = *original_termios;
	raw.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}
