#include <iostream>
#include <thread>
#include <mutex>
#include <vector>
#include <chrono>
#include <cstdlib>

using namespace std;

// Mutex to synchronize console output
mutex cout_mutex;

// Helper function to print philosopher actions
void print_action(int id, const string& action) {
    cout_mutex.lock();
    cout << "Philosopher " << id << " is " << action << "." << endl;
    cout_mutex.unlock();
}

// Philosopher thread function
void philosopher(int id, int num_philosophers, vector<mutex>& forks) {
    while (true) {
        // Thinking phase
        print_action(id, "thinking");
        this_thread::sleep_for(chrono::seconds(1));

        // Determine left and right fork indices
        int left = id;
        int right = (id + 1) % num_philosophers;

        // Acquire forks based on philosopher's position
        if (id == num_philosophers - 1) {
            // Last philosopher picks right fork first to avoid deadlock
            forks[right].lock();
            forks[left].lock();
        } else {
            forks[left].lock();
            forks[right].lock();
        }

        // Eating phase
        print_action(id, "eating");
        this_thread::sleep_for(chrono::seconds(1));

        // Release forks
        forks[left].unlock();
        forks[right].unlock();
    }
}

int main(int argc, char* argv[]) {
    // Check command line arguments
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <number_of_philosophers>" << endl;
        return 1;
    }

    // Parse number of philosophers
    int num_philosophers = stoi(argv[1]);
    if (num_philosophers < 2) {
        cerr << "Number of philosophers must be at least 2" << endl;
        return 1;
    }

    // Initialize forks (mutexes)
    vector<mutex> forks(num_philosophers);

    // Create philosopher threads
    vector<thread> threads;
    for (int i = 0; i < num_philosophers; ++i) {
        threads.emplace_back(philosopher, i, num_philosophers, ref(forks));
    }

    // Wait for all threads (infinite execution)
    for (auto& t : threads) {
        t.join();
    }

    return 0;
}