/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tbp.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 10:37:03 by erian             #+#    #+#             */
/*   Updated: 2024/10/16 19:09:41 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tbp.h"

double norm(t_vector a)
{
    return sqrt(a.x * a.x + a.y * a.y);
}

// Vector subtraction
t_vector vector_subtract(t_vector a, t_vector b)
{
    t_vector result;
    result.x = a.x - b.x;
    result.y = a.y - b.y;
    return result;
}

// Vector addition
t_vector vector_add(t_vector a, t_vector b)
{
    t_vector result;
    result.x = a.x + b.x;
    result.y = a.y + b.y;
    return result;
}

// Vector scaling
t_vector vector_scale(t_vector a, double scalar)
{
    t_vector result;
    result.x = a.x * scalar;
    result.y = a.y * scalar;
    return result;
}

t_vector bodyFunc(t_vector r1, t_vector r2, t_vector r3, double mass2, double mass3)
{
    t_vector dr_dt;
    double epsilon = 1e-5;

    t_vector r1_r2 = vector_subtract(r1, r2);
    t_vector r1_r3 = vector_subtract(r1, r3);
    
    double mag_r1_r2 = norm(r1_r2) + epsilon;
    double mag_r1_r3 = norm(r1_r3) + epsilon;
    
    dr_dt = vector_scale(r1_r2, -G * mass2 / pow(mag_r1_r2, 3));
    dr_dt = vector_add(dr_dt, vector_scale(r1_r3, -G * mass3 / pow(mag_r1_r3, 3)));
    
    return dr_dt;
}

void Run(t_vector *rA, t_vector *rB, t_vector *rC, t_vector *vA, t_vector *vB, t_vector *vC, FILE *file)
{
    for (int i = 1; i < STEPS; ++i)
	{
        // K_1
        t_vector k_1_A = vA[i - 1];
        t_vector k_1_B = vB[i - 1];
        t_vector k_1_C = vC[i - 1];
        t_vector k_1_A_v = bodyFunc(rA[i - 1], rB[i - 1], rC[i - 1], Mass2, Mass3);
        t_vector k_1_B_v = bodyFunc(rB[i - 1], rC[i - 1], rA[i - 1], Mass3, Mass1);
        t_vector k_1_C_v = bodyFunc(rC[i - 1], rA[i - 1], rB[i - 1], Mass1, Mass2);
        
        // K_2
        t_vector k_2_A = vector_add(vA[i - 1], vector_scale(k_1_A_v, TIME_STEP / 2));
        t_vector k_2_B = vector_add(vB[i - 1], vector_scale(k_1_B_v, TIME_STEP / 2));
        t_vector k_2_C = vector_add(vC[i - 1], vector_scale(k_1_C_v, TIME_STEP / 2));
        
        t_vector k_2_A_v = bodyFunc(vector_add(rA[i - 1], vector_scale(k_1_A, TIME_STEP / 2)), 
                                    vector_add(rB[i - 1], vector_scale(k_1_B, TIME_STEP / 2)), 
                                    vector_add(rC[i - 1], vector_scale(k_1_C, TIME_STEP / 2)), 
                                    Mass2, Mass3);
		t_vector k_2_B_v = bodyFunc(vector_add(rB[i - 1], vector_scale(k_1_B, TIME_STEP / 2)),
                                    vector_add(rC[i - 1], vector_scale(k_1_C, TIME_STEP / 2)),
                                    vector_add(rA[i - 1], vector_scale(k_1_A, TIME_STEP / 2)),
                                    Mass3, Mass1);
        t_vector k_2_C_v = bodyFunc(vector_add(rC[i - 1], vector_scale(k_1_C, TIME_STEP / 2)),
                                    vector_add(rA[i - 1], vector_scale(k_1_A, TIME_STEP / 2)),
                                    vector_add(rB[i - 1], vector_scale(k_1_B, TIME_STEP / 2)),
                                    Mass1, Mass2);
        
        // K_3
        t_vector k_3_A = vector_add(vA[i - 1], vector_scale(k_2_A_v, TIME_STEP / 2));
        t_vector k_3_B = vector_add(vB[i - 1], vector_scale(k_2_B_v, TIME_STEP / 2));
        t_vector k_3_C = vector_add(vC[i - 1], vector_scale(k_2_C_v, TIME_STEP / 2));
        
        t_vector k_3_A_v = bodyFunc(vector_add(rA[i - 1], vector_scale(k_2_A, TIME_STEP / 2)), 
                                    vector_add(rB[i - 1], vector_scale(k_2_B, TIME_STEP / 2)), 
                                    vector_add(rC[i - 1], vector_scale(k_2_C, TIME_STEP / 2)), 
                                    Mass2, Mass3);
		t_vector k_3_B_v = bodyFunc(vector_add(rB[i - 1], vector_scale(k_2_B, TIME_STEP / 2)),
                                    vector_add(rC[i - 1], vector_scale(k_2_C, TIME_STEP / 2)),
                                    vector_add(rA[i - 1], vector_scale(k_2_A, TIME_STEP / 2)),
                                    Mass3, Mass1);
        t_vector k_3_C_v = bodyFunc(vector_add(rC[i - 1], vector_scale(k_2_C, TIME_STEP / 2)),
                                    vector_add(rA[i - 1], vector_scale(k_2_A, TIME_STEP / 2)),
                                    vector_add(rB[i - 1], vector_scale(k_2_B, TIME_STEP / 2)),
                                    Mass1, Mass2);

        // K_4
        t_vector k_4_A = vector_add(vA[i - 1], vector_scale(k_3_A_v, TIME_STEP));
        t_vector k_4_B = vector_add(vB[i - 1], vector_scale(k_3_B_v, TIME_STEP));
        t_vector k_4_C = vector_add(vC[i - 1], vector_scale(k_3_C_v, TIME_STEP));
        
        t_vector k_4_A_v = bodyFunc(vector_add(rA[i - 1], vector_scale(k_3_A, TIME_STEP)), 
                                    vector_add(rB[i - 1], vector_scale(k_3_B, TIME_STEP)), 
                                    vector_add(rC[i - 1], vector_scale(k_3_C, TIME_STEP)), 
                                    Mass2, Mass3);
		t_vector k_4_B_v = bodyFunc(vector_add(rB[i - 1], vector_scale(k_3_B, TIME_STEP)),
                                    vector_add(rC[i - 1], vector_scale(k_3_C, TIME_STEP)),
                                    vector_add(rA[i - 1], vector_scale(k_3_A, TIME_STEP)),
                                    Mass3, Mass1);
        t_vector k_4_C_v = bodyFunc(vector_add(rC[i - 1], vector_scale(k_3_C, TIME_STEP)),
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

void drawCircle(SDL_Renderer *renderer, int centerX, int centerY, int radius)
{
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w;
            int dy = radius - h;
            if ((dx * dx + dy * dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, centerX + dx, centerY + dy);
            }
        }
    }
}

// Adjusted to dynamically scale the positions to the screen
double get_max_position(t_vector *rA, t_vector *rB, t_vector *rC)
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
int convert_to_screen(double val, double max_simulation_value, int screen_dimension)
{
    return (int)((val / max_simulation_value) * (screen_dimension / 2)) + (screen_dimension / 2);
}

void visualize(t_vector *rA, t_vector *rB, t_vector *rC)
{
    // Initialize SDL
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
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return;
    }

    // Get the max simulation position to scale the coordinates
    double max_simulation_value = get_max_position(rA, rB, rC);
    printf("%f\n", max_simulation_value);

    // Simulation Loop
    SDL_Event e;
    int running = 1;
    int size = 5; // Size of the body (radius for circles)
    int i = 1; // Start from the first step (after initial positions)
    
    while (running && i < STEPS) {
        // Handle events
        while (SDL_PollEvent(&e) != 0) {
            if (e.type == SDL_QUIT) {
                running = 0;
            }
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
        drawCircle(renderer, posX_A, posY_A, size);

        // Body B (Green Circle)
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green for body B
        drawCircle(renderer, posX_B, posY_B, size);

        // Body C (Blue Circle)
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255); // Blue for body C
        drawCircle(renderer, posX_C, posY_C, size);

        // Update the screen
        SDL_RenderPresent(renderer);

        // Progress to the next step
        i++;

        SDL_Delay(10); // Limit the frame rate
    }

    // Clean up
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main()
{
    // Simulation setup
    t_vector    *rA = (t_vector*)malloc(STEPS * sizeof(t_vector));
    t_vector    *rB = (t_vector*)malloc(STEPS * sizeof(t_vector));
    t_vector    *rC = (t_vector*)malloc(STEPS * sizeof(t_vector));

    t_vector    *vA = (t_vector*)malloc(STEPS * sizeof(t_vector));
    t_vector    *vB = (t_vector*)malloc(STEPS * sizeof(t_vector));
    t_vector    *vC = (t_vector*)malloc(STEPS * sizeof(t_vector));

    // Initialize positions and velocities
    // rA[0] = (t_vector){0.746156, 0.0};
    // rB[0] = (t_vector){-0.373078, 0.238313};
    // rC[0] = (t_vector){-0.373078, -0.238313};
    
    // vA[0] = (t_vector){0.0, 0.324677};
    // vB[0] = (t_vector){0.764226, -0.162339};
    // vC[0] = (t_vector){-0.764226, -0.162339};

    //good example
    // rA[0] = (t_vector){1.0, 0.0};
    // rB[0] = (t_vector){-0.5, 0.866};
    // rC[0] = (t_vector){-0.5, -0.866};

    // vA[0] = (t_vector){0.0, 0.5};
    // vB[0] = (t_vector){-0.433, -0.25};
    // vC[0] = (t_vector){0.433, -0.25};

    //very good example
    rA[0] = (t_vector){-0.97000436, 0.24308753};
    rB[0] = (t_vector){0.97000436, -0.24308753};
    rC[0] = (t_vector){0.0, 0.0};

    vA[0] = (t_vector){0.0, 0.5};
    vB[0] = (t_vector){0.0, -0.5};
    vC[0] = (t_vector){0.0, 0.0};
    

    FILE* file = fopen("tbp.csv", "w");
    if (file == NULL)
    {
        printf("Error opening file!\n");
        return 1;
    }

    // Run the full simulation and store all the steps in the arrays
    Run(rA, rB, rC, vA, vB, vC, file);

    fclose(file);

    // Visualization loop
    visualize(rA, rB, rC);
    
    // Free memory
    free(rA);
    free(rB);
    free(rC);
    free(vA);
    free(vB);
    free(vC);

    SDL_Quit();

    return 0;
}
