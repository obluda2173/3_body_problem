/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rk4_tbp.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 19:07:11 by erian             #+#    #+#             */
/*   Updated: 2024/10/15 19:57:57 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RK4_3body_hpp
#define RK4_3body_hpp

#include <stdio.h>
#include <vector>
#include "../../eigen/Eigen/Dense"

using namespace Eigen ;

// Project specific typing

typedef Array<Vector2d,Dynamic,1> vecArray;
typedef Array<vecArray, Dynamic, 1> vecArray2;

class rk4_tbp {
    
public:
    
    // Constructor
    
    rk4_tbp(float m1,float m2,float m3){
        Mass1 = m1;
        Mass2 = m2;
        Mass3 = m3;
    };
    
    // Methods
    
    Vector2d bodyFunc(Vector2d r1, Vector2d r2, Vector2d r3, float mass2, float mass3);
    vecArray2 Run(float step, int N, Vector2d r1_0 , Vector2d r2_0 , Vector2d r3_0, const Vector2d v1_0 , Vector2d v2_0 , Vector2d v3_0);
    
private:
    
    float G = 1;
    float Mass1;
    float Mass2;
    float Mass3;
    
    
};
#endif