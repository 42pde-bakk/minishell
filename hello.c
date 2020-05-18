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
    while (str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
	while (1)
	{}
    return (42);
}
