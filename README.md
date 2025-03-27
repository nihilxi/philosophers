# Dining Philosophers Problem Simulation

This project provides a simulation of the classic Dining Philosophers problem, a concurrency scenario demonstrating synchronization challenges among multiple threads. The solution avoids deadlocks by altering the fork acquisition order for one philosopher.

## Problem Description

The Dining Philosophers problem involves `N` philosophers sitting around a table, alternating between thinking and eating. Each philosopher requires two forks (shared resources) to eat. The challenge is to design an algorithm that allows all philosophers to eat without deadlocks (where everyone waits indefinitely for forks) or starvation (where a philosopher never gets to eat).

## Solution Overview

The implementation uses:
- **Threads** to represent philosophers.
- **Mutexes** to model forks (shared resources).
- A **deadlock avoidance strategy**: The last philosopher picks up the right fork first, breaking the circular wait condition.

### Key Components

1. **Threads**  
   Each thread represents a philosopher. The threads execute an infinite loop of:
   - **Thinking**: Simulated with a 1-second delay.
   - **Fork Acquisition**: Locks two mutexes (forks) in an order that depends on the philosopher's position.
   - **Eating**: Simulated with a 1-second delay after acquiring forks.
   - **Fork Release**: Unlocks the mutexes.

2. **Critical Sections**  
   - **Fork Acquisition**: Accessing the `vector<mutex> forks` is a critical section. The `lock()` and `unlock()` operations ensure mutual exclusion.
   - **Console Output**: The `print_action` function uses a mutex to prevent interleaved text from multiple threads.

   **Resolution**:  
   - Forks are always acquired in pairs, with the last philosopher altering the acquisition order to prevent circular dependencies.
   - The `cout_mutex` serializes output operations.

## Running the Program

### Prerequisites
- A C++ compiler supporting C++11 or later (e.g., `g++`).

### Steps
1. **Clone the Repository**  
   ```bash
   git clone <repository-url>
   cd <repository-directory>
   ```

2. **Compile the Code**  
   ```bash
   g++ -std=c++11 -pthread philosophers.cpp -o dining_philosophers
   ```

3. **Execute the Program**  
   Run the executable with the number of philosophers (≥2) as an argument:  
   ```bash
   ./dining_philosophers 5
   ```

   Example output:  
   ```
   Philosopher 0 is thinking.
   Philosopher 1 is thinking.
   Philosopher 4 is eating.
   ...
   ```

4. **Termination**  
   The program runs indefinitely. Use `Ctrl+C` to stop it.

## Limitations

- **Infinite Execution**: The simulation does not terminate and must be stopped manually.
- **Simplified Output**: Console logging may not reflect precise timing due to mutex contention.
- **Resource Limits**: Large numbers of philosophers (e.g., >1000) may strain system resources.
