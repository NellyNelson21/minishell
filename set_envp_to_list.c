#include "minishell.h"

static t_envp	*lst_get_last_elem(t_envp *list)
{
	if (!list)
		return (NULL);
	if (!list->next)
		return (list);
	else
	{
		while (list->next)
			list = list->next;
		return (list);
	}
}

static t_envp	*lst_init_new_elem(char *key, char *value)
{
	t_envp	*lst_new_elem;

	lst_new_elem = malloc(sizeof(t_tokens));
	if (lst_new_elem && key && value)
	{
		lst_new_elem->key = ft_strdup(key);
		lst_new_elem->value = ft_strdup(value);
		lst_new_elem->next = NULL;
		return (lst_new_elem);
	}
	return (NULL);
}

static t_envp	*lst_add_back(t_envp *list_head, t_envp *elem)
{
	t_envp	*elem_to_add;

	if (!list_head)
		list_head = elem;
	else
	{
		elem_to_add = lst_get_last_elem(list_head);
		elem_to_add->next = elem;
	}
	return (list_head);
}

static char	*get_key(char *str, int n)
{
	char	*processed_str;
	int		processed_str_len;
	int		i;

	i = 0;
	processed_str_len = n;
	processed_str = malloc(sizeof(char) * (processed_str_len + 1));
	while (i < processed_str_len)
	{
		processed_str[i] = str[i];
		i++;
	}
	processed_str[i] = '\0';
	return (processed_str);
}

static char	*get_value(char *str, int n)
{
	char	*processed_str;
	int		processed_str_len;
	int		j;
	int		i;

	j = n + 1;
	i = 0;
	processed_str_len = ft_strlen(str) - n - 1;
	processed_str = malloc(sizeof(char) * (processed_str_len + 1));
	while (i < processed_str_len)
	{
		processed_str[i] = str[j];
		i++;
		j++;
	}
	processed_str[i] = '\0';
	return (processed_str);
}

t_envp	*set_envp_to_list(char **envp)
{
	t_envp	*head;
	int		i;
	int		j;
	char	*key;
	char	*value;

	head = NULL;
	i = 0;
	while (envp[i++])
	{
		j = 0;
		while (envp[i][j])
		{
			if (envp[i][j] == '=')
			{
				key = get_key(envp[i], j);
				value = get_value(envp[i], j);
				head = lst_add_back(head, lst_init_new_elem(key, value));
				free_if_not_null_s(key, value);
				break ;
			}
			j++;
		}
	}
	return (head);
}
