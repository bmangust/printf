#include <stdlib.h>

char	*ft_itoa_base(int value, int base)
{
	char *snum;
	char *s;
	int val;
	size_t cnt;

	val = value;
	cnt = 0;
	s = "0123456789abcdef";
	while(value)
	{
		value /= base;
		cnt++;
	}
	if (!(snum = (char*)malloc((cnt + 1) * sizeof(char))))
		return (NULL);
	snum[cnt--] = '\0';
	while(val)
	{
		snum[cnt--] = s[val % base];
		val /= base;
	}
	return snum;
}

char	*ft_itoa_baseu(int value, int base)
{
	char *snum;
	char *s;
	int val;
	size_t cnt;

	val = value;
	cnt = 0;
	s = "0123456789ABCDEF";
	while(value)
	{
		value /= base;
		cnt++;
	}
	if (!(snum = (char*)malloc((cnt + 1) * sizeof(char))))
		return (NULL);
	snum[cnt--] = '\0';
	while(val)
	{
		snum[cnt--] = s[val % base];
		val /= base;
	}
	return snum;
}