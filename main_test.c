#include "get_next_line.h"

char *func(char *str)
{
        static char *ptr ;

        //ptr = NULL;
        if (str)
        ptr = ft_strdup(str);
        return (ptr);
}


int main()
{
        int fd = open("alternate_line_nl_no_nl",O_RDWR | O_CREAT, S_IRWXU);
        char *ptr;
        static char *test;

        while ((ptr = get_next_line(fd)))
        {
                printf("%s",ptr);
                free(ptr);
        }
        ptr = get_next_line(fd);
        printf("%s",ptr);
        //free(ptr);
        //printf("%s %s \n", func("hello world"), func(NULL));
        /*char *str ;

        str = ft_strdup("hello world");
        str = NULL;
        printf("%s \n", str);*/
}

