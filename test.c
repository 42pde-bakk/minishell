#include <unistd.h>

int     main(int argc, char **argv)
{
    int i;
    char *str = "hello \n";

	if (argc == 3)
	{
		argv[1] = "hello";
	}
    i = 0;
	if (argv[1])
    	while (argv[1][i])
    	{
       	 	write(1, &argv[1][i], 1);
       	 	i++;
    	}
	// while (1);
	write(1, "\n", 1);
    return (42);
}
