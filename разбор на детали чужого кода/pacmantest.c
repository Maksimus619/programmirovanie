#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MAX_PLAYERS 4
#define SERVER_PORT 12345
#define WIDTH 20
#define HEIGHT 15
#define FULL_WIDTH (2 * WIDTH)
#define FULL_HEIGHT (2 * HEIGHT)
#define MAX_BUFFER_SIZE 1024
#define PLAYER_TILE 0x22
#define FOOD_TILE 0xAA
#define WALL_TILE 0xFF

typedef struct {
    uint32_t x;
    uint32_t y;
    uint32_t direction;
    uint32_t score;
} Player;

typedef struct {
    uint32_t magic;
    uint32_t ptype;
    uint32_t datasize;
} PacketHeader;

typedef struct {
    int socket;
    Player player;
} ClientData;

typedef struct {
    char map[FULL_HEIGHT][FULL_WIDTH];
    Player players[MAX_PLAYERS];
    int num_players;
    pthread_mutex_t lock;
} GameState;

GameState game_state;

void generate_map() {
    srand(time(NULL));
    char quarter[HEIGHT][WIDTH];
    // Generate a quarter of the map
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            int chance = rand() % 100;
            if (chance < 10) quarter[y][x] = WALL_TILE;
            else if (chance < 90) quarter[y][x] = FOOD_TILE;
            else quarter[y][x] = PLAYER_TILE; // Place player only if within certain conditions
        }
    }
    // Mirror to full map
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            game_state.map[y][x] = game_state.map[y][FULL_WIDTH - x - 1] = game_state.map[FULL_HEIGHT - y - 1][x] = game_state.map[FULL_HEIGHT - y - 1][FULL_WIDTH - x - 1] = quarter[y][x];
        }
    }
}

void init_game(int num_players) {
    generate_map();
    for (int i = 0; i < num_players; i++) {
        // Find random start position for each player
        while (1) {
            int rx = rand() % FULL_WIDTH;
            int ry = rand() % FULL_HEIGHT;
            if (game_state.map[ry][rx] != PLAYER_TILE && game_state.map[ry][rx] != WALL_TILE) {
                game_state.players[i].x = rx;
                game_state.players[i].y = ry;
                game_state.players[i].direction = -1;
                game_state.players[i].score = 0;
                game_state.map[ry][rx] = PLAYER_TILE;
                break;
            }
        }
    }
    game_state.num_players = num_players;
}

void *client_thread(void *arg) {
    ClientData *data = (ClientData *)arg;
    int socket = data->socket;
    Player player = data->player;

    // Example: Send initial game state
    send(socket, game_state.map, sizeof(game_state.map), 0);

    // Thread for receiving data from client
    char buffer[MAX_BUFFER_SIZE];
    while (recv(socket, buffer, sizeof(buffer), 0) > 0) {
        // Process client input
        uint32_t direction;
        memcpy(&direction, buffer, sizeof(direction));
        pthread_mutex_lock(&game_state.lock);
        player.direction = ntohl(direction);
        pthread_mutex_unlock(&game_state.lock);
    }

    close(socket);
    return NULL;
}

int main(int argc, char *argv[]) {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in address = {
        .sin_family = AF_INET,
        .sin_addr.s_addr = INADDR_ANY,
        .sin_port = htons(SERVER_PORT)
    };
    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, MAX_PLAYERS);

    pthread_t threads[MAX_PLAYERS];
    ClientData clients[MAX_PLAYERS];
    init_game(MAX_PLAYERS);

    for (int i = 0; i < MAX_PLAYERS; i++) {
        int client_socket = accept(server_fd, NULL, NULL);
        clients[i] = (ClientData){ .socket = client_socket, .player = game_state.players[i] };
        pthread_create(&threads[i], NULL, client_thread, &clients[i]);
    }

    for (int i = 0; i < MAX_PLAYERS; i++) {
        pthread_join(threads[i], NULL);
    }

    close(server_fd);
    return 0;
}
