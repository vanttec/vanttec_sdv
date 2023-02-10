/** ----------------------------------------------------------------------------
 * @file: el_rasho.cpp
 * @date: November 29, 2022
 * @author: Sebas Mtz
 * @email: sebas.martp@gmail.com
 * @author: Montserrat Cruz
 *
 * @brief: Description of 3-DOF car model in the non-inertial frame with
           Euler Angles for Applied Robotics class (con Montserrat).
           The nonlinear bycicle model was used.
           This model works for low speed movement and considers no
           longitudinal slip.
 * -----------------------------------------------------------------------------
 **/

#include <memory>
#include <functional>
#include <string>
#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "sdv_control_ros2/el_rasho.hpp"
#include <stdio.h>
namespace cafe
{

    Cafe::Cafe(rclcpp::Node::SharedPtr node,float   sample_time): node_(node), CarDynamicModel(sample_time)
    {

        /* Vehicle physical parameters */
        m_ = 1120;
        Iz_ = 1908.94666;
        A_ = 3.426;
        Cm_ = 700;
        //Cm_ = 340; // Chosen so max speed = 35 km/h = 9.722 m/s
        Cd_ = 0.9; // Cd was chosen based on the book 'fundamentals of vehicle dynamics'
        len_f_ = 1.58;
        len_r_ = 2.69;
        car_len_ = 4.27;
        MAX_R_ = 4.5;
        // u_dot_brake_ = 0.0;
        fr_ = 0.015;           // For passenger cars, from fundamentals of vehicle dynamics book
        C_alpha_ = 51935.3434; // m*g*fr*cos(theta) -> from fundamentals of vehicle dynamics book
        alpha_f_ = 0.0;
        alpha_r_ = 0.0;
        sub_ = node_->create_subscription<std_msgs::msg::Float32>("/car_control/car_control_node/steering", 10,std::bind(&CarDynamicModel::setSteeringInput, this, std::placeholders::_1));
        sub2_ = node_->create_subscription<sdv_msg::msg::ThrustControl>("/car_control/car_control_node/force", 10,std::bind(&CarDynamicModel::setForceInput, this, std::placeholders::_1));
        sub3_ = node_->create_subscription<sdv_msg::msg::VehicleControl>("/sdv/vanttec_vehicle/vehicle_control_cmd_manual", 10,std::bind(&CarDynamicModel::manual_control, this, std::placeholders::_1));
    }
Cafe::~Cafe(){}
} // namespace cafe
