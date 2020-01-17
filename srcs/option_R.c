/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   option_R.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obanshee <obanshee@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/17 20:19:23 by obanshee          #+#    #+#             */
/*   Updated: 2020/01/17 05:41:26 by obanshee         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_ls.h"

char	**set_dir_array(char **array, int len)
{
	int	i;

	i = 0;
	if (!(array = (char **)malloc(sizeof(char *) * (len + 1))))
		return (NULL);
	array[len] = NULL;
	return (array);
}

void	free_array(char **array, int len)
{
	while (array[len])
		free(array[len--]);
	free(array);
}

int		glp_rev(char *file, t_info *list, int i)
{
	struct stat	about_file;

	if (stat(file, &about_file))
	{
		ft_printf("GLP_REV ");
		return (error_message(file, (errno == EACCES) ? 0 : FULL_EXIT));
	}
	list[i].time_active_digit = about_file.st_atimespec.tv_sec;
	list[i].time_modif_digit = about_file.st_mtimespec.tv_sec;
	list[i].time_create_digit = about_file.st_ctimespec.tv_sec;
	return (0);
}

void	set_path_rev(char *path, char *file)
{
	int	len;
	int	i;

	len = ft_strlen(path);
	if (len > 0 && path[len - 1] != '/')
	{
		path[len] = '/';
		len++;
	}
	i = 0;
	while (file[i])
	{
		path[len] = file[i];
		i++;
		len++;
	}
	path[len] = '\0';
}

void	update_path_rev(char *file, char *path)
{
	int	i;
	int	len;

	i = 0;
	while (i < MAX_PATH)
		file[i++] = '\0';
	len = ft_strlen(path);
	i = 0;
	while (i < len)
	{
		file[i] = path[i];
		i++;
	}
	file[i] = '\0';
}

t_info	*recursive_create_array(t_options *options, char *file)
{
	DIR				*dir;
	struct dirent	*dir_read;
	int				len;
	int				current;
	t_info			*list_rev;
	char			*path;

	len = 0;
	if (!(dir = opendir(file)))
		return (NULL);
	dir_read = readdir(dir);
	while (dir_read != NULL)
	{
		if (dir_read->d_name[0] != '.' || (options->all &&
			(dir_read->d_name[0] == '.' && dir_read->d_name[1] != '.' &&
			dir_read->d_name[1] != '\0')))
			if (dir_read->d_type == 4)
				len++;
		dir_read = readdir(dir);
	}
	if (closedir(dir) == -1)
		return (NULL);

	current = 0;
	path = ft_strnew(MAX_PATH);
	list_rev = NULL;
	list_rev = set_info_list(len);
	if (!(dir = opendir(file)))
		return (NULL);
	dir_read = readdir(dir);
	while (dir_read != NULL)
	{
		if (dir_read->d_name[0] != '.' || (options->all &&
			(dir_read->d_name[0] == '.' && dir_read->d_name[1] != '.' &&
			dir_read->d_name[1] != '\0')))
			if (dir_read->d_type == 4)
			{
				list_rev[current].name = ft_strdup(dir_read->d_name);
				update_path_rev(path, file);
				set_path_rev(path, dir_read->d_name);
				glp_rev(path, list_rev, current);
				current++;
			}
		dir_read = readdir(dir);
	}
	if (closedir(dir) == -1)
		return (NULL);
	sort_info_list(list_rev, len, options);
	list_rev[0].size = len;
	return (list_rev);
}

void	bug_ls_for_recursion(t_options *options)
{
	int	i;

	i = 0;
	ft_printf("\n%s/", options->dir_array[options->bug_ls_for_recursion]);
	while (options->cur_dir[i] != '/')
		i++;
	i++;
	ft_printf("%s:\n", options->cur_dir + i);
}

int		recursive(t_options *options, char *file)
{
	char			*file_for_r;
	t_info			*list_rev;
	int				i;

	list_rev = recursive_create_array(options, file);
	if (list_rev == NULL)
		return (error_message(file, 0));
	i = 0;
	while (i < list_rev[0].size)
	{
		update_path(options, file);
		set_path(options, list_rev[i].name);
		bug_ls_for_recursion(options);
		file_for_r = ft_strdup(options->cur_dir);
		options->count = 0;
		processing(options, file_for_r);
		free(file_for_r);
		i++;
	}
	return (0);
}
