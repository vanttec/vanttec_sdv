/** ----------------------------------------------------------------------------
 * @file: pid.hpp
 * @date: July 30, 2020
 * @author: Sebastian Martinez
 * @email: sebas.martp@gmail.com
 * @author: Pedro Sanchez
 * @email: pedro.sc.97@gmail.com
 * 
 * @brief: Single DOF PID Controller class.
 * -----------------------------------------------------------------------------
 * */

#ifndef __PID_H__
#define __PID_H__

#include <sdv_control_ros2/common.hpp>
#include "sdv_msgs/msg/eta_pose.hpp"
#include "std_msgs/msg/float32.hpp"
#include "sdv_msgs/msg/system_dynamics.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include <cmath>

namespace pid
{
 class PID
 {
    protected:
        float sample_time_;

        float k_p_;
        float k_i_;
        float k_d_;

        float U_MAX_;

        DOFControllerType_E controller_type_;

    public:
        PID(const float sample_time, const float k_p, const float k_i, const float k_d, const float u_max, const DOFControllerType_E& type);
        virtual ~PID();

        float f_;
        float g_;

        float u_;
        float a_;
        float u_aux_;

        float set_point_;
        float error_;
        float prev_error_;

        void updateFunctions(const sdv_msgs::msg::SystemDynamics &non_linear_functions);
        void updateSetpoint(const float set_point, const float a_);
        void calculateManipulation(const geometry_msgs::msg::Twist &current_value);
        
 };
}
#endif
