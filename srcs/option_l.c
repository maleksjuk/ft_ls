/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_l.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/18 18:59:24 by obanshee          #+#    #+#             */
/*   Updated: 2019/12/23 22:03:03 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

int		get_list_mode(t_info *list, int i, mode_t mode)
{
	list[i].mode[0] = S_ISDIR(mode) ? 'd' : (S_ISLNK(mode) ? 'l' : '-');
	list[i].mode[0] = S_ISCHR(mode) ? 'c' : (S_ISBLK(mode) ? 'b' : '-');
	list[i].mode[0] = S_ISFIFO(mode) ? 'p' : (S_ISSOCK(mode) ? 's' : '-');

	list[i].mode[10] = '\0';
	list[i].mode[1] = mode & S_IRUSR ? 'r' : '-';
	list[i].mode[2] = mode & S_IWUSR ? 'w' : '-';
	list[i].mode[3] = mode & S_IXUSR ? 'x' : '-';
	list[i].mode[4] = mode & S_IRGRP ? 'r' : '-';
	list[i].mode[5] = mode & S_IWGRP ? 'w' : '-';
	list[i].mode[6] = mode & S_IXGRP ? 'x' : '-';
	list[i].mode[7] = mode & S_IROTH ? 'r' : '-';
	list[i].mode[8] = mode & S_IWOTH ? 'w' : '-';
	list[i].mode[9] = mode & S_IXOTH ? 'x' : '-';
	return (0);
}

void	set_format_date(char *date)
{
	int		i;
	int		j;
	char	*current;
	long	cur_time;
	char	*year;

	i = -1;
	while (i++ < 6)
		date[i] = date[4 + i];
	cur_time = time(NULL);
	current = ft_strdup(ctime(&cur_time));
	year = ft_strdup(date);
	j = -1;
	while (++j < 4)
	{
		current[j] = current[20 + j];
		year[j] = year[20 + j];
	}
	current[j] = '\0';
	year[j] = '\0';
	j = 0;
	if (!ft_strcmp(current, year))
		while (j < 5)
			date[i++] = date[11 + j++];
	else
	{
		date[i++] = ' ';
		while (j < 4)
			date[i++] = date[20 + j++];
	}
	date[i] = '\0';
}

int		get_list_time(t_info *list, int i, struct stat about_file)
{
	list[i].time_active_digit = about_file.st_atimespec.tv_sec;
	list[i].time_modif_digit = about_file.st_mtimespec.tv_sec;
	list[i].time_create_digit = about_file.st_ctimespec.tv_sec;
	list[i].time_active = ft_strdup(ctime(&about_file.st_atimespec.tv_sec));
	list[i].time_modif = ft_strdup(ctime(&about_file.st_mtimespec.tv_sec));
	list[i].time_create = ft_strdup(ctime(&about_file.st_ctimespec.tv_sec));
	set_format_date(list[i].time_active);
	set_format_date(list[i].time_modif);
	set_format_date(list[i].time_create);
	return (0);
}

int		get_list_params(char *file, t_info *list, int i)
{
	struct stat		about_file;
	struct passwd	*uid;
	struct group	*gid;

	if (stat(file, &about_file))
	{
		perror("stat -l");
		return(1);
	}
	list[i].size = (intmax_t)about_file.st_size;
	list[i].nlink = (int)about_file.st_nlink;
	get_list_mode(list, i, about_file.st_mode);
	get_list_time(list, i, about_file);
	uid = getpwuid(about_file.st_uid);
	list[i].user = ft_strdup(uid->pw_name);
	gid = getgrgid(about_file.st_gid);
	list[i].group = ft_strdup(gid->gr_name);
	if (i == 0)
		list[0].total = 0;
	else if (i > 1)
		list[0].total = list[0].total + (intmax_t)about_file.st_blocks;
	return (0);
}

void	print_list(t_info *list, int i, t_options *options)
{
	ft_printf("%s %*i %*s %*s %*d %*s %s\n",
		list[i].mode, 
		options->tab_len[1], list[i].nlink,
		options->tab_len[2] - 1, list[i].user,
		options->tab_len[3], list[i].group,
		options->tab_len[4], list[i].size,
		options->tab_len[5], list[i].time_modif,
		list[i].name);
}
