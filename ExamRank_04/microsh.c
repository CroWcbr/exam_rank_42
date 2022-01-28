#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

typedef struct s_cmd
{
	char	*cmd[20]; //**cmd;
	int		prev; // 1 - pipe || 0 - other
	int		next; // 1 - pipe || 0 - other
	int		prev_pipe;
}t_cmd;

int	ft_strlen(char *str)
{
	int i = 0;
	while (str[i])
		i++;
	return i;
}

void    fatal(void)
{
    write(2, "error: fatal\n", ft_strlen("error: fatal\n"));
    exit (1);
}

void my_execve(t_cmd *tmp, char **envr)
{
	int		fd[2];
	int		pid;
	int		ex;

	if (tmp->next && pipe(fd))
		fatal();
	if ((pid = fork()) < 0)
		fatal();
	if (pid == 0)
	{
		if (tmp->next && dup2(fd[1], STDOUT_FILENO) < 0)
			fatal();
		if (tmp->prev && dup2(tmp->prev_pipe, STDIN_FILENO) < 0)	
			fatal();
		if ((ex = execve(tmp->cmd[0], tmp->cmd, envr)) < 0)
        {
            write(2, "error: cannot execute ", ft_strlen("error: cannot execute "));
            write(2, tmp->cmd[0], ft_strlen(tmp->cmd[0]));
            write(2, "\n", 1);
        }
        exit(ex);
	}
	else
	{
		waitpid(pid, 0, 0);
		if (tmp->prev == 1)
			close(tmp->prev_pipe);
		if (tmp->next)
		{
			close(fd[1]);
			tmp->prev_pipe = fd[0];
		}
	}
}

int main(int argc, char **argv, char **envr)
{
	if (argc == 1)
		return 0;

	t_cmd	tmp;
	int i = 1;
	while (i < argc)
	{
		int start = i;
		while (argv[i] && strcmp(argv[i], "|") && strcmp(argv[i], ";"))
			i++;
		if (i == start)
			;
		else if (!strcmp(argv[start], "cd"))
		{
			if (i - start != 2)
				write(2, "error: cd: bad arguments\n", ft_strlen("error: cd: bad arguments\n"));
			else if (chdir(argv[start + 1]))
			{
				write(2, "error: cd: cannot change directory to ", ft_strlen("error: cd: cannot change directory to "));
				write(2, argv[start + 1], ft_strlen(argv[start + 1]));
				write(2, "\n", ft_strlen("\n"));
			}
		}
		else
		{
			tmp.cmd = NULL;
			tmp.prev = 0;
			tmp.next = 0;
			if (!strcmp(argv[start - 1], "|"))
				tmp.prev = 1;
			if (argv[i] && !strcmp(argv[i], "|"))
				tmp.next = 1;
//			tmp.cmd = (char**)malloc(sizeof(char *) * (i - start + 1));
			int j = -1;
			while (++j < i - start)
				tmp.cmd[j] = argv[start + j];
			tmp.cmd[j] = NULL;
			my_execve(&tmp, envr);
//			free(tmp.cmd);
		}
		i++;
	}
	return 0;
}
