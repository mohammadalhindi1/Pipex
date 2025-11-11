#include "pipex.h"

static void	first_child(t_pipex *px, char **argv, char **envp)
{
	char	*cmd[2];

	if (dup2(px->infile, STDIN_FILENO) == -1)
	{
		error_perror("dup2");
		exit(1);
	}
	if (dup2(px->pipefd[1], STDOUT_FILENO) == -1)
	{
		error_perror("dup2");
		exit(1);
	}
	close(px->pipefd[0]);
	close(px->pipefd[1]);
	close(px->infile);
	close(px->outfile);
	cmd[0] = argv[2];
	cmd[1] = NULL;
	execve(cmd[0], cmd, envp);
	error_perror(cmd[0]);
	exit(1);
}

static void	second_child(t_pipex *px, char **argv, char **envp)
{
	char	*cmd[2];

	if (dup2(px->pipefd[0], STDIN_FILENO) == -1)
	{
		error_perror("dup2");
		exit(1);
	}
	if (dup2(px->outfile, STDOUT_FILENO) == -1)
	{
		error_perror("dup2");
		exit(1);
	}
	close(px->pipefd[0]);
	close(px->pipefd[1]);
	close(px->infile);
	close(px->outfile);
	cmd[0] = argv[3];
	cmd[1] = NULL;
	execve(cmd[0], cmd, envp);
	error_perror(cmd[0]);
	exit(1);
}

int	run_pipex(t_pipex *px, char **argv, char **envp)
{
	if (pipe(px->pipefd) == -1)
	{
		error_perror("pipe");
		return (0);
	}
	px->pid1 = fork();
	if (px->pid1 == -1)
	{
		error_perror("fork");
		return (0);
	}
	if (px->pid1 == 0)
		first_child(px, argv, envp);
	px->pid2 = fork();
	if (px->pid2 == -1)
	{
		error_perror("fork");
		return (0);
	}
	if (px->pid2 == 0)
		second_child(px, argv, envp);
	close(px->pipefd[0]);
	close(px->pipefd[1]);
	waitpid(px->pid1, NULL, 0);
	waitpid(px->pid2, NULL, 0);
	return (1);
}

