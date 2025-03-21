#include "rclcpp/rclcpp.hpp"
class MyNode: public rclcpp::Node 
{
    public:
    MyNode() : Node("my_node"), counter_(0)
    {
        RCLCPP_INFO(this->get_logger(), "Hello cpp node plz###%^");
        timer_= this->create_wall_timer(std::chrono::seconds(1),
        std::bind(&MyNode::timerCallback, this));
    }
    private:
          void timerCallback()
          {
            counter_++;
            RCLCPP_INFO(this->get_logger(), "Timer callback is %d",counter_);
          }
          rclcpp::TimerBase::SharedPtr timer_;
          int counter_;
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
