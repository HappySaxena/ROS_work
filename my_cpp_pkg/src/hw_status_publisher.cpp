#include "rclcpp/rclcpp.hpp"
#include "my_robot_interface/msg/hardware_status.hpp"
class HardwareStatusPublisher: public rclcpp::Node 
{
    public:
    HardwareStatusPublisher() : Node("hardware_status_publisher"){
    
        this->declare_parameter("age_publisher",2);
        this->declare_parameter("publisher_frequency",1.0);

        number_ = this->get_parameter("age_publisher").as_int(); // not dynamically understand the type
         double frequency_ = this->get_parameter("publisher_frequency").as_double();
pub_ = this->create_publisher<my_robot_interface::msg::HardwareStatus>("hardware_status",10);
timer_ = this->create_wall_timer(
    std::chrono::milliseconds((int) (1000.0 / frequency_)),
    std::bind(&HardwareStatusPublisher::publishHardwareStatus,this)
);
        RCLCPP_INFO(this->get_logger(), "publishing has been started");
     
    }
    private:
    rclcpp::Publisher<my_robot_interface::msg::HardwareStatus>::SharedPtr pub_;
    rclcpp::TimerBase::SharedPtr timer_;
    
    int number_;
    void publishHardwareStatus()
    {
        auto msg = my_robot_interface::msg::HardwareStatus();
        msg.temperature = 46;
        msg.age = number_;
        msg.are_motor_ready = false;
        msg.debug_msg = "motors are not ready";
        pub_->publish(msg);
    }
          
};

int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<HardwareStatusPublisher>();  // Added missing parenthesis
            // Added missing semicolon
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
