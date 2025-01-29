#include <stdio.h>
#include <stdlib.h> // Include stdlib.h for malloc
#include <string.h> // Include string.h for sprintf
#include <stdbool.h> 
#include "API.h"


void logm(char* text) {
    fprintf(stderr, "%s\n", text);
    fflush(stderr);
}

#define MAX_QUEUE_SIZE 100

typedef struct {
    int r;
    int c;
    int val;
    int walls[4]; // 0 = north, 1 = south, 2 = east, 3 = west
} Square;

typedef struct {
    Square data[MAX_QUEUE_SIZE];
    int front;
    int rear;
    int size;
} Queue;
//test gvuig
//jvv
Square map[16][16];
Queue q;

bool isQueueEmpty() {
    return q.size == 0;
}

bool isQueueFull() {
    return q.size == MAX_QUEUE_SIZE;
}

void enqueue(Square s) {
    if (isQueueFull()) {
        printf("Queue is full!\n");
        return;
    }
    q.rear = (q.rear + 1) % MAX_QUEUE_SIZE;
    q.data[q.rear] = s;
    q.size++;
}

Square dequeue() {
    Square s = {0, 0, 0, {0, 0, 0, 0}};
    if (isQueueEmpty()) {
        printf("Queue is empty!\n");
        return s;
    }
    s = q.data[q.front];
    q.front = (q.front + 1) % MAX_QUEUE_SIZE;
    q.size--;
    return s;
}

char* intToString(int num) {
    char* str = (char*)malloc(11 * sizeof(char));
    if (str != NULL) {
        sprintf(str, "%d", num);
    }
    return str;
}

// check neightbors
void checkN(Square s) { 
    if (s.walls[0] == 0 && s.r > 0) { // nort
        if (map[s.r - 1][s.c].val > s.val + 1) {
            map[s.r - 1][s.c].val = s.val + 1;
            enqueue(map[s.r - 1][s.c]);
            char* valStr = intToString(s.val + 1);
            API_setText(s.c, s.r - 1, valStr);
            free(valStr);
        }
    }
    if (s.walls[1] == 0 && s.r < 15) { // south
        if (map[s.r + 1][s.c].val > s.val + 1) {
            map[s.r + 1][s.c].val = s.val + 1;
            enqueue(map[s.r + 1][s.c]);
            char* valStr = intToString(s.val + 1);
            API_setText(s.c, s.r + 1, valStr);
            free(valStr);
        }
    }
    if (s.walls[2] == 0 && s.c < 15) { //east
        if (map[s.r][s.c + 1].val > s.val + 1) {
            map[s.r][s.c + 1].val = s.val + 1;
            enqueue(map[s.r][s.c + 1]);
            char* valStr = intToString(s.val + 1);
            API_setText(s.c + 1, s.r, valStr);
            free(valStr);
        }
    }
    if (s.walls[3] == 0 && s.c > 0) { //west
        if (map[s.r][s.c - 1].val > s.val + 1) {
            map[s.r][s.c - 1].val = s.val + 1;
            enqueue(map[s.r][s.c - 1]);
            char* valStr = intToString(s.val + 1);
            API_setText(s.c - 1, s.r, valStr);
            free(valStr);
        }
    }
}


void floodFill(){
    while (!isQueueEmpty()) {
        Square s = dequeue();
        checkN(s);
    }
}

int main() {
    //initialize queue
    q.front = 0;
    q.rear = -1;
    q.size = 0;
    //initialize map
    for (int col = 0; col < 16; col++) {
        for (int row = 15; row >= 0; row--) {
            Square s = {.r = row, .c = col, .val = 2000, .walls = {0, 0, 0, 0}};
            if (col == 0) {
                s.walls[3] = 1;
                API_setWall(col, row, 'w');
            }
            if (col == 15) {
                s.walls[2] = 1;
                API_setWall(col, row, 'e');
            }
            if (row == 0) {
                s.walls[1] = 1;
                API_setWall(col, row, 's');
            }
            if (row == 15) {
                s.walls[0] = 1;
                API_setWall(col, row, 'n');
            }
            char* valStr = intToString(s.val);
            API_setText(s.c, s.r, valStr);
            free(valStr);
            map[s.c][s.r] = s;
        }
    }

    //initializes 4 center squares
    Square botL = {.r = 7, .c = 7, .val = 0, .walls = {0, 0, 0, 0}};
    map[botL.c][botL.r] = botL;
    char* valStr1 = intToString(botL.val);
    API_setText(botL.c, botL.r, valStr1);
    free(valStr1);
    enqueue(botL);

    Square botR = {.r = 7, .c = 8, .val = 0, .walls = {0, 0, 0, 0}};
    map[botR.c][botR.r] = botR;
    char* valStr2 = intToString(botR.val);
    API_setText(botR.c, botR.r, valStr2);
    free(valStr2);
    enqueue(botR);

    Square topR = {.r = 8, .c = 8, .val = 0, .walls = {0, 0, 0, 0}};
    map[topR.c][topR.r] = topR;
    char* valStr3 = intToString(topR.val);
    API_setText(topR.c, topR.r, valStr3);
    free(valStr3);
    enqueue(topR);

    Square topL = {.r = 8, .c = 7, .val = 0, .walls = {0, 0, 0, 0}};
    map[topL.c][topL.r] = topL;
    char* valStr4 = intToString(topL.val);
    API_setText(topL.c, topL.r, valStr4);
    free(valStr4);
    enqueue(topL);

    
    // Set walls for testing within the map array and visually using API_setWall
    //floodFill();
   // Add walls at (5, 5): north and east
   map[5][5].walls[0] = 1; // North wall
   map[5][5].walls[2] = 1; // East wall
   API_setWall(5, 5, 'n');
   API_setWall(5, 5, 'e');

   // Add wall at (7, 7): west
   map[7][7].walls[3] = 1; // West wall
   API_setWall(7, 7, 'w');

   // Add walls at (10, 8): south and east
   map[10][8].walls[1] = 1; // South wall
   map[10][8].walls[2] = 1; // East wall
   API_setWall(10, 8, 's');
   API_setWall(10, 8, 'e');

   // Add walls at (3, 12): west and north
   map[3][12].walls[3] = 1; // West wall
   map[3][12].walls[0] = 1; // North wall
   API_setWall(3, 12, 'w');
   API_setWall(3, 12, 'n');
    floodFill();

    return 0;
}