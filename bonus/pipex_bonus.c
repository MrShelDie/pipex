/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 17:04:34 by nick              #+#    #+#             */
/*   Updated: 2022/02/10 13:16:01 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"
#include "libft_tools.h"

static char	**get_paths(char *const *envp)
{
	int	i;

	i = -1;
	while (envp[++i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			return (ft_split(envp[i] + 5, ':'));
	}
	return (NULL);
}

static void	init_prime(
	int argc, char *const *argv, char *const *envp, t_prime *prime)
{
	prime->argc = argc;
	prime->argv = argv;
	prime->envp = envp;
	prime->envp_paths = get_paths(envp);
	prime->cmds_size = argc - 3;
	prime->here_doc = FALSE;
}

static void	fill_prime(int argc, char *const *argv, t_prime *prime)
{
	int		first_cmd_idx;
	int		i;

	first_cmd_idx = 2;
	if (!ft_strncmp(argv[1], "here_doc", 9))
	{
		first_cmd_idx = 3;
		prime->here_doc = TRUE;
		prime->cmds_size = argc - 4;
	}
	prime->cmds = (char *const **)malloc(sizeof(char **) * (prime->cmds_size));
	if (!prime->cmds)
		pipex_exit(prime, MALLOC, prime->argv[0], NULL);
	i = -1;
	while (++i + first_cmd_idx < argc - 1)
	{
		prime->cmds[i] = ft_split(argv[i + first_cmd_idx], ' ');
		if (!prime->cmds[i])
			pipex_exit(prime, MALLOC, prime->argv[0], NULL);
	}
}

static int	pipex(t_prime *prime)
{
	int		last_proc_status;
	int		status;
	int		pipefd[2];
	int		readfd;
	int		i;

	first_child(pipefd, prime);
	i = 1;
	if (prime->here_doc)
		i = 0;
	while (i++ < prime->cmds_size - 1)
	{
		readfd = pipefd[READ_END];
		middle_child(prime->cmds[i], pipefd, readfd, prime);
	}
	readfd = pipefd[READ_END];
	waitpid(last_child(readfd, prime), &last_proc_status, 0);
	i = 0;
	while (++i < prime->cmds_size)
		wait(&status);
	return (last_proc_status);
}

int	main(int argc, char **argv, char **envp)
{
	t_prime	prime;
	int		status;

	if (argc < 5)
		pipex_exit(NULL, ARGS, argv[0], NULL);
	init_prime(argc, argv, envp, &prime);
	fill_prime(argc, argv, &prime);
	status = pipex(&prime);
	free_prime(&prime);
	exit(status);
}
