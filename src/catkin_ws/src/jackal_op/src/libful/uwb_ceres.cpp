/**
 * UWB localization ceres utilities.
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

#include "uwb_ceres.hpp"

/**
 * @brief Ceres cost function constructor.
 *
 * @param n1 Number of anchors seen by tag1.
 * @param n2 Number of anchors seen by tag2.
 * @param cost Cost for distance constraint.
 * @param dist_bars Distance between UWBs poles..
 * @param vectors
 */
Function::Function(unsigned int n1, unsigned int n2, 
                   double cost, double dist_bars,
                   std::vector<double>& dists1, 
                   std::vector<double>& dists2, 
                   std::vector<double>& poles1_x, 
                   std::vector<double>& poles1_y, 
                   std::vector<double>& poles1_z, 
                   std::vector<double>& poles2_x, 
                   std::vector<double>& poles2_y, 
                   std::vector<double>& poles2_z) 
                   : 
                   n1(n1), n2(n2),
                   cost(cost), dist_bars(dist_bars),
                   dists1(dists1),
                   dists2(dists2),
                   poles1_x(poles1_x),
                   poles1_y(poles1_y),
                   poles1_z(poles1_z),
                   poles2_x(poles2_x),
                   poles2_y(poles2_y),
                   poles2_z(poles2_z)
{
    std::vector<int32_t> *block_sizes = mutable_parameter_block_sizes();
    block_sizes->reserve(1);
    block_sizes->push_back(6);
    set_num_residuals(n1+n2+1);
}

/**
 * @brief Ceres cost function Evaluate.
 *
 * @param parameters
 * @param residuals
 * @param jacobians
 */
bool Function::Evaluate(double const* const* parameters, double* residuals, double** jacobians) const 
{
    double x1 = parameters[0][0], y1 = parameters[0][1], z1 = parameters[0][2];
    double x2 = parameters[0][3], y2 = parameters[0][4], z2 = parameters[0][5];

    int param_size = parameter_block_sizes()[0];
    double nrm;
    double* nrms1 = new double[n1];
    double* nrms2 = new double[n2];
    double dx, dy, dz;

    for (unsigned int i = 0; i < n1; i++) 
    {
        dx = (x1 - poles1_x[i]);
        dy = (y1 - poles1_y[i]);
        dz = (z1 - poles1_z[i]);
        nrms1[i] = sqrt(dx*dx + dy*dy + dz*dz);
        residuals[i] = nrms1[i] - dists1[i];
    }

    for (unsigned int i = 0; i < n2; i++) 
    {
        dx = (x2 - poles2_x[i]);
        dy = (y2 - poles2_y[i]);
        dz = (z2 - poles2_z[i]);
        nrms2[i] = sqrt(dx*dx + dy*dy + dz*dz);
        residuals[n1+i] = nrms2[i] - dists2[i];
    }

    dx = x1-x2;
    dy = y1-y2;
    dz = z1-z2;

    nrm = sqrt(dx*dx + dy*dy + dz*dz);
    residuals[n1+n2] = cost * (nrm - dist_bars);

    if (jacobians != nullptr) {
        if (jacobians[0] != nullptr)
        {
            for (unsigned int i = 0; i < param_size * (n1+n2+1); i++) {
                jacobians[0][i] = 0.0;
            }
            
            for (unsigned int i = 0; i < n1; i++) 
            {
                if(nrms1[i] > 0.0) {
                    jacobians[0][i * param_size + 0] += (x1 - poles1_x[i]) / nrms1[i];
                    jacobians[0][i * param_size + 1] += (y1 - poles1_y[i]) / nrms1[i];
                    jacobians[0][i * param_size + 2] += (z1 - poles1_z[i]) / nrms1[i];
                }                
            }

            for (unsigned int i = 0; i < n2; i++) 
            {
                if(nrms2[i] > 0.0) {
                    jacobians[0][(i + n1) * param_size + 3] += (x2 - poles2_x[i]) / nrms2[i];
                    jacobians[0][(i + n1) * param_size + 4] += (y2 - poles2_y[i]) / nrms2[i];
                    jacobians[0][(i + n1) * param_size + 5] += (z2 - poles2_z[i]) / nrms2[i];
                }
            }

            if(nrm > 0.0) {
                jacobians[0][(n1+n2) * param_size + 0] += cost * dx / nrm;
                jacobians[0][(n1+n2) * param_size + 1] += cost * dy / nrm;
                jacobians[0][(n1+n2) * param_size + 2] += cost * dz / nrm;
                jacobians[0][(n1+n2) * param_size + 3] -= cost * dx / nrm;
                jacobians[0][(n1+n2) * param_size + 4] -= cost * dy / nrm;
                jacobians[0][(n1+n2) * param_size + 5] -= cost * dz / nrm;
            }
        }
    }

    delete[] nrms1;
    delete[] nrms2;

    return true;
}


Result solve(Function *function, std::array<double, 3> &p1_0, std::array<double, 3> &p2_0){
    ceres::Problem problem;

    double p[6];
    p[0] = p1_0[0];
    p[1] = p1_0[1];
    p[2] = p1_0[2];
    p[3] = p2_0[0];
    p[4] = p2_0[1];
    p[5] = p2_0[1];

    std::vector<double*> parameters;
    parameters.reserve(1);
    parameters.push_back(p);

    problem.AddResidualBlock(function, nullptr, parameters);

    Solver::Options options;
    options.max_num_iterations = 10000;
    options.linear_solver_type = ceres::DENSE_QR;
    options.minimizer_progress_to_stdout = false;

    Result result;
    Solve(options, &problem, &result.summary);

    result.p1[0] = p[0];
    result.p1[1] = p[1];
    result.p1[2] = p[2];
    result.p2[0] = p[3];
    result.p2[1] = p[4];
    result.p2[2] = p[5];

    return result;
}