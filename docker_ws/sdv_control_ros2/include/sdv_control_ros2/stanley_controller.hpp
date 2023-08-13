/** ----------------------------------------------------------------------------
 * @file: stanley_controller.hpp
 * @date: November 30, 2022
 * @author: Sebas Mtz
 * @email: sebas.martp@gmail.com
 * 
 * @brief: Stanley Controller class
 * -----------------------------------------------------------------------------
 * */

#ifndef __STANLEY_CONTROLLER__
#define __STANLEY_CONTROLLER__

#include <stdio.h>
#include <cmath>
#include "sdv_msgs/msg/eta_pose.hpp"
#include "geometry_msgs/msg/twist.hpp"
#include "std_msgs/msg/float32.hpp"


namespace stanleycontroller
{
 class StanleyController
 {
    protected:
        float DELTA_MAX_;       // Max steering
        float psi_;             // Current heading
        float k_;               // Controller gain
        float k_soft_;          // Soft gain
        float e_;               // Crosstrack error
        float vel_;             // velocity vector norm
        float ak_;


    public:
        StanleyController(float delta_max, float k, float k_soft);
        virtual ~StanleyController();
        
        sdv_msgs::msg::EtaPose vehicle_pose_;
        float delta_;           // Desired steering

        void calculateCrosstrackError(float x0, float y0, float x1, float y1);
        void setHeading(const sdv_msgs::msg::EtaPose &pose);
        void calculateSteering(const geometry_msgs::msg::Twist &vel);
        
 };
}
#endif
