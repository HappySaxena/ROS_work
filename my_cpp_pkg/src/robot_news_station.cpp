#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/msg/string.hpp"

class Robot_news_station_Node : public rclcpp::Node 
{
public:
    Robot_news_station_Node() : Node("robot_news_station"), robot_name_("chitti")
    {
        this->declare_parameter("robot_ka_name","aryan");
        robot_name_ = get_parameter("robot_ka_name").as_string();
        publisher_ = this->create_publisher<example_interfaces::msg::String>("robot_news", 10);
        // Create a timer that calls the publishNews function every 500 milliseconds
        timer_ = this->create_wall_timer(
            std::chrono::milliseconds(500),
            std::bind(&Robot_news_station_Node::publishNews, this)
        );
        RCLCPP_INFO(this->get_logger(), "Publishing has been started");
    }

private:
    void publishNews()
    {
        auto msg = example_interfaces::msg::String(); // auto should be alag 
        msg.data = "Hi, this is a message for " + robot_name_;
        publisher_->publish(msg);
    }
    
    std::string robot_name_;
    rclcpp::Publisher<example_interfaces::msg::String>::SharedPtr publisher_;
    rclcpp::TimerBase::SharedPtr timer_;
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<Robot_news_station_Node>(); 
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
