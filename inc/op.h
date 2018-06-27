/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   op.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 16:40:04 by cpaquet           #+#    #+#             */
/*   Updated: 2018/06/27 04:24:59 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OP_H
# define OP_H

# define IND_SIZE			2
# define REG_SIZE			4
# define DIR_SIZE			REG_SIZE

# define REG_CODE			1
# define DIR_CODE			2
# define IND_CODE			3

# define MAX_ARGS_NUMBER	24
# define MAX_PLAYERS		4
# define MEM_SIZE			(4*1024)
# define IDX_MOD			(MEM_SIZE / 8)
# define CHAMP_MAX_SIZE		(MEM_SIZE / 6)

# define COMMENT_CHAR		'#'
# define LABEL_CHAR			':'
# define DIRECT_CHAR		'%'
# define SEPARATOR_CHAR		','
# define ENDL_COMMENT_CHAR	';'
# define COMMENT_STR2		";"
# define COMMENT_STR		"#"

# define LABEL_CHARS		"abcdefghijklmnopqrstuvwxyz_0123456789"

# define NAME_CMD_STRING	".name"
# define COMMENT_CMD_STRING	".comment"

# define REG_NUMBER			16

# define CYCLE_TO_DIE		1536
# define CYCLE_DELTA		1000
# define NBR_LIVE			21
# define MAX_CHECKS			10
# define OP_NBR				16

typedef char		t_arg_type;

# define T_REG				1
# define T_DIR				2
# define T_IND				4
# define T_LAB				8

# define PROG_NAME_LENGTH	(128)
# define COMMENT_LENGTH		(2048)
# define MAGIC_LENGTH		4
# define SIZE_LENGTH		4
# define HEADER_INTERME		(MAGIC_LENGTH + PROG_NAME_LENGTH)
# define HEADER_MAX_SIZE	(HEADER_INTERME + SIZE_LENGTH + COMMENT_LENGTH)
# define COR_MAX_SIZE		(HEADER_MAX_SIZE + CHAMP_MAX_SIZE)
# define COREWAR_EXEC_MAGIC	0xea83f3

typedef struct		s_header
{
	unsigned int	magic;
	char			prog_name[PROG_NAME_LENGTH + 1];
	unsigned int	prog_size;
	char			comment[COMMENT_LENGTH + 1];
}					t_header;

typedef struct		s_op
{
	char			*name;
	int				nb_params;
	char			param_type[MAX_ARGS_NUMBER];
	int				opcode;
	int				nb_cycle;
	char			*description;
	int				o_cod;
	int				dir_addr;
}					t_op;

extern t_op			g_op_tab[OP_NBR + 1];

#endif
