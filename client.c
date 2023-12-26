/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kbilgili <kbilgili@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/21 15:23:14 by kbilgili          #+#    #+#             */
/*   Updated: 2023/12/22 05:21:50 by kbilgili         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <limits.h>
#include "libft.h"

int	args_verifier(int argc, char **args)
{
	if (argc < 3 || args[1] == NULL
		|| ft_atoi(args[1]) <= 0 || ft_strlen(args[1]) == 0)
	{
		ft_putstr_fd("Usage: ./client [PID] [message]", STDOUT_FILENO);
		exit(-1);
	}
	if (argc < 3 || args[2] == NULL)
	{
		ft_putstr_fd("Usage: ./client [PID] [message]", STDOUT_FILENO);
		return (-1);
	}
	if (kill(ft_atoi(args[1]), 0) < 0)
	{
		ft_putstr_fd("Invalid PID.\n", STDOUT_FILENO);
		exit(-1);
	}
	return (1);
}

void	handle_first_bit(char *c, pid_t existing_pid, int *bits_remaining)
{
	*bits_remaining = CHAR_BIT * sizeof(*c);
	if (*c)
	{
		if ((*c & (1 << *bits_remaining)))
			kill(existing_pid, SIGUSR1);
		else
			kill(existing_pid, SIGUSR2);
		(*bits_remaining)--;
	}
	else
	{
		kill(existing_pid, SIGUSR2);
		(*bits_remaining)--;
	}
}

void	send_message(char *message, pid_t server_pid)
{
	static char		*message_data;
	static int		index = 0;
	static int		bits_remaining = -1;
	static pid_t	existing_pid;

	if (server_pid != 0)
	{
		message_data = message;
		existing_pid = server_pid;
	}
	if (bits_remaining < 0)
		handle_first_bit(&message_data[index], existing_pid, &bits_remaining);
	else
	{
		if ((message_data[index] & (1 << bits_remaining)))
			kill(existing_pid, SIGUSR1);
		else
			kill(existing_pid, SIGUSR2);
		if (bits_remaining == 0 && message_data[index] != '\0')
			index++;
		bits_remaining--;
	}
}

void	acknowledge(int sig)
{
	if (sig == SIGUSR1)
		send_message(0, 0);
	else if (sig == SIGUSR2)
	{
		ft_putstr_fd("Message received by the server.", STDOUT_FILENO);
		exit(0);
	}
}

int	main(int argc, char **args)
{
	pid_t	server_pid;
	char	*message;

	args_verifier(argc, args);
	server_pid = (pid_t)ft_atoi(args[1]);
	message = args[2];
	signal(SIGUSR1, &acknowledge);
	signal(SIGUSR2, &acknowledge);
	send_message(message, server_pid);
	while (1)
		usleep(300);
	return (0);
}
