/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 19:03:43 by erian             #+#    #+#             */
/*   Updated: 2024/10/15 19:23:38 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef circle_hpp
#define circle_hpp

#include <stdio.h>
#include <cmath>
#include <vector>
#include "../../glfw/include/GLFW/glfw3.h"

// Circle Asset Class

class CircleGL {
    
public:
    
    // Constructor
    
    CircleGL(float x, float y, float radius,float R,float G,float B){
        
        circleX = x;
        circleY = y;
        circleRadius = radius;
        Red = R;
        Green = G;
        Blue = B;
        
    };
    
    // Methods
    
    void draw(bool trail);
    
    void move(float newX,float newY);
    
    std::vector<float> Xpositions;
    std::vector<float> Ypositions;

private:
    
    float circleX;
    float circleY;
    float circleRadius;
    
    float Red;
    float Green;
    float Blue;
};


#endif