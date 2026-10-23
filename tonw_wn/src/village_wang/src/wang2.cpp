#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/string.hpp"
#include "std_msgs/msg/u_int32.hpp"

//创建命名空间
using std::placeholders::_1;
using std::placeholders::_2;

/*创建一个类继承Node所有的功能*/

class SingDogNode : public rclcpp::Node{
    public:
    SingDogNode(std::string name) : Node(name){
        RCLCPP_INFO(this -> get_logger(),"大家好我是单身狗%s",name.c_str());
    
        //使用声明的订阅者成员变量创建一个订阅者，来订阅李四的小说，名字需要与python节点定义的一致，否则无法订阅
        sub_novel = this->create_subscription<std_msgs::msg::String>("sexy_girl", 10, std::bind(&SingDogNode::topic_callback,this,_1));
        //使用声明的发布者成员变量创建一个发布者，来给李四支付稿费，名字需要与python节点定义的一致，否则python方面的订阅节点无法订阅到该节点
        pub_novel = this->create_publisher<std_msgs::msg::UInt32>("sexy_girl_money", 10);
    
    };


    private:
    /*创建订阅与接受回调函数，代表王二开始订阅艳娘传奇这个话题节点
    （艳娘传奇是python编写的程序发布的一个话题已经实现话题的发布以及订阅，订阅是指接收打赏金额话题）
    在这里我们需要实现王二通过订阅与发布与python的节点进行通行
    */
   //声明一个订阅者（成员变量），用于订阅小说
   rclcpp::Subscription<std_msgs::msg::String>::SharedPtr sub_novel;

   //声明一个发布者（成员变量），用于给李四发布稿费
   rclcpp::Publisher<std_msgs::msg::UInt32>::SharedPtr pub_novel;

   //收到话题后的回调函数
   void topic_callback(const std_msgs::msg::String::SharedPtr msg){

        //订阅到小说后，通过发布者给李四发稿费
        //新建一张人民币，使用发布者指定的类型
        std_msgs::msg::UInt32 money;
        money.data = 10;
        //发送给李四
        pub_novel->publish(money);

        //
        RCLCPP_INFO(this->get_logger(),"朕已阅，%s", msg ->data.c_str());

   };

   
};


int main(int argc,char **argv){
    rclcpp::init(argc, argv);
    auto node = std::make_shared<SingDogNode>("wnag2");
    rclcpp::spin(node);
    rclcpp::shutdown();
    return 0;
}

