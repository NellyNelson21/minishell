#include "minishell.h"

void	deal_with_redir(t_tokens *t, t_processes *p)
{
	if (ft_strcmp(t->token, "<\0"))
		p->infile = ft_strdup(t->next->token);
	else if (ft_strcmp(t->token, "<<\0"))
		p->stop_word = ft_strdup(t->next->token);
	else if (ft_strcmp(t->token, ">\0"))
		p->outfile_with_replace = ft_strdup(t->next->token);
	else if (ft_strcmp(t->token, ">>\0"))
		p->outfile_without_replace = ft_strdup(t->next->token);
	else
		return ;
}

void	parse_arg(t_processes *p, t_tokens *t, t_arguments **args)
{
	if (p->args_to_cmd)
	{
		(*args)->next = malloc(sizeof(t_arguments));
		(*args) = (*args)->next;
		(*args)->arg = ft_strdup(t->token);
	}
	else
	{
		p->args_to_cmd = malloc(sizeof(t_arguments));
		p->args_to_cmd->arg = ft_strdup(t->token);
		(*args) = p->args_to_cmd;
	}
	(*args)->next = NULL;
}

void	parse_pipe(t_processes **p)
{
	(*p)->next = malloc(sizeof(t_processes));
	(*p) = (*p)->next;
	(*p)->idx += 1;
	(*p)->next = NULL;
}

void	parse(t_minishell *minishell)
{
	t_tokens	*t;
	t_processes	*p;
	t_arguments	*args;

	args = NULL;
	t = minishell->tokens;
	minishell->processes = malloc(sizeof(t_processes));
	p = minishell->processes;
	p->next = NULL;
	p->idx = 0;
	p->args_to_cmd = NULL;
	while (t)
	{
		if (!ft_strcmp(t->type_of_tocken, "redir\0"))
			deal_with_redir(t, p);
		else if (!ft_strcmp(t->type_of_tocken, "cmd\0"))
			p->cmd = ft_strdup(t->token);
		else if (!ft_strcmp(t->type_of_tocken, "arg\0"))
			parse_arg(p, t, &args);
		else if (!ft_strcmp(t->type_of_tocken, "pipe\0"))
			parse_pipe(&p);
		else
			return ;
		t = t->next;
	}
}
