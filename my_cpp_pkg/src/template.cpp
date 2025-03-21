#include "rclcpp/rclcpp.hpp"
class MyNode: public rclcpp::Node 
{
    public:
    MyNode() : Node("my_node"), counter_(0)
    {
        RCLCPP_INFO(this->get_logger(), "Hello cpp node plz###%^");
     
    }
    private:
          
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<MyNode>();  // Added missing parenthesis
            // Added missing semicolon
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
