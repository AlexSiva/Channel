#include <iostream>
#include <thread>
#include "buffered_channel.h"
void threadFunction(Channel<int> &channel) {
  std::this_thread::sleep_for(std::chrono::seconds(2));
  channel.Send(1337);
  std::cout << "Successful sending.\n";
  channel.Close();
}
int main() {
  Channel<int> channel(10);
  for (int i = 0; i < 10; i++) {
    channel.Send(i);
  }
  std::thread thr(threadFunction, std::ref(channel));
  for (int i = 0; i < 12; i++) {
    std::pair<int, bool> value = channel.Recv();
    std::cout << value.first << std::endl;
  }
  thr.join();

  return 0;
}