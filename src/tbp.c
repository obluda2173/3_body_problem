/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tbp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:37:03 by erian             #+#    #+#             */
/*   Updated: 2024/10/16 22:35:43 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tbp.h"

int main(void)
{
    t_vector    *rA = (t_vector*)malloc(STEPS * sizeof(t_vector));
    t_vector    *rB = (t_vector*)malloc(STEPS * sizeof(t_vector));
    t_vector    *rC = (t_vector*)malloc(STEPS * sizeof(t_vector));

    t_vector    *vA = (t_vector*)malloc(STEPS * sizeof(t_vector));
    t_vector    *vB = (t_vector*)malloc(STEPS * sizeof(t_vector));
    t_vector    *vC = (t_vector*)malloc(STEPS * sizeof(t_vector));

    // Initialize positions and velocities

    // Option 1: Chaotic
    // rA[0] = (t_vector){1.0, 0.0};
    // rB[0] = (t_vector){-0.5, sqrt(3.0) / 2.0};
    // rC[0] = (t_vector){-0.5, -sqrt(3.0) / 2.0};

    // vA[0] = (t_vector){0.0, sqrt(3.0) / 2.0};
    // vB[0] = (t_vector){-sqrt(3.0) / 4.0, -0.25};
    // vC[0] = (t_vector){sqrt(3.0) / 4.0, -0.25}; 

    // Option 2: Chaotic
    // rA[0] = (t_vector){1.0, 0.0};
    // rB[0] = (t_vector){-0.5, 0.866};
    // rC[0] = (t_vector){-0.5, -0.866};

    // vA[0] = (t_vector){0.0, 0.5};
    // vB[0] = (t_vector){-0.433, -0.25};
    // vC[0] = (t_vector){0.433, -0.25};

    // Option 3: Hénon’s First Orbit (highly recommended)
    rA[0] = (t_vector){-1.0, 0.0};
    rB[0] = (t_vector){0.0, 0.0};
    rC[0] = (t_vector){1.0, 0.0};

    vA[0] = (t_vector){0.0, 0.5};
    vB[0] = (t_vector){0.0, 0.0};
    vC[0] = (t_vector){0.0, -0.5};

    FILE* file = fopen("tbp.csv", "w");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }

    run(rA, rB, rC, vA, vB, vC, file);

    fclose(file);

    visualize(rA, rB, rC);
    
    free(rA);
    free(rB);
    free(rC);
    free(vA);
    free(vB);
    free(vC);

    SDL_Quit();

    return 0;
}
