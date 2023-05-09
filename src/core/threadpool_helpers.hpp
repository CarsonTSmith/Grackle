#pragma once

#include <atomic>
#include <condition_variable>
#include <mutex>

// these are used so that the ctpl_stl.h threadpool can 
// notify grackle's do_poll() thread that the queue is
// less than MAX_QUEUE_SIZE
namespace threadpool {

static constexpr int MAX_QUEUE_SIZE = 1024;

extern std::condition_variable cv;
extern std::mutex mutex;
extern std::atomic<int> tasks_in_queue;

}