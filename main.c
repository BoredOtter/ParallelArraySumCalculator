#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <ncurses.h>

int main() {
    int i, j, n;
    int suma = 0;
    int pid;

    initscr();
    start_color();

    init_pair(1, COLOR_GREEN, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_BLUE, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);

    clear();
    int row, col;
    getmaxyx(stdscr, row, col);

    attron(COLOR_PAIR(3));
    mvprintw(0, (col - 67) / 2, "Program calculating the sum of array elements in separate processes\n");
    attroff(COLOR_PAIR(3));

    mvprintw(1, (col - 30) / 2, "Enter the size of the array: ");
    scanw("%d", &n);
    int **A = (int **)malloc(n * sizeof(int *));

    for (int i = 0; i < n; i++) {
        A[i] = (int *)malloc(n * sizeof(int));
    }

    // Getting values of array elements from the user
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            mvprintw(4, (col - 30) / 2, "Enter the element (%d, %d) of the array: ", i + 1, j + 1);
            scanw("%d", &A[i][j]);
        }
    }
    clear();
    refresh();

    attron(COLOR_PAIR(3));
    mvprintw(0, (col - 67) / 2, "Program calculating the sum of array elements in separate processes\n");
    attroff(COLOR_PAIR(3));

    attron(COLOR_PAIR(1));
    mvprintw(n + 5, (col - 30) / 2, "Input array:\n");
    attroff(COLOR_PAIR(1));

    for (int i = 0; i < n; i++) {
        printw("Row %d: ", i);
        for (int j = 0; j < n; j++) {
            attron(COLOR_PAIR(1));
            printw("%d ", A[i][j]);
            attroff(COLOR_PAIR(1));
        }
        printw("\n");
    }
    
    // Creating n child processes
    for (i = 0; i < n; i++) {
        pid = fork(); // Creating a child process
        if (pid == 0) {
            // If it is a child process
            int suma_wiersza = 0;
            for (j = 0; j < n; j++) {
                suma_wiersza += A[i][j];
            }
            exit(suma_wiersza); // Returning partial sum
        }
    }

    for (i = 0; i < n; i++) {
        int suma_wiersza;
        wait(&suma_wiersza);
        // WEXITSTATUS allows obtaining the value returned by the child process upon its termination
        suma += WEXITSTATUS(suma_wiersza); // Calculating the total sum
    }

    attron(COLOR_PAIR(1));
    mvprintw(2, (col - 30) / 2, "Sum of array elements: ");
    attroff(COLOR_PAIR(1));

    attron(COLOR_PAIR(2));
    printw("%d\n", suma);
    attroff(COLOR_PAIR(2));

    for (int i = 0; i < n; i++) {
        int suma_wiersza = 0;
        for (int j = 0; j < n; j++) {
            suma_wiersza += A[i][j];
        }
        printw("Sum of row %d: ", i + 1);
        attron(COLOR_PAIR(1));
        printw("%d\n", suma_wiersza);
        attroff(COLOR_PAIR(1));
    }

    refresh();
    attron(COLOR_PAIR(4));
    mvprintw(1, (col - 46) / 2, "Press any key to exit the program");
    attroff(COLOR_PAIR(4));
    getch();
    endwin();
    return 0;
}
