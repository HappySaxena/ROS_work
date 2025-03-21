#include "rclcpp/rclcpp.hpp"
#include "example_interfaces/srv/add_two_ints.hpp"
class AddTwoInts: public rclcpp::Node 
{
    public:
    AddTwoInts() : Node("add_two_ints_client")
    {
        
       
        threads_.push_back(std::thread(std::bind(&AddTwoInts::callAddTwoIntsService,this,1,7)));  // bracket nhi lgate extra dhyan rkh
     threads_.push_back(std::thread(std::bind(&AddTwoInts::callAddTwoIntsService,this,1,9)));
    
    }
    void callAddTwoIntsService(int64_t a,int64_t b) 
    {
        auto client = this->create_client<example_interfaces::srv::AddTwoInts>("add_two_ints");
         while (!client->wait_for_service(std::chrono::seconds(1))){
             RCLCPP_WARN(this->get_logger(),"Waiting for the server to be up...");
            }
            auto request = std::make_shared<example_interfaces::srv::AddTwoInts::Request>();
            request->a = a;
            request->b = b;
            auto future = client->async_send_request(request);
            try
            {
                auto response = future.get(); 
                RCLCPP_INFO(this->get_logger(), " %ld + %ld =  %ld", a,b,response->sum);
            }
            catch(const std::exception& e)
            {
                RCLCPP_ERROR(this->get_logger(),"Service call failed ");
            }
            
    }
    private:
          
          std::vector<std::thread> threads_;  // vector bnake multiple thread bna skte hain....har thread se request bhej skte hain fir//
};
int main(int argc, char **argv)
{
    rclcpp::init(argc, argv);
    auto node = std::make_shared<AddTwoInts>();
  

    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}
