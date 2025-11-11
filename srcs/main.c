#include "pipex.h"

static int	init_pipex(t_pipex *px, char **argv)
{
	px->infile = open(argv[1], O_RDONLY);
	if (px->infile == -1)
	{
		error_perror(argv[1]);
		return (0);
	}
	px->outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0644);
	if (px->outfile == -1)
	{
		close(px->infile);
		error_perror(argv[4]);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv, char **envp)
{
	t_pipex	px;

	if (argc != 5)
	{
		error_msg("Usage: ./pipex file1 cmd1 cmd2 file2");
		return (1);
	}
	if (!init_pipex(&px, argv))
		return (1);
	if (!run_pipex(&px, argv, envp))
	{
		close(px.infile);
		close(px.outfile);
		return (1);
	}
	close(px.infile);
	close(px.outfile);
	return (0);
}

