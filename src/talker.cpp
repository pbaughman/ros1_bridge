// Copyright 2015 Open Source Robotics Foundation, Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include <iostream>

#include <rclcpp/rclcpp.hpp>

#include <simple_msgs/msg/string.hpp>


int main(int argc, char * argv[])
{
  rclcpp::init(argc, argv);

  auto node = rclcpp::node::Node::make_shared("talker");

  auto chatter_pub = node->create_publisher<simple_msgs::msg::String>("chatter", 10);

  rclcpp::WallRate loop_rate(10);

  auto count = 0;
  while (rclcpp::ok()) {
    auto msg = std::make_shared<simple_msgs::msg::String>();
    msg->data = "hello world " + std::to_string(count);
    std::cout << msg->data << std::endl;
    chatter_pub->publish(msg);

    rclcpp::spin_some(node);
    loop_rate.sleep();
    ++count;
  }

  return 0;
}