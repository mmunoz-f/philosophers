# philosophers

In this project I learnt the basics of threading. In the main part, the philo folder, I learnt about how threads worked, using mutex to manage the data.

We see the usual <a href="https://en.wikipedia.org/wiki/Dining_philosophers_problem" target="_blank">dining philosophers problem</a>, to resolve it depending on whether the philosopher is an even or odd number it will try to take his right or left fork, this way avoids deadlock.

In the bonus part of the project, all the forks are in the middle of the table, and the objective is to correctly use different processes with <a href="https://man7.org/linux/man-pages/man2/fork.2.html" target="_blank">fork()</a> and semaphores.

After compiling by using `make` you will be able to launch the philo executable. You will have to add a few parameters to start a simulation:

```bash
./philo number_of_philosophers time_to_die time_to_eat time_to_sleep [min_number_of_times_to_eat]
```
```bash
./philo 4 400 200 200
```
This will show a feedback of how the philosophers are doing.
