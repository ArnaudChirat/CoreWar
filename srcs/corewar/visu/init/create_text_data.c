/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_text_data.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/26 22:50:36 by lbelda            #+#    #+#             */
/*   Updated: 2018/06/27 02:34:26 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "visu.h"

#define L_ALIGN 154.
#define R_ALIGN -124.
#define B_ALIGN -45.
#define U_ALIGN 45.
#define Z_LEFT -25.5
#define Z_RIGHT -15.5
#define Z_L -15.5
#define Z_R -22.5

#define PROC_OF 8.
#define LIVE_OF 16.
#define P_XOF -16.
#define L_XOF -16.

#define ROT -0.4

#define SCALE_BIG 8.
#define SCALE_MEDIUM 6.
#define SCALE_SMALL 4.

static void	create_pos_data(t_glfloat3 *pos)
{
	pos[TXT_CYC] = (t_glfloat3){6, -115, 0.0};
	pos[TXT_PL1] = (t_glfloat3){L_ALIGN, U_ALIGN, Z_LEFT};
	pos[TXT_PL2] = (t_glfloat3){R_ALIGN, U_ALIGN, Z_RIGHT};
	pos[TXT_PL3] = (t_glfloat3){L_ALIGN, B_ALIGN, Z_LEFT};
	pos[TXT_PL4] = (t_glfloat3){R_ALIGN, B_ALIGN, Z_RIGHT};
	pos[TXT_PL1_PROC] = (t_glfloat3){L_ALIGN, U_ALIGN - PROC_OF, Z_LEFT};
	pos[TXT_PL2_PROC] = (t_glfloat3){R_ALIGN, U_ALIGN - PROC_OF, Z_RIGHT};
	pos[TXT_PL3_PROC] = (t_glfloat3){L_ALIGN, B_ALIGN - PROC_OF, Z_LEFT};
	pos[TXT_PL4_PROC] = (t_glfloat3){R_ALIGN, B_ALIGN - PROC_OF, Z_RIGHT};
	pos[TXT_PL1_LIVE] = (t_glfloat3){L_ALIGN, U_ALIGN - LIVE_OF, Z_LEFT};
	pos[TXT_PL2_LIVE] = (t_glfloat3){R_ALIGN, U_ALIGN - LIVE_OF, Z_RIGHT};
	pos[TXT_PL3_LIVE] = (t_glfloat3){L_ALIGN, B_ALIGN - LIVE_OF, Z_LEFT};
	pos[TXT_PL4_LIVE] = (t_glfloat3){R_ALIGN, B_ALIGN - LIVE_OF, Z_RIGHT};
	pos[TXT_PL1_PN] = (t_glfloat3){L_ALIGN + P_XOF, U_ALIGN - PROC_OF, Z_L};
	pos[TXT_PL2_PN] = (t_glfloat3){R_ALIGN + P_XOF, U_ALIGN - PROC_OF, Z_R};
	pos[TXT_PL3_PN] = (t_glfloat3){L_ALIGN + P_XOF, B_ALIGN - PROC_OF, Z_L};
	pos[TXT_PL4_PN] = (t_glfloat3){R_ALIGN + P_XOF, B_ALIGN - PROC_OF, Z_R};
	pos[TXT_PL1_LN] = (t_glfloat3){L_ALIGN + L_XOF, U_ALIGN - LIVE_OF, Z_L};
	pos[TXT_PL2_LN] = (t_glfloat3){R_ALIGN + L_XOF, U_ALIGN - LIVE_OF, Z_R};
	pos[TXT_PL3_LN] = (t_glfloat3){L_ALIGN + L_XOF, B_ALIGN - LIVE_OF, Z_L};
	pos[TXT_PL4_LN] = (t_glfloat3){R_ALIGN + L_XOF, B_ALIGN - LIVE_OF, Z_R};
}

static void	create_rot_data(float *rot)
{
	int	i;

	i = TXT_PL1;
	rot[TXT_CYC] = 0.;
	while (i < TXT_MAX)
	{
		rot[i] = (i - TXT_PL1) % 2 ? ROT : -ROT;
		i++;
	}
}

static void	create_scale_data(float *scale)
{
	int	i;

	i = -1;
	i = TXT_PL1;
	scale[TXT_CYC] = SCALE_BIG;
	while (i <= TXT_PL4)
		scale[i++] = SCALE_MEDIUM;
	while (i < TXT_MAX)
		scale[i++] = SCALE_SMALL;
}

void		create_text_data(t_text_data *data)
{
	create_pos_data(data->pos);
	create_rot_data(data->rot);
	create_scale_data(data->scale);
}
