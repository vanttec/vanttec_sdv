/** ----------------------------------------------------------------------------
 * @file: el_rasho.hpp
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
#ifndef SDV_CONTROL_ROS2__CAFE_HPP_
#define SDV_CONTROL_ROS2__CAFE_HPP_
#include <memory>
#include <chrono>
#include "car_3dof_dynamic_model.hpp"
#include "rclcpp/rclcpp.hpp"
namespace cafe
{

class Cafe : public car_dynamic_model::CarDynamicModel {
    public:
        /* Constructor and destructor */
        Cafe(rclcpp::Node::SharedPtr node, float sample_time);
        virtual ~Cafe();

        /* Control inputs */
        float B_;           // Steering command
        float D_;           // Throttle command

        
        /* Class methods */
        // void calculateControlInputs();
        private:
            rclcpp::Node::SharedPtr node_;
            float sample_time;
};
} // namespace cafe
#endif // SDV_CONTROL_ROS2__CAFE_HPP_

