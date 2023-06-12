This program calculates the sum of array elements using separate child processes in parallel. It is designed to run on the Linux operating system and demonstrates the concept of parallel processing.

The program utilizes the following libraries: `stdio.h`, `stdlib.h`, `unistd.h`, `sys/wait.h`, and `ncurses.h`.

Key Features:

-   Creates a square array based on user-defined size.
-   Spawns separate child processes to calculate the sum of each row in parallel.
-   Uses the `ncurses` library for interactive console output.

How It Works:

1.  The program initializes necessary variables, including the array size (`n`), a variable for storing the total sum (`suma`), and a variable for the process ID (`pid`).
2.  It prompts the user to enter the size of the square array.
3.  Dynamic memory allocation is performed to create a 2D array based on the user-defined size.
4.  The program prompts the user to input the values for each element of the array.
5.  The array is displayed on the console.
6.  Child Process Creation: The program forks `n` child processes, each responsible for calculating the sum of a row in the array.
7.  Each child process iterates over the corresponding row and calculates the sum.
8.  The child process exits and returns the partial sum to the parent process.
9.  The parent process waits for each child process to complete and retrieves their partial sums using `wait()` and `WEXITSTATUS()`.
10.  The parent process calculates the total sum by adding up the partial sums.
11.  The total sum and the sum for each row are displayed on the console using `ncurses`.
12.  The program waits for user input and exits.

Note: This code is specifically written for the Linux operating system and may not be directly compatible with other operating systems due to the use of Linux-specific libraries.