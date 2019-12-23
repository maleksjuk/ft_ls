/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 15:58:40 by obanshee          #+#    #+#             */
/*   Updated: 2019/12/23 18:58:33 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_LS_H
# define FT_LS_H

# include "../libftprintf/includes/ft_printf.h"
# include <unistd.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <dirent.h>
# include <errno.h>
# include <string.h>
# include <limits.h>
# include <time.h>
# include <pwd.h>
# include <grp.h>

typedef struct	s_options
{
	int		list;
	int		recursive;
	int		all;
	int		reverse;
	int		time_order;
	/*
	**	служебные переменные
	*/	
	char	illegal;
	char	**dir_array;
	int		flag;
	char	*cur_dir;
	int		tab_len[7];
}				t_options;

typedef struct	s_info
{
	char		*name;
	char		mode[11];
	char		type;
	char		*user;
	char		*group;
	int			nlink;
	intmax_t	size;
	char		*time_create;
	char		*time_modif;
	char		*time_active;
}				t_info;

/*
**	options.c
*/
void	init_options(t_options *options, int ac);
int		input_options(t_options *options, char *params);

/*
**	ft_ls.c
*/
int		final_ls(t_options *options);
int		reading(t_info *list, char *file, t_options *options);
int		printing(t_info *list, t_options *options, struct stat about);
int		processing(t_options *options, char *file);
int		ft_ls(t_options *options, int num);

/*
**	lib_ls.c
*/
void	sort_ascii(char **array, int num);
t_info	*set_info_list(t_info *list, int len);
void	sort_info_list(t_info *list, int len, t_options *options);
void	set_path(t_options *options, char *path, char *file);
void	set_null_tab_len(t_options *options);

/*
**	option_R.c
*/
int		recursive(t_options *options, char *file);

/*
**	option_l.c
*/
int		get_list_params(char *file, t_info *list, int i);
void	print_list(t_info *list, int i, t_options *options);

#endif