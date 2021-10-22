#include "../../lib/libmin.h"

int	small_free(t_lexer *l, void *ptr, void *ptr2, int mode)
{
	free_lexer_tokens(l, 0);
	free_lexer_nodes(l, 0);
	if (ptr)
		free(ptr);
	if (ptr2)
		free(ptr2);
	if (mode && l)
	{
		double_free(l->pwd);
		double_free(l->pathptr);
		free_env(l->envp);
		free(l);
	}
	return (0);
}

int	small_finish_free(t_lexer *l, void *ptr, void *ptr2)
{
	if (l)
	{
		double_free(l->pwd);
		double_free(l->pathptr);
		l->envp = free_env(l->envp);
		free(l);
	}
	if (ptr)
		free(ptr);
	if (ptr2)
		free(ptr2);
	return (0);
}