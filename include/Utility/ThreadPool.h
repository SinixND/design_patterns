// https://stackoverflow.com/a/32593825/21874203

#ifndef IG20240526193442
#define IG20240526193442

#include <condition_variable>
#include <cstdint>
#include <functional>
#include <mutex>
#include <queue>
#include <thread>
#include <vector>

// included as an example of a parameterized macro
#define DISALLOW_COPY_AND_ASSIGN(T) \
    T(const T&) = delete;           \
    T& operator=(const T&) = delete;

// Usage: thread_pool->queueJob([/* args, &ref */] { /* ... */ });
class ThreadPool
{
public:
    // Add a new job to the pool; use a lock so that there isn't a data race.
    void queueJob(const std::function<void()>& job);

    // ThreadPool::Stop will not terminate any currently running jobs, it just waits for them to finish via active_thread.join().
    void stop();

    // The busy() function can be used in a while loop, such that the main thread can wait the threadpool to complete all the tasks before calling the threadpool destructor.
    bool busy();

    ThreadPool();
    ~ThreadPool();
    DISALLOW_COPY_AND_ASSIGN(ThreadPool)

private:
    // Each thread should be running its own infinite loop, constantly waiting for new tasks to grab and run.
    void start();

    // The infinite loop function. This is a while (true) loop waiting for the task queue to open up.
    void threadLoop();

    // Tells threads to stop looking for jobs
    bool should_terminate = false;

    // Prevents data races to the job queue
    std::mutex queue_mutex;

    // Allows threads to wait on new jobs or termination
    std::condition_variable mutex_condition;
    std::vector<std::thread> threads;
    std::queue<std::function<void()>> jobs;
};

#endif

// The anonymous code blocks are used so that when they are exited, the std::unique_lock variables created within them go out of scope, unlocking the mutex.

inline ThreadPool::ThreadPool()
{
    start();
}

inline void ThreadPool::start()
{
    const uint32_t num_threads = std::thread::hardware_concurrency(); // Max # of threads the system supports

    for (uint32_t ii = 0; ii < num_threads; ++ii)
    {
        threads.emplace_back(std::thread(&ThreadPool::threadLoop, this));
    }
}

inline void ThreadPool::threadLoop()
{
    while (true)
    {
        std::function<void()> job;
        {
            std::unique_lock<std::mutex> lock(queue_mutex);

            mutex_condition.wait(lock, [this]
                                 { return !jobs.empty() || should_terminate; });

            if (should_terminate)
            {
                return;
            }

            job = jobs.front();

            jobs.pop();
        }

        job();
    }
}

inline void ThreadPool::queueJob(const std::function<void()>& job)
{
    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        jobs.push(job);
    }

    mutex_condition.notify_one();
}

inline bool ThreadPool::busy()
{
    bool poolbusy;

    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        poolbusy = !jobs.empty();
    }

    return poolbusy;
}

inline void ThreadPool::stop()
{
    while (busy())
        ;

    {
        std::unique_lock<std::mutex> lock(queue_mutex);
        should_terminate = true;
    }

    mutex_condition.notify_all();

    for (std::thread& active_thread : threads)
    {
        active_thread.join();
    }

    threads.clear();
}

inline ThreadPool::~ThreadPool()
{
    stop();
}