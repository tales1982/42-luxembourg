Dining Philosophers Problem Implementation
Table of Contents
Introduction
Project Structure
Compilation and Execution
Program Workflow
Detailed Function Descriptions
Main Functions (philo.c)
Initialization Functions (start.c)
Simulation Control Functions (launch.c)
Philosopher Actions (philo_actions.c)
Utility Functions (utils.c)
Philosopher Checks (philo_checks.c)
Error Handling (msg_error.c)
Conclusion
Introduction
The Dining Philosophers Problem is a classic synchronization problem in computer science, illustrating the challenges of allocating limited resources among multiple processes without causing deadlock or starvation.

In this implementation, we simulate a number of philosophers sitting around a table, each alternating between thinking and eating. Forks (shared resources) are placed between each pair of philosophers, and each philosopher requires two forks to eat.

The program ensures that:

No two philosophers eat with the same fork simultaneously.
Philosophers do not starve and are able to eat after thinking.
The simulation handles different scenarios, including when a philosopher dies due to starvation.
Project Structure
The project is organized into multiple source files for clarity and modularity:

philo.h: Header file containing structure definitions and function prototypes.
philo.c: Contains the main function and core execution logic.
start.c: Handles initialization of simulation parameters and mutexes.
launch.c: Manages the launching and termination of the simulation.
philo_actions.c: Defines actions that each philosopher can perform.
utils.c: Provides utility functions for time management and logging.
philo_checks.c: Contains functions to monitor philosophers' states.
msg_error.c: Handles error messaging and reporting.
Compilation and Execution
Compilation
To compile the program, ensure you have gcc installed and run:

bash
Copiar código
make
This will generate an executable named philo.

Execution
Run the program using the following syntax:

bash
Copiar código
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [number_of_times_each_philosopher_must_eat]
Parameters:

number_of_philosophers: Total philosophers and forks.
time_to_die (in milliseconds): Time a philosopher can survive without eating.
time_to_eat (in milliseconds): Time a philosopher takes to eat.
time_to_sleep (in milliseconds): Time a philosopher spends sleeping.
number_of_times_each_philosopher_must_eat (optional): Simulation ends when all philosophers have eaten this many times.
Example:

bash
Copiar código
./philo 5 800 200 200 7
This starts a simulation with 5 philosophers where each must eat 7 times, and with specified times for dying, eating, and sleeping.

Program Workflow
Initialization:

The program parses command-line arguments and initializes simulation parameters.
Mutexes for forks and shared resources are initialized.
Philosopher structures are set up with initial values.
Launching Threads:

A thread is created for each philosopher, representing their lifecycle.
A monitoring thread checks for philosopher deaths and whether all have eaten enough times.
Philosopher Lifecycle:

Each philosopher alternates between thinking, eating, and sleeping.
Before eating, a philosopher attempts to pick up the left and right forks (mutexes).
Actions are logged with timestamps relative to the simulation start time.
Monitoring and Termination:

The monitoring thread continually checks if any philosopher has died or if all have eaten the required number of times.
Upon detection, the simulation stops, threads are joined, and resources are cleaned up.
Detailed Function Descriptions
Main Functions (philo.c)
1. main(int argc, char **argv)
Description:

Entry point of the program.
Validates command-line arguments.
Initializes the simulation and launches it.
Handles return values and exits appropriately.
Parameters:

argc: Argument count.
argv: Argument vector containing simulation parameters.
Behavior:

Calls init_simulation to set up the simulation.
If initialization is successful, calls launch_simulation to start the simulation.
Returns exit status based on success or encountered errors.
Initialization Functions (start.c)
1. parse_arguments(t_simulation *sim, char **argv)
Description:

Parses and validates command-line arguments.
Sets simulation parameters based on input.
Parameters:

sim: Pointer to the simulation structure.
argv: Argument vector containing input parameters.
Behavior:

Converts string arguments to integers using ft_atoi.
Checks for valid ranges and assigns values to sim.
Returns 0 on success or calls handle_error on failure.
2. setup_philos(t_simulation *sim)
Description:

Initializes philosopher structures with default values.
Parameters:

sim: Pointer to the simulation structure.
Behavior:

Assigns IDs, fork IDs, and initial meal times to each philosopher.
Handles the special case when there is only one philosopher.
Returns 0 upon successful setup.
3. init_mutexes(t_simulation *sim)
Description:

Initializes mutexes for forks and shared resources.
Parameters:

sim: Pointer to the simulation structure.
Behavior:

Initializes a mutex for each fork.
Initializes mutexes for writing (write_lock) and meal checking (meal_check).
Returns 0 on success or 1 if mutex initialization fails.
4. init_simulation(t_simulation *sim, char **argv)
Description:

Orchestrates the entire initialization process.
Parameters:

sim: Pointer to the simulation structure.
argv: Argument vector containing input parameters.
Behavior:

Calls parse_arguments, init_mutexes, and setup_philos sequentially.
Returns 0 on successful initialization or appropriate error code.
Simulation Control Functions (launch.c)
1. launch_simulation(t_simulation *sim)
Description:

Starts the simulation by creating philosopher threads and monitoring threads.
Parameters:

