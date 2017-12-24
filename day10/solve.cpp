#include <iyostream>

/* TODO: 2 versions, one with lock/mutex the other with a lock free queue
 */

void print()
{
	std::cout << "Asynchronous call" << std::endl;
}

template <typename T = void(*)()>
struct Job
{
	int delay;
	T f;
};


template <typename T = void(*)()>
class Scheduler
{
public:
	void schedule(T f, int delay)
	{
		m.lock();
		jobs.emplace_back(d, delay);
		m.unlock();
	}

	void stopScheduling()
	{
		running = false;
	}

	void startScheduling()
	{
		future = std::launch(std::launch::async,
			Scheduler::loop, std::ref(jobs));

		running = true;
	}
private:
	static void loop(std::list<Job<T>>& jobs)
	{
		while (running) {
			m.lock();
			for (Job& j : jobs) {
				if (j.delay == 0) {
					j.f();
				}
				--j.delay;
			}
			m.unlock();
		}
	}
private:
	std::mutex m;
	std::list<Job<T>> jobs;

	std::future<void> future;
	std::atomic<bool> running;
};


int main()
{
	Scheduler s;
	s.schedule();
	s.schedule();
	s.schedule();
	s.schedule();

	while (true) {
		std::cout << "Test " << std::endl;
	}
}
