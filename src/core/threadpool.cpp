#include "threadpool.hpp"

// the global threadpool for handling requests
ctpl::thread_pool threadpool::g_threadpool(std::thread::hardware_concurrency());