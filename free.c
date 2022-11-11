#include "minishell.h"

void	*free_list(t_tokens *list_head)
{
	t_tokens	*temp;

	while (list_head != NULL)
	{
		temp = list_head;
		list_head = list_head->next;
		free(temp);
	}
	return (NULL);
}

void	free_if_not_null(void *pointer)
{
	if (pointer)
		free(pointer);
}

void	free_if_not_null_s(void *pointer1, void *pointer2)
{
	if (pointer1)
		free(pointer1);
	if (pointer2)
		free(pointer2);
}

void	*free_and_return_null(t_tokens *list_head, char *uncovered_token, char *readed_line)
{
	free_if_not_null_s(uncovered_token, readed_line);
	free_list(list_head);
	return (NULL);
}

int free_and_return_1(t_tokens *list_head, char *readed_line)
{
	free_if_not_null(readed_line);
	free_list(list_head);
	return (1);
}

void	free_while_result(t_tokens *list_head, char *readed_line)
{
	free_list(list_head);
	free_if_not_null(readed_line);
}