/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flevesqu <flevesqu@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/11/23 19:14:38 by flevesqu          #+#    #+#             */
/*   Updated: 2017/08/27 10:58:47 by flevesqu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_H
# define LIBFT_H
# include <string.h>
# include "get_next_line.h"
# include "libftprintf.h"
# include "ft_string.h"

typedef unsigned long long	t_ulong;
typedef unsigned char		t_uchar;

# ifndef ELECTRIC_MEMORY
#  define FAST_STRLEN
# endif

# ifdef DEBUGTTY

int	g_debug_fd;

#  define DEBUG_INIT()	g_debug_fd = open(DEBUGTTY, O_WRONLY)
#  define DEBUG(...)	dprintf(g_debug_fd, __VA_ARGS__)

# else

#  define DEBUG_INIT()
#  define DEBUG(...)

# endif

# define O1	0x00000000000000FFUL
# define O2	0x000000000000FF00UL
# define O3	0x0000000000FF0000UL
# define O4	0x00000000FF000000UL
# define O5	0x000000FF00000000UL
# define O6	0x0000FF0000000000UL
# define O7	0x00FF000000000000UL
# define O8	0xFF00000000000000UL

# define HIGH_BITS	0x8080808080808080UL
# define LOW_BITS	0x0101010101010101UL

# define DUPC(c)				(LOW_BITS * (t_uchar)(c))
# define LONGCHR_NULL(l)		(((l) - LOW_BITS) & ~(l) & HIGH_BITS)

# define OFFLEFT1(c)	((t_ulong)(c))
# define OFFLEFT2(c)	((t_ulong)(c) << 8)
# define OFFLEFT3(c)	((t_ulong)(c) << 16)
# define OFFLEFT4(c)	((t_ulong)(c) << 24)
# define OFFLEFT5(c)	((t_ulong)(c) << 32)
# define OFFLEFT6(c)	((t_ulong)(c) << 40)
# define OFFLEFT7(c)	((t_ulong)(c) << 48)
# define OFFLEFT8(c)	((t_ulong)(c) << 56)

# define OFFRGHT1(c)	((t_ulong)(c))
# define OFFRGHT2(c)	((t_ulong)(c) >> 8)
# define OFFRGHT3(c)	((t_ulong)(c) >> 16)
# define OFFRGHT4(c)	((t_ulong)(c) >> 24)
# define OFFRGHT5(c)	((t_ulong)(c) >> 32)
# define OFFRGHT6(c)	((t_ulong)(c) >> 40)
# define OFFRGHT7(c)	((t_ulong)(c) >> 48)
# define OFFRGHT8(c)	((t_ulong)(c) >> 56)

# define _CLEAR_FLAG(f, a)		(f) = ((f) & (~(a)))

# define _REPLACE_FLAG(f, a, b)	(f) = (((f) & (~(a))) | (b))

# define _ADD_FLAG(f, a)		(f) |= (a)

typedef struct	s_dlist
{
	void			*content;
	size_t			content_size;
	struct s_dlist	*next;
}				t_dlist;

typedef struct	s_blist
{
	void			*data;
	struct s_blist	*prev;
	struct s_blist	*next;
}				t_blist;

typedef struct	s_list
{
	void			*data;
	struct s_list	*next;
}				t_list;

typedef struct	s_heuristic
{
	int		heuristic;
	void	*data;
}				t_heuristic;

void			*ft_memset(void *b, int c, size_t len);
void			*ft_memalloc(size_t size);
void			ft_memdel(void **ap);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_memccpy(void *dst, const void *src, int c, size_t n);
void			*ft_memmove(void *dst, const void *src, size_t len);
void			*ft_memchr(const void *s, int c, size_t n);
void			*ft_memrchr(const void *s, int c, size_t n);
int				ft_memcmp(const void *s1, const void *s2, size_t n);
void			ft_bzero(void *s, size_t n);

int				ft_putc(int c);
void			ft_putchar(int c);
void			ft_putstr(const char *s);
void			ft_putendl(const char *s);
void			ft_putnbr(int n);
void			ft_putchar_fd(int c, int fd);
void			ft_putstr_fd(const char *s, int fd);
void			ft_putendl_fd(const char *s, int fd);
void			ft_putnbr_fd(int n, int fd);

size_t			ft_strlen(const char *str);
char			*ft_strnew(size_t size);
void			ft_strdel(char **as);
void			ft_striter(char *s, void (*f)(char *));
char			*ft_strdup(const char *s1);
char			*ft_strcpy(char *dst, const char *src);
char			*ft_strncpy(char *dst, const char *src, size_t n);
char			*ft_strcat(char *s1, const char *s2);
char			*ft_strncat(char *s1, const char *s2, size_t n);
size_t			ft_strlcat(char *dst, const char *src, size_t size);
char			*ft_strchr(const char *s, int c);
char			*ft_strrchr(const char *s, int c);
char			*ft_strstr(const char *s1, const char *s2);
char			*ft_strnstr(const char *s1, const char *s2, size_t n);
int				ft_strncmp(const char *s1, const char *s2, size_t n);
int				ft_strcmp(const char *s1, const char *s2);
int				ft_strcmp_nocase(const char *s1, const char *s2);
void			ft_striter(char *s, void (*f)(char*));
void			ft_striteri(char *s, void (*f)(unsigned int, char*));
char			*ft_strmap(const char *s, char (*f)(char));
char			*ft_strmapi(const char *s, char (*f)(unsigned int, char));
int				ft_strequ(const char *s1, const char *s2);
int				ft_strnequ(const char *s1, const char *s2, size_t n);
char			*ft_strsub(const char *s, unsigned int start, size_t len);
char			*ft_strjoin(const char *s1, const char *s2);
char			*ft_strtrim(const char *s1);
char			**ft_strsplit(const char *s, char c);
char			*ft_strndup(const char *s1, size_t n);
char			*ft_strfjoin(char *s1, char *s2);
char			*ft_strsubc(char *s1, const char *s2, size_t *n);

int				ft_strncmp_nocase(const char *s1, const char *s2, size_t n);
char			*ft_ifstrrchr(char *s, int c);
int				ft_toupper(int c);
int				ft_tolower(int c);
t_dlist			*ft_dlstnew(const void *content, size_t content_size);
void			ft_dlstdelone(t_dlist **alst, void (*del)(void *, size_t));
void			ft_dlstdel(t_dlist **alst, void (*del)(void *, size_t));
void			ft_dlstadd(t_dlist **alst, t_dlist *n);
void			ft_dlstiter(t_dlist *lst, void (*f)(t_dlist *elem));
t_dlist			*ft_dlstmap(t_dlist *lst, t_dlist *(*f)(t_dlist *elem));
void			ft_dlstswap(t_dlist *lst1, t_dlist *lst2);
t_dlist			*ft_dlstlast(t_dlist **lst);
t_dlist			*ft_dlstgetn(t_dlist **lst, size_t n);
void			ft_dlstaddn(t_dlist **lst, size_t n, t_dlist *nw);
int				get_next_line(int fd, char **line);
int				ft_isspace(int c);
char			*ft_getenv(char **env, const char *toget);
char			**ft_splitwhitespaces(const char *s);
void			ft_free_2d(char **tab);
t_heuristic		ft_new_heuristic(void *data, int heuristic);

t_list			*ft_lstpushnew(t_list **first, void *data);
t_list			*ft_lstnew(void *data);
void			ft_lstfree(t_list **lst);

t_blist			*ft_blstpushnew(t_blist **first, void *data);
t_blist			*ft_blstnew(void *data);

size_t			ft_ilen(int i);
size_t			ft_ilen_base(int i, int base);
size_t			ft_ulen(unsigned int i);
size_t			ft_ulen_base(unsigned int i, int base);

char			*ft_itoa(int n);
char			*ft_itoa_base(int n, int base);
char			*ft_utoabuf(unsigned int nb, char *buf);
char			*ft_utoabuf_base(unsigned int nb, char *buf, int base);

int				ft_atoi(const char *s1);
int				ft_atoi_base(const char *s1, int base);
unsigned int	ft_atou_base(const char *str, int base);

int				ft_isalpha(int c);
int				ft_isdigit(int c);
int				ft_isdigitbase(int c, int base);
int				ft_isalnum(int c);
int				ft_isascii(int c);
int				ft_isprint(int c);
int				ft_isupper(int c);
int				ft_islower(int c);
int				ft_isstrspaces(const char *str);

char			*ft_strnewc(size_t size, char c);

#endif
