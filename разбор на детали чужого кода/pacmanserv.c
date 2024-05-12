#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ncurses.h>
#include <errno.h>

#define WIDTH 20
#define HEIGHT 15
#define FULL_WIDTH (2 * WIDTH)
#define FULL_HEIGHT (2 * HEIGHT)
#define MAX_PLAYERS 4
#define SERVER_PORT 12345

enum tile { EMPTY = ' ', WALL = 'X', FOOD = '.', PLAYER = '?' };
enum direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

typedef struct {
    int x, y;
    enum direction dir;
    int score;
} Player;

typedef struct {
    int socket;
    Player players[MAX_PLAYERS];
    char map[FULL_HEIGHT][FULL_WIDTH];
} GameState;

GameState game_state;

// Function to initialize game map and players
void init_game() {
    memset(game_state.map, EMPTY, sizeof(game_state.map));
    // Simulated map initialization and players setup...
}

// Thread function for handling each client
void *client_handler(void *arg) {
    int sock = *(int *)arg;
    char buffer[1024];
    int read_size;

    while ((read_size = recv(sock, buffer, sizeof(buffer), 0)) > 0) {
        // Process received data from client
    }

    if (read_size == 0) {
        puts("Client disconnected");
        fflush(stdout);
    } else if (read_size == -1) {
        perror("recv failed");
    }

    close(sock);
    return 0;
}

int main(int argc, char *argv[]) {
    int socket_desc, client_sock, c;
    struct sockaddr_in server, client;

    // Create socket
    socket_desc = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_desc == -1) {
        printf("Could not create socket");
    }
    puts("Socket created");

    // Prepare the sockaddr_in structure
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(SERVER_PORT);

    // Bind
    if (bind(socket_desc, (struct sockaddr *)&server, sizeof(server)) < 0) {
        perror("bind failed. Error");
        return 1;
    }
    puts("bind done");

    // Listen
    listen(socket_desc, 3);

    // Accept and incoming connection
    puts("Waiting for incoming connections...");
    c = sizeof(struct sockaddr_in);
    pthread_t thread_id;

    while ((client_sock = accept(socket_desc, (struct sockaddr *)&client, (socklen_t *)&c))) {
        puts("Connection accepted");

        if (pthread_create(&thread_id, NULL, client_handler, (void *)&client_sock) < 0) {
            perror("could not create thread");
            return 1;
        }

        puts("Handler assigned");
    }

    if (client_sock < 0) {
        perror("accept failed");
        return 1;
    }

    return 0;
}
