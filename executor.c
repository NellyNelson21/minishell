#include "minishell.h"

static char	*get_cmd(char **paths, char *cmd) // возвращает абсолютный путь к команде (.../bin/echo)
{
	char	*tmp_dir;
	char	*command;

	while (*paths)
	{
		tmp_dir = ft_strjoin(*paths, "/");
		command = ft_strjoin(tmp_dir, cmd);
		free(tmp_dir);
		if (access(command, 0) == 0)
			return (command);
		free(command);
		paths++;
	}
	return (NULL);
}

static char	*find_path(char **envp) //возвращает указатель на папку с путями к командам
{
	while (ft_strncmp("PATH", *envp, 4))
		envp++;
	return (*envp + 5);
}

static void	child_free(char **cmd_args, char *cmd)
{
	int	i;

	i = 0;
	while (cmd_args[i])
	{
		free(cmd_args[i]);
		i++;
	}
	free(cmd_args);
	free(cmd);
}

static void	parent_free(t_executor *exec)
{
	int	i;

	i = 0;
	while (exec->cmd_paths[i])
	{
		free(exec->cmd_paths[i]);
		i++;
	}
	free(exec->cmd_paths);
	free(exec->pipe);
}

static void	create_pipes(t_executor *exec)
{
	int	i;

	i = 0;
	while (i < exec->processes_num - 1)
	{
		if (pipe(exec->pipe + 2 * i) < 0)
			parent_free(exec);
		i++;
	}
}

void	close_pipes(t_executor *exec)
{
	int	i;

	i = 0;
	while (i < (exec->pipe_nmbs))
	{
		close(exec->pipe[i]);
		i++;
	}
}

static int	list_len(t_arguments *args_to_cmd)
{
	int	len;

	len =  0;
	while (args_to_cmd)
	{
		args_to_cmd = args_to_cmd->next;
		len++;
	}
	return (len);
}

static char	**get_cmds_from_list(t_arguments *args_to_cmd)
{
	char	**args;
	int		i;

	args = malloc(sizeof(char *) * list_len(args_to_cmd));
	i = 0;
	while (args_to_cmd)
	{
		args[i] = malloc(sizeof(char) * ft_strlen(args_to_cmd->arg));
		args[i] = args_to_cmd->arg;
		args_to_cmd = args_to_cmd->next;
		i++;
	}
	return(args);
}

static void	execute_cmd(t_processes *p, t_executor *exec, char **envp)
{
	pid_t		p_id;
	char		**cmd_args;
	char		*cmd;

	p_id = fork();
	if (!p_id)
	{
		// if (p->outfile_with_replace
		// 	|| p->outfile_without_replace
		// 	|| p->infile || p->stop_word)
		// 	{
		// 		//сделать dup для файлов
		// 	}
		//сделать dup между пайпами
		cmd_args = get_cmds_from_list(p->args_to_cmd); //вытаскивает аргументы из списка в виде массива строк
		cmd = get_cmd(exec->cmd_paths, p->cmd);
		if (!cmd)
		{
			//error: command not found or permition denied;
			child_free(cmd_args, cmd);
			//exit???
		}
		execve(cmd, cmd_args, envp);
	}
}

int	executor(t_minishell *minishell)
{
	t_processes	*p;
	t_executor	*exec;

	exec = malloc(sizeof(t_executor));
	p = minishell->processes;
	exec->processes_num = minishell->n_pipes + 1;
	exec->pipe_nmbs = 2 * minishell->n_pipes;
	exec->pipe = (int *)malloc(sizeof(int) * exec->pipe_nmbs);
	if (!exec->pipe)
	{
		//malloc error
		return (1);
	}
	exec->paths = find_path(minishell->env);
	exec->cmd_paths = ft_split(exec->paths, ':');
	if (!exec->cmd_paths || !exec->paths)
	{
		free(exec->pipe);
		return (1);
	}
	create_pipes(exec);
	while (p->idx < exec->processes_num)
	{
		execute_cmd(p, exec, minishell->env);
		p = p->next;
	}
	close_pipes(exec);
	waitpid(-1, NULL, 0);
	parent_free(exec);
	return (0);
}