#include "threadpool.hpp"

// global thread worker pool
ctpl::thread_pool threadpool::threadpool(std::thread::hardware_concurrency() + 1);
