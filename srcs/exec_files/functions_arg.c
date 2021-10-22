#include "../../lib/libmin.h"

int	compatibility_arg(TOKENTYPE type, int mode)
{
	if (type == CHAR_INUT || type == CHAR_TIRET)
		return (1);
	if (type == CHAR_ARG)
		return (1);
	if ((type == CHAR_APO || type == CHAR_GUILL) && !mode)
		return (1);
	if (type == CHAR_SPACE)
		return (1);
	return (0);
	return (mode);
}

char	*remove_for_arg(char *str)
{
	int	count;

	count = 0;
	while (str[count])
	{
		str[count] = str[count + 1];
		count++;
	}
	if (count > 1)
		str[count - 2] = '\0';
	else
		str[count] = 0;
	return (str);
}

void	check_for_arg(char **str, t_lexer *l, t_node *n)
{
	int	count;

	count = 0;
	while (str && str[count])
	{
		if (str[count][0] == '\'' || str[count][0] == '\"')
		{
			if (ft_strlen(str[count]) >= 2)
			{
				if (str[count][0] == str[count][ft_strlen(str[count]) - 1])
				{
					if (get_token_buffer(l, str[count]))
						get_token_buffer(l, str[count])->type = CHAR_INUT;
					n->str[count] = remove_for_arg(str[count]);
					count = join_close_token(l, str, count);
					if (count < 0)
						return ;
				}
				else
					count++;
			}
			else
				count++;
		}
		else
			count++;
	}
}

int		correct_name(t_lexer *l, t_token *t)
{
	char	*str;
	char	*str2;

	str = t->line;
	str2 = l->buffer[get_buffer_count(l, t)];
	if (!ft_strlen(str2))
		return (0);
	if (str[0] == '\'' || str[0] == '\"')
		{
			if (str[0] == str[ft_strlen(str2) - 1])
				return (1);
		}
	return (0);
}