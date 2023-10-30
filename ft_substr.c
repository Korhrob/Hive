
#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*out;

	// error checks
	// s == null, len == 0 or null, start > len
	out = (char *) malloc(len);
	if (out == 0)
		return (0);
	while (len > 0)
	{
		*out = *s;
		out++;
		s++;
		len--;
	}
	*out = 0;
	return (out);
}
