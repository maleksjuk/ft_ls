/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ls.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 15:58:40 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/06 19:44:00 by obanshee         ###   ########.fr       */
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
	char	**files_array;
	char	**dir_array;
	int		len_for_array[2];
	int		flag;
	int		flag_list;
	char	*cur_dir;
	int		tab_len[7];
	int		count;
}				t_options;

typedef struct	s_info
{
	char		*name;
	char		mode[12];
	char		type;
	char		*user;
	char		*group;
	int			nlink;
	intmax_t	size;
	char		*time_create;
	long		time_create_digit;
	char		*time_modif;
	long		time_modif_digit;
	char		*time_active;
	long		time_active_digit;
	intmax_t	total;
	intmax_t	total_no_all;
	char		*path_link;
	int			flag_link;
}				t_info;

/*
**	main.c
*/
int		error_message(char *str);

/*
**	options.c
*/
void	set_null_tab_len(t_options *options);
void	init_options(t_options *options, int ac);
int		input_options(t_options *options, char *params);

/*
**	ft_ls.c
*/
int		final_ls(t_options *options);
int		ft_ls(t_options *options);

int	processing_dir(t_options *options, t_info *list, char *file);
int	processing_files(t_options *options, t_info *list);
int	processing(t_options *options, char *file);

/*
**	reader.c
*/
int		reading(t_info *list, char *file, t_options *options);
int		reading_one_file(t_info *list, char name[1024], t_options *options, int i);

/*
**	printer.c
*/
int		printing(t_info *list, t_options *options, int len);
void	print_list(t_info *list, int i, t_options *options);

/*
**	lib_ls.c
*/
void	sort_ascii(char **array, int num);
t_info	*set_info_list(t_info *list, int len);
void	update_value_tab_len(t_options *options, t_info *list, int len);
void	sort_info_list(t_info *list, int len, t_options *options);
void	set_path(t_options *options, char *path, char *file);
void	update_path(t_options *options, char *path);

/*
**	option_R.c
*/
int		recursive(t_options *options, char *file);

/*
**	option_l.c
*/
int		get_list_params(char *file, t_info *list, int i);	// BAD WORKS

#endif