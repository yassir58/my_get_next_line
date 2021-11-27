#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include "fcntl.h"
/// for testing purpose
#include <stdio.h>
#include <string.h>



char *get_next_line(int);
size_t ft_strlen(char const *);
char *try_get_line(char *);
char *ft_substr(char const *s, unsigned int start, size_t len);
char *ft_strjoin(char *, char *);
char *ft_strdup(const char *);
char *ft_strchr(char *, char);
#endif
