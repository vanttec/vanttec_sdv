#include <memory>
#include <chrono>
#include "sdv_control_ros2/6dof_tf2_broadcaster.hpp"
namespace tf2broadcaster
{
   TF2Broadcaster::TF2Broadcaster(rclcpp::Node::SharedPtr node,const std::string& _parent, const std::string& _child): node_(node), parent_frame(_parent), child_frame(_child)
   {
    
    br = std::make_unique<tf2_ros::TransformBroadcaster>(node_);
    sub_ = node_->create_subscription<sdv_msgs::msg::EtaPose>("/car_simulation/dynamic_model/eta_pose",  10,std::bind(&TF2Broadcaster::BroadcastTransform, this, std::placeholders::_1));
    

   }
   TF2Broadcaster::~TF2Broadcaster(){}

   void TF2Broadcaster::BroadcastTransform(const sdv_msgs::msg::EtaPose& _pose)
 {    
    geometry_msgs::msg::TransformStamped transformStamped;
    
    // From NED to RViz reference frame (x forward, y left, z up): negate y and z
    transformStamped.header.stamp               = node_->now();
    transformStamped.header.frame_id            = this->parent_frame;
    transformStamped.child_frame_id             = this->child_frame;
    transformStamped.transform.translation.x    = _pose.x;
    transformStamped.transform.translation.y    = -_pose.y;
    transformStamped.transform.translation.z    = -_pose.z;

    tf2::Quaternion q;
    q.setRPY(_pose.phi, _pose.theta, _pose.psi);
    q.normalize();
    transformStamped.transform.rotation.x = q.x();
    transformStamped.transform.rotation.y = q.y();
    transformStamped.transform.rotation.z = q.z();
    transformStamped.transform.rotation.w = q.w();
    // std::cout << std::endl;
    // std::cout << transformStamped.transform.rotation.x << std::endl;
    // std::cout << transformStamped.transform.rotation.y << std::endl;
    // std::cout << transformStamped.transform.rotation.z << std::endl;
    // std::cout << transformStamped.transform.rotation.w << std::endl;

    // For NED to ENU: swap x and y and negate z
    // transformStamped.transform.rotation.x = _pose.orientation.y;
    // transformStamped.transform.rotation.y = _pose.orientation.x;
    // transformStamped.transform.rotation.z = -_pose.orientation.z;
    // transformStamped.transform.rotation.w = _pose.orientation.w;

    this->br->sendTransform(transformStamped);

    geometry_msgs::msg::PoseStamped      pose;

    pose.header.stamp       = node_->now();
    pose.header.frame_id    = this->parent_frame;
    pose.pose.position.x    = _pose.x;
    pose.pose.position.y    = -_pose.y;
    pose.pose.position.z    = -_pose.z;
    pose.pose.orientation.x = q.x();
    pose.pose.orientation.y = q.y();
    pose.pose.orientation.z = q.z();
    pose.pose.orientation.w = q.w();

    this->path.header.stamp     =  node_->now();
    this->path.header.frame_id  = this->parent_frame;
    this->path.poses.push_back(pose);
}

}// namespace tf2broadcaster