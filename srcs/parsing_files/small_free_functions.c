#include "../../lib/libmin.h"

int	small_free(t_lexer *l, void *ptr, void *ptr2, int mode)
{
	rl_line_buffer[1] = '\0';
	double_free(l->pwd);
	double_free(l->pathptr);
	free_lexer_nodes(l, 0);
	free_lexer_tokens(l, 1);
	if (ptr)
		free(ptr);
	if (ptr2)
		free(ptr2);
	if (mode)
		free(l);
	return (0);
}