/**
 * UWB localization ceres utilities header.
 *
 * Giorgio Manca <giorgio.manca97@gmail.com>
 * Lorenzo Bianchi <lnz.bnc@gmail.com>
 * Intelligent Systems Lab <isl.torvergata@gmail.com>
 *
 * April 27, 2023
 */

/**
 * This is free software.
 * You can redistribute it and/or modify this file under the
 * terms of the GNU General Public License as published by the Free Software
 * Foundation; either version 3 of the License, or (at your option) any later
 * version.
 *
 * This file is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with
 * this file; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin St, Fifth Floor, Boston, MA 02110-1301 USA.
 */

#include <ceres/ceres.h> // sudo ln -s /usr/local/include/eigen3/Eigen /usr/include/Eigen


using ceres::CostFunction;
using ceres::Problem;
using ceres::Solver;


class Function : public CostFunction {
public:
    Function(unsigned int n1, unsigned int n2, 
             double cost, double dist_bars,
             std::vector<double>& dists1, 
             std::vector<double>& dists2, 
             std::vector<double>& poles1_x, 
             std::vector<double>& poles1_y, 
             std::vector<double>& poles1_z, 
             std::vector<double>& poles2_x, 
             std::vector<double>& poles2_y, 
             std::vector<double>& poles2_z);

    bool Evaluate(double const* const* parameters, double* residuals, double** jacobians) const;
    
private:
    unsigned int n1, n2;
    double cost, dist_bars;
    std::vector<double>& dists1;
    std::vector<double>& dists2; 
    std::vector<double>& poles1_x;
    std::vector<double>& poles1_y;
    std::vector<double>& poles1_z;
    std::vector<double>& poles2_x;
    std::vector<double>& poles2_y;
    std::vector<double>& poles2_z;
};


struct Result {
    Result() {}

    std::array<double, 3> p1;
    std::array<double, 3> p2;
    ceres::Solver::Summary summary;
};


Result solve(Function *function, std::array<double, 3> &p1_0, std::array<double, 3> &p2_0);