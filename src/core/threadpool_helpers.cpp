#include "threadpool_helpers.hpp"

std::condition_variable threadpool::cv;
std::mutex threadpool::mutex;
std::atomic<int> threadpool::tasks_in_queue = 0;