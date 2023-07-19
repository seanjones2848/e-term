// #include <signal.h>
// #include <stdlib.h>
// #include <sysexits.h>
// #include <unistd.h>
// #include <util.h>

// pid_t child = 0;

// void sighandler(int signum) {
//   if (child > 0) {
//     killpg(child, signum);
//     exit(signum);
//   }
// }

// // Run a command in a pty.
// // Usage: /path/to/this/binary command to run
// int main(int argc, char *argv[]) {
//   if (argc < 2) {
//     return EX_USAGE;
//   }

//   int master;
//   child = forkpty(&master, NULL, NULL, NULL);

//   if (child == -1) {
//     perror("failed to fork pty");
//     return EX_OSERR;
//   }

//   if (child == 0) {
//     // we're in the child process, so replace it with the command
//     execvp(argv[1], argv + 1);
//     perror("failed to execute command");
//     return EX_OSERR;
//   }

//   // trap kill signals and forward them to child process
//   signal(SIGHUP, sighandler);
//   signal(SIGINT, sighandler);
//   signal(SIGTERM, sighandler);

//   const int buf_size = 1024;
//   char buf[buf_size];
//   fd_set fds;
//   ssize_t bytes_read;

//   // forward the output continuously
//   while (1) {
//     FD_ZERO(&fds);
//     FD_SET(master, &fds);

//     if (select(master + 1, &fds, NULL, NULL, NULL) > 0 && FD_ISSET(master, &fds)) {
//       bytes_read = read(master, buf, buf_size);
//       if (bytes_read <= 0) {
//         return EXIT_SUCCESS;
//       }

//       if (write(STDOUT_FILENO, buf, bytes_read) != bytes_read) {
//         perror("failed to write to stdout");
//         return EX_OSERR;
//       }
//     }
//   }
// }
