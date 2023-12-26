/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbilgili <kbilgili@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:23:29 by kbilgili          #+#    #+#             */
/*   Updated: 2023/12/22 06:04:01 by kbilgili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <limits.h>
#include "libft.h"

void	handlemessage(int sig, siginfo_t *siginfo, void *context)
{
	static int	bits_remaining = -1;
	static char	current_char;

	(void)context;
	if (bits_remaining < 0)
	{
		bits_remaining = CHAR_BIT * sizeof(current_char);
	}
	if (sig == SIGUSR1)
		current_char |= (1 << bits_remaining);
	else if (sig == SIGUSR2)
		current_char &= ~(1 << bits_remaining);
	if (!bits_remaining && current_char)
		ft_putchar_fd(current_char, 1);
	else if (!bits_remaining && !current_char)
		kill(siginfo->si_pid, SIGUSR2);
	bits_remaining--;
	kill(siginfo->si_pid, SIGUSR1);
}

int	main(int argc, char **args)
{
	pid_t				server_pid;
	struct sigaction	act;

	if (argc != 1)
	{
		ft_putstr_fd(args[0], 1);
		ft_putstr_fd(" usage: ./server\n", 1);
	}
	server_pid = getpid();
	ft_putstr_fd("Server PID: ", STDOUT_FILENO);
	ft_putnbr_fd(server_pid, STDOUT_FILENO);
	ft_putchar_fd('\n', STDOUT_FILENO);
	act.sa_sigaction = handlemessage;
	sigemptyset(&act.sa_mask);
	act.sa_flags = SA_RESTART | SA_SIGINFO | SA_NODEFER;
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);
	while (1)
		usleep(300);
	return (0);
}
