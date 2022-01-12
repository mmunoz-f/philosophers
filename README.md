# philosophers

In this project I learnt the basics of threading. In the main part, the philo folder, I learnt about how threads worked, using mutex to manage the data.

We see the usual <a href="https://en.wikipedia.org/wiki/Dining_philosophers_problem" target="_blank">dining philosophers problem</a>, to resolve it depending on whether the philosopher is an even or odd number it will try to take his right or left fork, this way avoids deadlock.

In the bonus part of the project, all the forks are in the middle of the table, and the objective is to correctly use different processes with <a href="https://man7.org/linux/man-pages/man2/fork.2.html" target="_blank">fork()</a> and semaphores.
