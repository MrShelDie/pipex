/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_error_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 17:08:44 by nick              #+#    #+#             */
/*   Updated: 2022/02/10 13:17:59 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "libft_tools.h"

static void	print_error_msg(t_error error)
{
	if (error == ARGS)
		ft_putstr_fd("Too few argumets\n", 2);
	else if (error == MALLOC)
		ft_putstr_fd("Memory allocation error\n", 2);
	else if (error == PIPE)
		ft_putstr_fd("Pipe creation error\n", 2);
	else if (error == FORK)
		ft_putstr_fd("Error when creating a new process\n", 2);
	else if (error == CMD_NOT_FOUND)
		ft_putstr_fd("command not found\n", 2);
	else if (error == FILE_NOT_FOUND)
		ft_putstr_fd("No such file or directory\n", 2);
	else if (error == FILE_PERM)
		ft_putstr_fd("Permission denied\n", 2);
	else if (error == FILE_OPEN)
		ft_putstr_fd("File opening error\n", 2);
	else if (error == DUP)
		ft_putstr_fd("I/O stream redirection error\n", 2);
	else if (error == EXECVE)
		ft_putstr_fd("process start execution error\n", 2);
}

static void	pipex_perror(t_error error, const char *program, const char *file)
{
	ft_putstr_fd(program, 2);
	ft_putstr_fd(": ", 2);
	if (file != NULL)
	{
		ft_putstr_fd(file, 2);
		ft_putstr_fd(": ", 2);
	}
	if (error != NONE)
		print_error_msg(error);
}

void	free_prime(t_prime *prime)
{
	if (prime)
	{
		if (prime->envp_paths)
			ft_free_split((char **)prime->envp_paths);
		if (prime->cmds)
		{
			while (--prime->cmds_size >= 0)
				ft_free_split((char **)prime->cmds[prime->cmds_size]);
		}
	}
}

void	pipex_exit(
	t_prime *prime, t_error error, const char *program, const char *file)
{
	if (error != NONE)
		pipex_perror(error, program, file);
	free_prime(prime);
	exit(EXIT_SUCCESS);
}
