import rclpy
from rclpy.node import Node
from std_msgs.msg import String,UInt32 #std_msgs是ros2内部带有的接口，作用是为我们提供消息类型




class WidthNode(Node):
    def __init__(self,name):
        super().__init__(name)
        self.get_logger().info("大家好我是作家%s"% name)
        #2.创建并初始化发布者成员属性pubnovel
        self.pub_novel = self.create_publisher(String,"sexy_girl",10)
        
        #3.编写发布者逻辑
        #每五秒发布一个章节
        self.i = 0
        self.time_port = 5
        self.timer = self.create_timer(self.time_port,self.timer_callback)
        
        
        #账户钱的数量
        self.account = 80
        #创建并初始化订阅发布者数学submonny
        self.submonny = self.create_subscription(UInt32,"sexy_girl_money",self.recv_monny_callback,10)
        
    def timer_callback(self):
        '''定时器回调函数'''
        msg = String() #创建消息结构体
        msg.data = "第%d回，撤夜湖第%d回偶遇艳娘" % (self.i,self.i) #为消息结构体填入数据
        self.pub_novel.publish(msg)
        self.get_logger().info("李四：我发布了艳娘传奇%s"%msg.data)
        self.i +=1
        
    def recv_monny_callback(self,money):
        """编写回调处理逻辑"""
        self.account += money.data
        self.get_logger().info("李四：我已经收到了稿费%d" % self.account)
        
        
        
def main(args=None):
    rclpy.init(args=args)
    node = WidthNode("li4")
    rclpy.spin(node)
    rclpy.shutdown()
    
