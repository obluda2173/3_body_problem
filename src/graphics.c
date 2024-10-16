/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   graphics.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 20:29:26 by erian             #+#    #+#             */
/*   Updated: 2024/10/16 22:33:00 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tbp.h"

static void draw_circle(SDL_Renderer *renderer, int centerX, int centerY, int radius)
{
    for (int w = 0; w < radius * 2; w++)
	{
        for (int h = 0; h < radius * 2; h++)
		{
            int dx = radius - w;
            int dy = radius - h;
            if ((dx * dx + dy * dy) <= (radius * radius))
                SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
        }
    }
}

// Change the size of the screen according to the bodies movement
static double get_max_position(t_vector *rA, t_vector *rB, t_vector *rC)
{
    double max_pos = 0.0;
    for (int i = 0; i < STEPS; ++i)
    {
        double distA = norm(rA[i]);
        double distB = norm(rB[i]);
        double distC = norm(rC[i]);
        if (distA > max_pos) max_pos = distA;
        if (distB > max_pos) max_pos = distB;
        if (distC > max_pos) max_pos = distC;
    }
    return max_pos;
}

// Convert simulation coordinates to screen coordinates
static int convert_to_screen(double val, double max_simulation_value, int screen_dimension)
{
    return (int)((val / max_simulation_value) * (screen_dimension / 2)) + (screen_dimension / 2);
}

void visualize(t_vector *rA, t_vector *rB, t_vector *rC)
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return;
    }

    // Create a window
    SDL_Window *window = SDL_CreateWindow("Three Body Problem", 
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL)
    {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_Quit();
        return;
    }

    // Create a renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL)
    {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    // Get the max simulation position to scale the coordinates
    double max_simulation_value = get_max_position(rA, rB, rC) + 0.05;

    // Simulation Loop
    SDL_Event e;
    int running = 1;
    int size = 7; // Size of the body (radius)
    int i = 1; // Start from the first step (after initial positions)
    
    while (running && i < STEPS)
    {
        // Handle events
        while (SDL_PollEvent(&e) != 0)
        {
            if (e.type == SDL_QUIT)
                running = 0;
        }

        // Clear the screen
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Draw bodies for this step
        int posX_A = convert_to_screen(rA[i].x, max_simulation_value, SCREEN_WIDTH);
        int posY_A = convert_to_screen(-rA[i].y, max_simulation_value, SCREEN_HEIGHT); // Inverted y-axis
        int posX_B = convert_to_screen(rB[i].x, max_simulation_value, SCREEN_WIDTH);
        int posY_B = convert_to_screen(-rB[i].y, max_simulation_value, SCREEN_HEIGHT); // Inverted y-axis
        int posX_C = convert_to_screen(rC[i].x, max_simulation_value, SCREEN_WIDTH);
        int posY_C = convert_to_screen(-rC[i].y, max_simulation_value, SCREEN_HEIGHT); // Inverted y-axis

        // Body A (Red Circle)
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red for body A
        draw_circle(renderer, posX_A, posY_A, size);

        // Body B (Green Circle)
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green for body B
        draw_circle(renderer, posX_B, posY_B, size);

        // Body C (Blue Circle)
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue for body C
        draw_circle(renderer, posX_C, posY_C, size);

        // Update the screen
        SDL_RenderPresent(renderer);

        i++;

        SDL_Delay(2);
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
