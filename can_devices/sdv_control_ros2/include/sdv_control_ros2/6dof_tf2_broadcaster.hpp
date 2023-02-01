/** ----------------------------------------------------------------------------
 * @file: 6dof_tf2_broadcaster.hpp
 * @date: April 10, 2022
 * @author: Pedro Sanchez
 * @email: pedro.sc.97@gmail.com
 * @author: Sebastian Martinez
 * @email: sebas.martp@gmail.com
 * 
 * @brief: Used to publish the current pose of the simulated vehicle and correctly
 *         represent it in RViz.
 * -----------------------------------------------------------------------------
 **/

#ifndef SDV_CONTROL_ROS2__6DOF_TF2_BROADCASTER_H__
#define SDV_CONTROL_ROS2__6DOF_TF2_BROADCASTER_H__

#include <math.h>
#include <memory>
#include <chrono>
#include "rclcpp/rclcpp.hpp"
#include <string.h>
#include "tf2/LinearMath/Quaternion.h"
#include "tf2_ros/transform_broadcaster.h"
#include "geometry_msgs/msg/transform_stamped.hpp"
#include "geometry_msgs/msg/pose.hpp"
#include "geometry_msgs/msg/pose_stamped.hpp"
#include "nav_msgs/msg/path.hpp"
#include "sdv_msg/msg/eta_pose.hpp"
namespace tf2broadcaster
{
class TF2Broadcaster
{
    public:
        
        TF2Broadcaster(rclcpp::Node::SharedPtr node,const std::string& _parent, const std::string& _child);
        virtual ~TF2Broadcaster();
        
        nav_msgs::msg::Path  path;

        std::string parent_frame;
        std::string child_frame;
        /* Class methods */
        void BroadcastTransform(const sdv_msg::msg::EtaPose& msg);
    private:
        rclcpp::Node::SharedPtr node_;
        std::unique_ptr<tf2_ros::TransformBroadcaster> br;
        rclcpp::Subscription<sdv_msg::msg::EtaPose>::SharedPtr sub_;

};
}// namespace tf2broadcaster
#endif // SDV_CONTROL_ROS2__6DOF_TF2_BROADCASTER_H__