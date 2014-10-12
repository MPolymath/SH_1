/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mdiouf <mdiouf@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2014/04/14 09:16:53 by mdiouf            #+#    #+#             */
/*   Updated: 2014/10/12 19:48:04 by mdiouf           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <errno.h>

typedef struct	s_split
{
	int			nbr_words;
	int			nbr_chars;
	int			i;
	int			j;
	int			k;
	int			start;
	char		**split_c;
}				t_split;

int			ft_strlen(const char *string);
int			ft_multiplier(int n, int times);
int			ft_atoi(const char *str);
void		*ft_bzero(void *s, size_t n);
int			ft_isalnum(int c);
int			ft_isalpha(int c);
int			ft_isascii(int c);
int			ft_isdigit(int c);
int			ft_isprint(int c);
void		*ft_memmove(void *s1, const void *s2, size_t n);
void		*ft_memchr(const void *s, int c, size_t n);
int			ft_memcmp(const void *s1, const void *s2, size_t n);
void		*ft_memcpy(void *s1, const void *s2, size_t n);
void		*ft_memset(void *b, int c, size_t len);
int			ft_multiplier(int n, int times);
char		*ft_strcat(char *s1, const char *s2);
char		*ft_strchr(const char *s, int c);
int			ft_strcmp(const char *s1, const char *s2);
char		*ft_strcpy(char *s1, const char *s2);
char		*ft_strdup(const char *s1);
char		*ft_strncat(char *s1, const char *s2, size_t n);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*ft_strncpy(char *s1, const char *s2, size_t n);
char		*ft_strnstr(const char *s1, const char *s2, size_t n);
int			ft_comparestrings(const char *s1, const char *s2, int i);
char		*ft_strrchr(const char *s, int c);
char		*ft_strstr(const char *s1, const char *s2);
int			ft_tolower(int c);
int			ft_toupper(int c);
char		*ft_itoa(int nbr);
void		ft_putchar(char c);
void		ft_putchar_fd(char c, int fd);
void		ft_putendl(char const *s);
void		ft_putendl_fd(char const *s, int fd);
void		ft_putnbr(int nbr);
void		ft_putnbr_fd(int nbr, int fd);
void		ft_putstr(char const *s);
void		ft_putstr_fd(char const *s, int fd);
int			ft_comparestrings(const char *s1, const char *s2, int i);
void		*ft_memccpy(void *s1, const void *s2, int c, size_t n);
void		*ft_memalloc(size_t size);
void		ft_memdel(void **ap);
char		*ft_strnew(size_t size);
void		ft_strdel(char **as);
void		ft_strclr(char *s);
void		ft_striter(char *s, void (*f)(char *));
void		ft_striteri(char *s, void (*f)(unsigned int, char *));
char		*ft_strmap(char const *s, char (*f) (char));
char		*ft_strmapi(char const *s, char (*f) (unsigned int, char));
int			ft_strequ(char const *s1, char const *s2);
int			ft_strnequ(char const *s1, char const *s2, size_t n);
char		*ft_strsub(char const *s, unsigned int start, size_t len);
char		*ft_strjoin(char const *s1, char const *s2);
int			ft_index_lastalnum(char const *s);
int			ft_index_firstalnum(char const *s);
char		*ft_begin_end_space_delete(char const *s);
char		*ft_strtrim(char const *s);
char		**ft_strsplit(char const *s, char c);
char		**ft_strsplit2(char const *s, char c);
size_t		ft_strlcat(char *dst, const char *src, size_t size);
int			ft_atoi2(int i, int length, int negative, char const *str);
#endif
