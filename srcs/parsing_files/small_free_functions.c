#include "../../lib/libmin.h"

int	small_free(t_lexer *l, void *ptr, void *ptr2, int mode)
{
	rl_line_buffer[1] = '\0';
	free_lexer_tokens(l, 0);
	free_lexer_nodes(l, mode);
	if (ptr)
		free(ptr);
	if (ptr2)
		free(ptr2);
	if (mode)
	{
		double_free(l->pwd);
		double_free(l->pathptr);
		free(l);
	}
	else
	{
		double_free(l->pwd);
		double_free(l->pathptr);
	}
	return (0);
}

int	small_finish_free(t_lexer *l, void *ptr, void *ptr2)
{
	double_free(l->pwd);
	double_free(l->pathptr);
	free(l);
	if (ptr)
		free(ptr);
	if (ptr2)
		free(ptr2);
	return (0);
}

void	free_list(t_list *env)
{
	t_list	*tmp;

	while(env)
	{
		free(env->content);
		tmp = env->next;
		free(env);
		env = tmp;
	}
}