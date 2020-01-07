int ft_int_length_base(int value, int base)
{
	int cnt;

	cnt = 0;
	if (value <= 0) {
		if (base == 10)
			cnt++;
	}
	while (value) {
		value /= base;
		cnt++;
	}
	return (cnt);
}