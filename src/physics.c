/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   physics.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:28:56 by erian             #+#    #+#             */
/*   Updated: 2024/10/16 20:57:21 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tbp.h"

double norm(t_vector a)
{
    return sqrt(a.x * a.x + a.y * a.y);
}

// Vector subtraction
static t_vector vector_subtract(t_vector a, t_vector b)
{
    t_vector result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    return result;
}

// Vector addition
static t_vector vector_add(t_vector a, t_vector b)
{
    t_vector result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}

// Vector scaling
static t_vector vector_scale(t_vector a, double scalar)
{
    t_vector result;
    result.x = a.x * scalar;
    result.y = a.y * scalar;
    return result;
}

static t_vector body_func(t_vector r1, t_vector r2, t_vector r3, double mass2, double mass3)
{
    t_vector dr_dt;
    t_vector r1_r3 = vector_subtract(r1, r3);
    t_vector r1_r2 = vector_subtract(r1, r2);

    double epsilon = 1e-5;
    double mag_r1_r2 = norm(r1_r2) + epsilon;
    double mag_r1_r3 = norm(r1_r3) + epsilon;
    
    dr_dt = vector_scale(r1_r2, -G * mass2 / pow(mag_r1_r2, 3));
    dr_dt = vector_add(dr_dt, vector_scale(r1_r3, -G * mass3 / pow(mag_r1_r3, 3)));
    
    return dr_dt;
}

void run(t_vector *rA, t_vector *rB, t_vector *rC, t_vector *vA, t_vector *vB, t_vector *vC, FILE *file)
{
    for (int i = 1; i < STEPS; ++i)
	{
        // K_1
        t_vector k_1_A = vA[i - 1];
        t_vector k_1_B = vB[i - 1];
        t_vector k_1_C = vC[i - 1];
        t_vector k_1_A_v = body_func(rA[i - 1], rB[i - 1], rC[i - 1], Mass2, Mass3);
        t_vector k_1_B_v = body_func(rB[i - 1], rC[i - 1], rA[i - 1], Mass3, Mass1);
        t_vector k_1_C_v = body_func(rC[i - 1], rA[i - 1], rB[i - 1], Mass1, Mass2);
        
        // K_2
        t_vector k_2_A = vector_add(vA[i - 1], vector_scale(k_1_A_v, TIME_STEP / 2));
        t_vector k_2_B = vector_add(vB[i - 1], vector_scale(k_1_B_v, TIME_STEP / 2));
        t_vector k_2_C = vector_add(vC[i - 1], vector_scale(k_1_C_v, TIME_STEP / 2));
        
        t_vector k_2_A_v = body_func(vector_add(rA[i - 1], vector_scale(k_1_A, TIME_STEP / 2)), 
                                    vector_add(rB[i - 1], vector_scale(k_1_B, TIME_STEP / 2)), 
                                    vector_add(rC[i - 1], vector_scale(k_1_C, TIME_STEP / 2)), 
                                    Mass2, Mass3);
		t_vector k_2_B_v = body_func(vector_add(rB[i - 1], vector_scale(k_1_B, TIME_STEP / 2)),
                                    vector_add(rC[i - 1], vector_scale(k_1_C, TIME_STEP / 2)),
                                    vector_add(rA[i - 1], vector_scale(k_1_A, TIME_STEP / 2)),
                                    Mass3, Mass1);
        t_vector k_2_C_v = body_func(vector_add(rC[i - 1], vector_scale(k_1_C, TIME_STEP / 2)),
                                    vector_add(rA[i - 1], vector_scale(k_1_A, TIME_STEP / 2)),
                                    vector_add(rB[i - 1], vector_scale(k_1_B, TIME_STEP / 2)),
                                    Mass1, Mass2);
        
        // K_3
        t_vector k_3_A = vector_add(vA[i - 1], vector_scale(k_2_A_v, TIME_STEP / 2));
        t_vector k_3_B = vector_add(vB[i - 1], vector_scale(k_2_B_v, TIME_STEP / 2));
        t_vector k_3_C = vector_add(vC[i - 1], vector_scale(k_2_C_v, TIME_STEP / 2));
        
        t_vector k_3_A_v = body_func(vector_add(rA[i - 1], vector_scale(k_2_A, TIME_STEP / 2)), 
                                    vector_add(rB[i - 1], vector_scale(k_2_B, TIME_STEP / 2)), 
                                    vector_add(rC[i - 1], vector_scale(k_2_C, TIME_STEP / 2)), 
                                    Mass2, Mass3);
		t_vector k_3_B_v = body_func(vector_add(rB[i - 1], vector_scale(k_2_B, TIME_STEP / 2)),
                                    vector_add(rC[i - 1], vector_scale(k_2_C, TIME_STEP / 2)),
                                    vector_add(rA[i - 1], vector_scale(k_2_A, TIME_STEP / 2)),
                                    Mass3, Mass1);
        t_vector k_3_C_v = body_func(vector_add(rC[i - 1], vector_scale(k_2_C, TIME_STEP / 2)),
                                    vector_add(rA[i - 1], vector_scale(k_2_A, TIME_STEP / 2)),
                                    vector_add(rB[i - 1], vector_scale(k_2_B, TIME_STEP / 2)),
                                    Mass1, Mass2);

        // K_4
        t_vector k_4_A = vector_add(vA[i - 1], vector_scale(k_3_A_v, TIME_STEP));
        t_vector k_4_B = vector_add(vB[i - 1], vector_scale(k_3_B_v, TIME_STEP));
        t_vector k_4_C = vector_add(vC[i - 1], vector_scale(k_3_C_v, TIME_STEP));
        
        t_vector k_4_A_v = body_func(vector_add(rA[i - 1], vector_scale(k_3_A, TIME_STEP)), 
                                    vector_add(rB[i - 1], vector_scale(k_3_B, TIME_STEP)), 
                                    vector_add(rC[i - 1], vector_scale(k_3_C, TIME_STEP)), 
                                    Mass2, Mass3);
		t_vector k_4_B_v = body_func(vector_add(rB[i - 1], vector_scale(k_3_B, TIME_STEP)),
                                    vector_add(rC[i - 1], vector_scale(k_3_C, TIME_STEP)),
                                    vector_add(rA[i - 1], vector_scale(k_3_A, TIME_STEP)),
                                    Mass3, Mass1);
        t_vector k_4_C_v = body_func(vector_add(rC[i - 1], vector_scale(k_3_C, TIME_STEP)),
                                    vector_add(rA[i - 1], vector_scale(k_3_A, TIME_STEP)),
                                    vector_add(rB[i - 1], vector_scale(k_3_B, TIME_STEP)),
                                    Mass1, Mass2);
        
        // Update positions
		rA[i] = vector_add(rA[i - 1], vector_scale(vector_add(vector_add(k_1_A, vector_scale(vector_add(k_2_A, k_3_A), 2)), k_4_A), TIME_STEP / 6));
        rB[i] = vector_add(rB[i - 1], vector_scale(vector_add(vector_add(k_1_B, vector_scale(vector_add(k_2_B, k_3_B), 2)), k_4_B), TIME_STEP / 6));
        rC[i] = vector_add(rC[i - 1], vector_scale(vector_add(vector_add(k_1_C, vector_scale(vector_add(k_2_C, k_3_C), 2)), k_4_C), TIME_STEP / 6));

        // Update velocities
        vA[i] = vector_add(vA[i - 1], vector_scale(vector_add(vector_add(k_1_A_v, vector_scale(vector_add(k_2_A_v, k_3_A_v), 2)), k_4_A_v), TIME_STEP / 6));
        vB[i] = vector_add(vB[i - 1], vector_scale(vector_add(vector_add(k_1_B_v, vector_scale(vector_add(k_2_B_v, k_3_B_v), 2)), k_4_B_v), TIME_STEP / 6));
        vC[i] = vector_add(vC[i - 1], vector_scale(vector_add(vector_add(k_1_C_v, vector_scale(vector_add(k_2_C_v, k_3_C_v), 2)), k_4_C_v), TIME_STEP / 6));
        
        fprintf(file, "%d, %lf, %lf, %lf, %lf, %lf, %lf\n", i, rA[i].x, rA[i].y, rB[i].x, rB[i].y, rC[i].x, rC[i].y);
    }
}
