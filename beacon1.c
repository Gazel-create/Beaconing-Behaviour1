#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>

int main() {
    int sock;
    struct sockaddr_in server_addr;
    struct timespec req;

    // Define the sleep duration (e.g., 5 seconds)
    req.tv_sec = 5;      // Seconds
    req.tv_nsec = 0;     // Nanoseconds

    printf("Starting custom beacon heartbeat...\n");

    while(1) {
        // 1. Create the socket (This will get a File Descriptor, usually 3)
        sock = socket(AF_INET, SOCK_STREAM, 0);
        if (sock < 0) {
            perror("Socket creation failed");
            exit(1);
        }

        // 2. Setup the destination IP and Port
        server_addr.sin_family = AF_INET;
        server_addr.sin_port = htons(4444); // The port to connect to
        inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr); // The IP

        // 3. Fire the 'connect' syscall
        // Even if it fails (Connection refused), the syscall still executes and can be traced!
        connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr));

        // Close the socket so we don't run out of file descriptors
        close(sock);

        // 4. Fire the 'nanosleep' syscall to pause the program
        nanosleep(&req, NULL);
    }

    return 0;
}
