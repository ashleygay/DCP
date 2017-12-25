#include <iostream>
#include <iterator>
#include <list>
#include <mutex>
#include <atomic>
#include <future>

/* TODO: 2 versions, one with lock/mutex the other with a lock free queue
 */

void print()
{
	std::cout << "Asynchronous call" << std::endl;
}

struct Job
{
	Job(void(*function)(), int _delay): f(function), delay(_delay){}

	void(*f)();
	int delay;
};

class Scheduler
{
public:
	~Scheduler()
	{
		stopScheduling();
	}

	void schedule(void(*f)(), int delay)
	{
		m.lock();
		jobs.push_back(Job(f, delay));
		m.unlock();
	}

	void stopScheduling()
	{
		running = false;
		future.get();
	}

	void startScheduling()
	{
		future = std::async(std::launch::async,
			&Scheduler::loop, this);

		running = true;
	}
private:
	void loop()
	{
		while (running) {
			m.lock();

			for (auto j = jobs.begin() ; j != jobs.end(); ++j) {
				if (j->delay == 0) {
					j->f();
				}
				--j->delay;
			}

			m.unlock();
			using namespace std::chrono_literals;
			std::this_thread::sleep_for(1ms);
		}
	}

private:
	std::list<Job> jobs;

	std::atomic<bool> running;
	std::mutex m;
	std::future<void> future;
};


int main()
{
	Scheduler s;
	s.startScheduling();
	s.schedule(print, 1000);
	while (true) {
		s.schedule(print, 2000);
		using namespace std::chrono_literals;
		std::this_thread::sleep_for(1ms);
	}
}
