#include "threadpool_helpers.hpp"

std::condition_variable threadpool::cv;
std::mutex threadpool::mutex;
int threadpool::tasks_in_queue = 0;