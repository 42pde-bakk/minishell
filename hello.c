#include <unistd.h>

int     main(void)
{
    int i;
    char *str = "hello world\n";

    i = 0;
    while (str[i])
    {
        write(1, &str[i], 1);
        i++;
    }
    return (12);
}
