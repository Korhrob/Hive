
#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*out;

	// Error checks, s1 or s2 == null or empty
	out = (char *) malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (out == 0)
		return(0);
	while (*s1 != 0)
	{
		*out = *s1;
		out++;
		s1++;
	}
	while (*s2 != 0)
	{
		*out = *s2;
		out++;
		s2++;
	}
	*out = 0;
	return (out);
}
