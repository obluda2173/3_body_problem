/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tbp.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erian <erian@student.42>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 13:33:10 by erian             #+#    #+#             */
/*   Updated: 2024/10/15 19:24:24 by erian            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef tbp_hpp
# define tbp_hpp

# include <iostream>
# include <cmath>
# include "../../glfw/include/GLFW/glfw3.h"
# include "../../eigen/Eigen/Dense"
# include "../circle/circle.hpp"
# include "../physics/rk4_tbp.hpp"

using namespace Eigen;

typedef Array<Vector2d, Dynamic, 1> vecArray;
typedef Array<vecArray, Dynamic, 1> vecArray2;

#endif 