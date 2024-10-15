/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tbp.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:29:52 by erian             #+#    #+#             */
/*   Updated: 2024/10/15 19:12:25 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tbp.hpp"

int	main(void)
{
	GLFWwindow* window;

    // Initial positions of the three bodies
    Vector2d r1(0.746156, 0);
    Vector2d r2(-0.373078, 0.238313);
    Vector2d r3(-0.373078, -0.238313);

    // Initial velocities of the three bodies
    Vector2d v1(0, 0.324677);
    Vector2d v2(0.764226, -0.162339);
    Vector2d v3(-0.764226, -0.162339);

    // Initialize the circle objects (representing celestial bodies) for rendering
    CircleGL circle1(r1(0), r1(1), 0.025, 0.65, 0.01, 0.36);
    CircleGL circle2(r2(0), r2(1), 0.025, 0.95, 0.45, 0.012);
    CircleGL circle3(r3(0), r3(1), 0.025, 0.95, 0.020, 0.19);

	// Running RK4
	rk4_tbp main(1, 1, 1);
	
	//main.Run(time step, total number of steps, [initital positions], [initial velocities])
	vecArray2 finalVals = main.Run(0.0012, 10000, r1, r2, r3, v1, v2, v3);

	if (!glfwInit())
    	return -1;

	window = glfwCreateWindow(800, 800, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	// Make context current
	glfwMakeContextCurrent(window);

	float i = 0;

	while(!glfwWindowShouldClose(window))
	{
		glClear(GL_COLOR_BUFFER_BIT);

		circle1.draw(true);
		circle2.draw(true);
		circle3.draw(true);

		// Updating position according to RK4 results
		if (i < 10000) {
			circle1.move(finalVals[0][i][0], finalVals[0][i][1]);
			circle2.move(finalVals[1][i][0], finalVals[1][i][1]);
			circle3.move(finalVals[2][i][0], finalVals[2][i][1]);
		}
		i += 1;

		// Swap front and back buffers
		glfwSwapBuffers(window);

		// Poll for and process events
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
