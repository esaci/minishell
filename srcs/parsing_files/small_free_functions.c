#include "../../lib/libmin.h"

int	small_free(t_lexer *l, void *ptr, void *ptr2, int mode)
{
	if (ptr)
		free(ptr);
	if (ptr2)
		free(ptr2);
	double_free(l->pwd);
	double_free(l->pathptr);
	free_lexer_nodes(l);
	free_lexer_tokens(l, 0);
	if (mode)
		free(l);
	return (0);
}