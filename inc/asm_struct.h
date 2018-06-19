/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   asm_struct.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpaquet <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/19 16:40:12 by cpaquet           #+#    #+#             */
/*   Updated: 2018/06/19 16:40:13 by cpaquet          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ASM_STRUCT_H
# define ASM_STRUCT_H

# define NAME_CMD_TYPE 			16
# define COMMENT_CMD_TYPE 		17
# define QUOTE_TYPE 			18
# define SEPARATOR_TYPE 		19
# define COMMENT_TYPE 			20
# define LABEL_SEP_TYPE 		21
# define DIRECT_ARG_TYPE 		22
# define INDIRECT_ARG_TYPE 		23
# define REGISTRE_TYPE 			24
# define NEW_LINE_TYPE 			25
# define LABEL_TYPE 			26
# define NAME_TYPE 				27
# define COMMENT_CHAR_TYPE 		28
# define SEPARATOR_CHAR_TYPE	29
# define DIRECT_CHAR_TYPE 		30
# define LABEL_CHAR_TYPE 		31
# define ENDL_COM_TYPE 			32

typedef struct					s_parse
{
	int							lig;
	int							col;
	char						*label;
	int							type;
	struct s_parse				*next;
}								t_parse;

typedef struct					s_label
{
	char						*label;
	int							index;
	int							len;
	int							state;
	struct s_label				*next;
}								t_label;

typedef struct					s_data
{
	char						state_header;
	char						occode;
	int							separator;
	int							opcode;
	int							arg;
	char						bytecode[CHAMP_MAX_SIZE];
	t_parse						*parse;
	t_header					header;
	int							len;
	t_label						*ind_label;
	t_label						*stor_label;
	int							opcode_index;
	int							nb_arg;
	int							in_comment;
	int							name_token;
	int							comment_token;
	int							comment;
	int							quotes;
}								t_data;

typedef struct					s_token
{
	char						*label;
	char						*type;
}								t_token;

#endif
