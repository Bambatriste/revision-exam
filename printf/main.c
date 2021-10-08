int	ft_printf(char *fmt, ...);

#include <stdio.h>

int main ()

{	
	int ret1 = 0;
	int ret2 = 0;

	/*ret1 =printf("PRINTF , str :%1.15s  nbr :%2.3d, hexa : %10.69x\n","to\0to",  -42, -127);*/
	ret2 = ft_printf("%%%%str : %s number : %d hexa : %x\n", "toto", -24, 240);	
	ret1 = printf("%%%%str : %s number : %d hexa : %x\n", "toto", -24, 240);	
	printf("ret true : %d , ret mine : %d", ret1, ret2);
}