sim: Pointer to the simulation structure.
Behavior:

Records the start time of the simulation.
Creates a thread for each philosopher, executing philo_thread.
Calls check_death to monitor the simulation status.
Cleans up resources by calling cleanup_simulation.
Returns 0 on success or 1 if thread creation fails.
2. check_death(t_simulation *sim, t_philosopher *philos)
Description:

Continuously monitors philosophers for death and completion conditions.
Parameters:

sim: Pointer to the simulation structure.
philos: Array of philosopher structures.
Behavior:

Loops until a philosopher dies or all have eaten enough times.
Calls check_philo_death for each philosopher to detect death.
Calls check_all_philos_full to check if all philosophers have met the meal requirement.
Sleeps briefly between checks to prevent excessive CPU usage.
3. cleanup_simulation(t_simulation *sim, t_philosopher *philos)
Description:

Cleans up resources after simulation ends.
Parameters:

sim: Pointer to the simulation structure.
philos: Array of philosopher structures.
Behavior:

Joins all philosopher threads to ensure they have completed execution.
Destroys all fork mutexes and other shared resource mutexes.
Ensures no resources are left allocated post-simulation.
Philosopher Actions (philo_actions.c)
1. philo_eats(t_philosopher *philo)
Description:

Handles the eating action for a philosopher.
Parameters:

philo: Pointer to the philosopher structure.
Behavior:

Attempts to lock left and right fork mutexes.
Logs the action of taking forks and starting to eat.
Updates last_meal_time and increments meals_eaten.
Sleeps for time_to_eat duration.
Unlocks fork mutexes after eating.
2. philo_sleeps_and_thinks(t_philosopher *philo)
Description:

Handles the sleeping and thinking actions for a philosopher.
Parameters:

philo: Pointer to the philosopher structure.
Behavior:

Logs the action of sleeping and sleeps for time_to_sleep duration.
After sleeping, logs the action of thinking if the simulation is still ongoing.
Checks for death or completion before proceeding to think.
Utility Functions (utils.c)
1. ft_atoi(const char *str)
Description:

Converts a string to an integer.
Parameters:

str: Input string representing a number.
Behavior:

Parses the string and converts it to a long integer.
Returns the integer value or -1 if the string is invalid.
2. get_current_time(void)
Description:

Retrieves the current time in milliseconds since epoch.
Returns:

Current time as a long long integer in milliseconds.
Behavior:

Uses gettimeofday to get current time.
Converts seconds and microseconds to milliseconds.
3. time_diff(long long start, long long end)
Description:

Calculates the difference between two time points.
Parameters:

start: Start time in milliseconds.
end: End time in milliseconds.
Returns:

Time difference in milliseconds.
4. sleep_for(long long time, t_simulation *sim)
Description:

Sleeps for a specified duration, interruptible by simulation end.
Parameters:

time: Duration to sleep in milliseconds.
sim: Pointer to the simulation structure.
Behavior:

Sleeps in small intervals (using usleep) while periodically checking if a philosopher has died.
Ensures the thread wakes up promptly if the simulation ends.
5. log_action(t_simulation *sim, int id, char *message)
Description:

Logs a philosopher's action with a timestamp.
Parameters:

sim: Pointer to the simulation structure.
id: Philosopher's ID.
message: Action message to log.
Behavior:

Locks write_lock mutex to ensure thread-safe logging.
Prints the timestamped message to standard output.
Unlocks the mutex after logging.
Philosopher Checks (philo_checks.c)
1. check_philo_death(t_simulation *sim, t_philosopher *philo, int i)
Description:

Checks if a specific philosopher has died.
Parameters:

sim: Pointer to the simulation structure.
philo: Array of philosopher structures.
i: Index of the philosopher to check.
Returns:

1 if the philosopher has died, 0 otherwise.
Behavior:

Locks meal_check mutex to access shared data safely.
Compares current time with last_meal_time to determine if the philosopher has starved.
Sets someone_died flag if death is detected and logs the event.
Unlocks the mutex before returning.
2. check_all_philos_full(t_simulation *sim, t_philosopher *philos)
Description:

Checks if all philosophers have eaten the required number of times.
Parameters:

sim: Pointer to the simulation structure.
philos: Array of philosopher structures.
Returns:

1 if all philosophers are full, 0 otherwise.
Behavior:

Iterates through all philosophers, counting those who have met the meal requirement.
If all are full, sets all_full flag and returns 1.
Ensures thread-safe access using meal_check mutex.
Error Handling (msg_error.c)
1. handle_error(int error_code)
Description:

Prints appropriate error messages based on error codes.
Parameters:

error_code: Integer representing the type of error.
Returns:

The same error_code passed in.
Behavior:

Matches error_code to predefined error messages.
Prints the corresponding message to standard output.
Facilitates consistent error reporting throughout the program.
Conclusion
This implementation of the Dining Philosophers Problem demonstrates effective use of multithreading and synchronization primitives in C. By carefully managing mutexes and thread interactions, the program avoids common concurrency issues such as deadlocks and race conditions.

The modular structure and adherence to coding standards (like limiting function sizes) ensure maintainability and readability. Each component plays a specific role, contributing to the overall functionality and robustness of the simulation.


