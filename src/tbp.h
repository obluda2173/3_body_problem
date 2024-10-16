/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tbp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:22:40 by erian             #+#    #+#             */
/*   Updated: 2024/10/16 18:59:33 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TBP_H
# define TBP_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include "/opt/homebrew/Cellar/sdl2/2.30.8/include/SDL2/SDL.h"
# include "/opt/homebrew/Cellar/sdl2/2.30.8/include/SDL2/SDL_render.h"

# define G				6.67430e-11	// Gravitational constant
# define TIME_STEP		0.001		// Time step for the simulation
# define STEPS			10000		// Number of steps in the simulation
# define Mass1			2e10		// Mass of body 1
# define Mass2			2e10		// Mass of body 2
# define Mass3			2e10		// Mass of body 3
# define SCREEN_WIDTH	1200
# define SCREEN_HEIGHT	800
# define SCALE_FACTOR	0.1

typedef struct	c_vector
{
	double x, y;
}				t_vector;

typedef struct	c_body
{
	double mass;
	t_vector position;
	t_vector velocity;
}				t_body;

#endif