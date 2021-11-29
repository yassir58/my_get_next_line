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
        int fd = open("gnlTester/files/alternate_line_nl_no_nl",O_RDWR | O_CREAT, S_IRWXU);
        char *ptr;

        ptr = get_next_line(fd);
        printf("test 1 : %s \n",ptr);
       ptr = get_next_line(fd);
        printf("test 2 : %s\n",ptr);
         ptr = get_next_line(fd);
        printf("test 3 : %s\n",ptr);
        ptr = get_next_line(fd);
        printf("test 4 : %s\n",ptr);
         ptr = get_next_line(fd);
        printf("test 5 : %s\n",ptr);
        ptr = get_next_line(fd);
        printf("test 6 : %s\n",ptr);
         ptr = get_next_line(fd);
        printf("test 7 : %s\n",ptr);
        ptr = get_next_line(fd);
        printf("test 8 : %s\n",ptr);
         ptr = get_next_line(fd);
        printf("test 9 : %s\n",ptr);
        ptr = get_next_line(fd);
        printf("test 10 : %s\n",ptr);
       
       
        
}

