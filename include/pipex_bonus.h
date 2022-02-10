/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nick <nick@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/06 16:42:22 by nick              #+#    #+#             */
/*   Updated: 2022/02/10 13:14:02 by nick             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>

# define FALSE 0
# define TRUE 1

# define READ_END 0
# define WRITE_END 1

/* The main data of the project */
typedef struct s_prime
{
	char *const	*argv;
	char *const	*envp_paths;
	char *const	*envp;
	char *const	**cmds;
	int			cmds_size;
	int			here_doc;
	int			argc;
}	t_prime;

/* Error handling codes */
typedef enum e_error
{
	ARGS,
	MALLOC,
	PIPE,
	FORK,
	CMD_NOT_FOUND,
	FILE_NOT_FOUND,
	FILE_PERM,
	FILE_OPEN,
	DUP,
	EXECVE,
	NONE
}	t_error;

/*	Displays an error message, clears data and ends the process */
void	pipex_exit(t_prime *prime, t_error error,
			const char *program, const char *file);

/* Prepares pipe for the first process and forks it */
void	first_child(int pipefd[2], t_prime *prime);

/* Prepares pipes for the middle process and forks it */
void	middle_child(char *const *cmd, int pipefd[2],
			int readfd, t_prime *prime);

/* Prepares pipes for the last process and forks it. Returns the pid
*  of the process so that the calling function can call waitpid*/
pid_t	last_child(int readfd, t_prime *prime);

/* If there is here_doc, then this process is executed
*  first, binds stdin to the first command */
void	here_doc_exec(t_prime *prime, int writefd);

/* The first process connects the file for reading, the first
*  command and the second command. Not executed if there is a here_doc */
void	first_child_exec(t_prime *prime, int writefd);

/* The middle child processes are connected to each other using pipe */
void	middle_child_exec(t_prime *prime, char *const *cmd,
			int readfd, int writefd);

/* The last process connects using pipe
*  to the previous one and opens the file for writing */
void	last_child_exec(t_prime *prime, int readfd);

void	replace_stdio(t_prime *prime, int readfd, int writefd);

/* Checks the existence of the command file and access to it */
void	check_cmd(char *cmd_full_path, const char *cmd, t_prime *prime);

/* Iterates through all the paths specified in envp_path, returns
*  the full path of the cmd or NULL if the file was not found */
char	*find_cmd_full_path(const char *cmd, char *const *envp_paths);

void	free_prime(t_prime *prime);

#endif
