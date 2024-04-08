#include "minishell.h"


// void pipes(t_mini *shell) {
//     t_cmd *cmd;
//     int fds[2];
//     pid_t pid;
//     pid_t prev_pid = -1;

//     // Loop through all commands in the pipeline
//     while (shell->current_cmd) {
//         cmd = (t_cmd *) shell->current_cmd;

//         // Create a pipe
//         if (pipe(fds) == -1) {
//             perror("pipe");
//             exit(EXIT_FAILURE);
//         }

//         // Fork a child process
//         pid = fork();
//         if (pid == -1) {
//             perror("fork");
//             exit(EXIT_FAILURE);
//         } else if (pid == 0) { // Child process
//             // If it's not the first command, set input to the previous command's output
//             if (prev_pid != -1) {
//                 dup2(fds[0], STDIN_FILENO); // Redirect stdin to the input of this command
//                 close(fds[1]); // Close unused write end
//             }
//             // If it's not the last command, set output to the pipe
//             if (shell->current_cmd->next) {
//                 dup2(fds[1], STDOUT_FILENO); // Redirect stdout to the output of this command
//             }
//             // Close all pipe ends
//             close(fds[0]);
//             close(fds[1]);

//             // Execute the command
//             execve(cmd->argv[0], cmd->argv, shell->env);
//             perror("execve");
//             exit(EXIT_FAILURE);
//         } else { // Parent process
//             // Close read end of the pipe if it's not the last command
//             if (shell->current_cmd->next) {
//                 close(fds[1]);
//             }
//             // Wait for the child process to finish
//             waitpid(pid, NULL, 0);
//         }

//         // Move to the next command
//         shell->current_cmd = shell->current_cmd->next;
//         prev_pid = pid;
//     }
// }

int main() {
    // Example usage
    t_mini shell;
    // Assume shell.current_cmd is properly initialized with a linked list of commands
    pipes(&shell);
    return 0;
}