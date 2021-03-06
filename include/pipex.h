/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 16:42:22 by nick              #+#    #+#             */
/*   Updated: 2022/02/16 15:51:25 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <errno.h>
# include <string.h>

# define FALSE 0
# define TRUE 1

# define READ_END 0
# define WRITE_END 1

/* The main data of the project */
typedef struct s_prime
{
	char *const	*argv;
	char *const	*paths;
	char *const	*envp;
	char *const	*cmds[2];
	char		*err_str;
}	t_prime;

/*	Displays an error message, clears data and ends the process */
void	pipex_exit(t_prime *prime, const char *program,
			const char *file, char *err_str);

/* Prepares pipe for the first process and forks it.
*  Returns the pid of the newly created process */
pid_t	first_child(int pipefd[2], t_prime *prime);

/* Prepares pipes for the last process and forks it.
*  Returns the pid of the newly created process */
pid_t	last_child(int readfd, t_prime *prime);

/* Replaces stdin and stdout with read and writefd respectively */
void	replace_stdio(t_prime *prime, int readfd, int writefd);

/* Checks the existence of the command file and access to it */
void	check_cmd(char *cmd_full_path, const char *cmd, t_prime *prime);

/* Iterates through all the paths specified in envp_path, returns
*  the full path of the cmd or NULL if the file was not found */
char	*find_cmd_path(const char *cmd, char *const *paths);

void	free_prime(t_prime *prime);

#endif
