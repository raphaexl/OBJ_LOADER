/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ebatchas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 19:57:33 by ebatchas          #+#    #+#             */
/*   Updated: 2019/08/07 15:20:07 by ebatchas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <math.h>

typedef struct s_vec3
{
	float x, y, z;
}				t_vec3;

typedef struct s_vec2
{
	float x, y;
}				t_vec2;

typedef struct	s_mesh
{
	t_vector	vertices;
	t_vector	uvs;
	t_vector	normals;
	t_vector	v_indices;
	t_vector	uv_indices;
	t_vector	n_indices;
}				t_mesh;

void	ft_parse_obj_vector(t_vector *v, char *line)
{
	char		**tab;
	t_vec3		vec;
	int			i;

	i = 0;
	vec = (t_vec3){.0, 0.0, 0.0};
	if ((tab = ft_strsplit(line, ' ')) && ft_tab_len(tab) == 4)
	{
		vec.x = ft_atof(tab[1]);
		vec.y = ft_atof(tab[2]);
		vec.z = ft_atof(tab[3]);
	}
	ft_tab_free(tab);
	v->push_back(v, &vec);
}

void	ft_parse_obj_uv(t_vector *v, char *line)
{
	char		**tab;
	t_vec2		vec;
	int			i;

	i = 0;
	vec = (t_vec2){.0, 0.0};
	if ((tab = ft_strsplit(line, ' ')) && ft_tab_len(tab) == 3)
	{
		vec.x = ft_atof(tab[1]);
		vec.y = ft_atof(tab[2]);
	}
	ft_tab_free(tab);
	v->push_back(v, &vec);
}

void	ft_parse_obj_normal(t_vector *v, char *line)
{
	char		**tab;
	t_vec3		vec;
	int			i;

	i = 0;
	vec = (t_vec3){.0, 0.0, .0};
	if ((tab = ft_strsplit(line, ' ')) && ft_tab_len(tab) == 4)
	{
		vec.x = ft_atof(tab[1]);
		vec.y = ft_atof(tab[2]);
		vec.z = ft_atof(tab[3]);
	}
	ft_tab_free(tab);
	v->push_back(v, &vec);
}

void		ft_bizzare(t_mesh *mesh, char **tab)
{
	int index[3];

	index[0] = ft_atoi(tab[0]);
	index[1] = ft_atoi(tab[1]);
	index[2] = ft_atoi(tab[2]);
	ft_vector_push_back(&mesh->v_indices, &index[0]);
	ft_vector_push_back(&mesh->uv_indices, &index[1]);
	ft_vector_push_back(&mesh->n_indices, &index[2]);
}

void	ft_parse_obj_faces(t_mesh *mesh, char *line)
{
	char		**tab1;
	char		**tab;
	int			i;

	i = 0;
	if ((tab1 = ft_strsplit(line, ' ')) && ft_tab_len(tab1) == 4)
	{
		while (i < 3 && (tab = ft_strsplit(tab1[i + 1], '/')) && ft_tab_len(tab) == 3)
		{
			ft_bizzare(mesh, tab);
			ft_tab_free(tab);
			i = i + 1;
		}
	}
	ft_tab_free(tab1);
}

void	ft_make_mesh(t_mesh *mesh, t_vector *v, t_vector *uvs, t_vector *normals)
{
	int		i;
	int		size;

	i = -1;
	size = mesh->v_indices.size(&mesh->v_indices);
	while (++i < size)
		mesh->vertices.push_back(&mesh->vertices,
				(t_vec3 *)v->items[*(int *)mesh->v_indices.items[i] - 1]);
	size = mesh->uv_indices.size(&mesh->uv_indices);
	i = -1;
	while (++i < size)
		mesh->uvs.push_back(&mesh->uvs,
				(t_vec2 *)uvs->items[*(int *)mesh->uv_indices.items[i] - 1]);
	size = mesh->n_indices.size(&mesh->n_indices);
	i = -1;
	while (++i < size)
		mesh->normals.push_back(&mesh->normals,
				(t_vec3 *)normals->items[*(int *)mesh->n_indices.items[i] - 1]);
}

void	ft_print_mesh(t_mesh *mesh)
{
	ft_putendl("VERTICES");
	for (int i = 0; i < mesh->vertices.length; i++)
	printf("indice : %d x : %.2f y : %.2f z : %.2f\n", i, ((t_vec3 *)mesh->vertices.items[i])->x,
			((t_vec3 *)mesh->vertices.items[i])->y, ((t_vec3 *)mesh->vertices.items[i])->z);
	ft_putendl("UV");
	for (int i = 0; i < mesh->uvs.length; i++)
	printf("indice : %d x : %.2f y : %.2f\n", i, ((t_vec2 *)mesh->uvs.items[i])->x, ((t_vec2 *)mesh->uvs.items[i])->y);
	ft_putendl("NORMALS");
	for (int i = 0; i < mesh->normals.length; i++)
	printf("indice : %d x : %.2f y : %.2f z : %.2f\n", i, ((t_vec3 *)mesh->normals.items[i])->x,
			((t_vec3 *)mesh->normals.items[i])->y, ((t_vec3 *)mesh->normals.items[i])->z);
}

void	ft_mesh_init(t_mesh *mesh)
{
	ft_vector_init(&mesh->vertices, sizeof(t_vec3));
	ft_vector_init(&mesh->uvs, sizeof(t_vec2));
	ft_vector_init(&mesh->normals, sizeof(t_vec3));
	ft_vector_init(&mesh->v_indices, sizeof(int));
	ft_vector_init(&mesh->uv_indices, sizeof(int));
	ft_vector_init(&mesh->n_indices, sizeof(int));
}

void	ft_mesh_clean(t_mesh *mesh)
{
	ft_vector_free(&mesh->vertices);
	ft_vector_free(&mesh->uvs);
	ft_vector_free(&mesh->normals);
	ft_vector_free(&mesh->v_indices);
	ft_vector_free(&mesh->uv_indices);
	ft_vector_free(&mesh->n_indices);
}

int		ft_load_obj_file(t_mesh *mesh, const char *file_name)
{
	int			fd;
	char		*line;
	t_vector	v_list;
	t_vector	uv_list;
	t_vector	n_list;

	fd = open(file_name, O_RDONLY);
	if (fd < 0 || fd > 4096)
		return (-1);
	ft_vector_init(&v_list, sizeof(t_vec3));
	ft_vector_init(&uv_list, sizeof(t_vec2));
	ft_vector_init(&n_list, sizeof(t_vec3));
	while (ft_get_next_line(fd, &line) && line)
	{
		if (line[0] == 'v' && line[1] == ' ')
			ft_parse_obj_vector(&v_list, line);
		else if (line[0] == 'v' && line[1] == 't')
			ft_parse_obj_uv(&uv_list, line);
		else if (line[0] == 'v' && line[1] == 'n')
			ft_parse_obj_normal(&n_list, line);
		else if (line[0] == 'f' && line[1] == ' ')
			ft_parse_obj_faces(mesh, line);
		free(line);
	}
	ft_make_mesh(mesh, &v_list, &uv_list, &n_list);
	ft_vector_free(&v_list);
	ft_vector_free(&uv_list);
	ft_vector_free(&n_list);
	close(fd);
	return (0);
}

void	ft_parse_file(const char *file_name)
{
	t_mesh mesh;

	ft_memset(&mesh, 0, sizeof(t_mesh));
	ft_mesh_init(&mesh);
	ft_load_obj_file(&mesh, file_name);
	ft_print_mesh(&mesh);
	ft_mesh_clean(&mesh);
}

int		main(int argc , char *argv[])
{
	if (argc == 2)
		ft_parse_file(argv[argc - 1]);
	return (0);
}
