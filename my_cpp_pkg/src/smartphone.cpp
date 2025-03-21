#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"
class SmartPhoneNode : public rclcpp::Node 
{
    public:
    SmartPhoneNode() : Node("smartphone")
    {
      
        
        subscriber_= this->create_subscription<example_interfaces::msg::String>("robot_news",10,
        std::bind(&SmartPhoneNode::CallbackRobotNews,this,std::placeholders::_1));
        RCLCPP_INFO(this->get_logger(), "This is now ready for subscribing");
     
    }
    private:
    void CallbackRobotNews(const example_interfaces::msg::String::SharedPtr msg){  // we have to use for messages a cosnst keyword 
        RCLCPP_INFO(this->get_logger(), "Received a message: %s", msg->data.c_str());
    }
    rclcpp::Subscription<example_interfaces::msg::String>::SharedPtr subscriber_;
   
          
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SmartPhoneNode>();  // Added missing parenthesis
            // Added missing semicolon
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
