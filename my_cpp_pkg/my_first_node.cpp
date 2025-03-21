#include "rclcpp/rclcpp.hpp"

int main(int argc,char **argv)
{
    rclcpp::init(argc,argv);
    auto_node = std::make_shared<rclcpp::Node>("cpp_test");  // making a node 
    RCLCPP_INFO(Node->get_logger(),"hello cpp node");
    rclcpp::spin(auto_node );
    rclcpp::shutdown();
    return 0;
}