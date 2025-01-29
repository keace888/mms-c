#include <stdio.h>
#include <stdlib.h> // Include stdlib.h for malloc
#include <string.h> // Include string.h for sprintf
#include <stdbool.h> 
#include <limits.h>
#include "API.h"


void logm(char* text) {
    fprintf(stderr, "%s\n", text);
    fflush(stderr);
}

#define MAX_QUEUE_SIZE 1000

typedef struct {
    int r;
    int c;
    int val;
    int walls[4]; // 0 = north, 1 = south, 2 = east, 3 = west
    int visits;
    int val_b;
} Square;

typedef struct {
    Square data[MAX_QUEUE_SIZE];
    int front;
    int rear;
    int size;
} Queue;

typedef struct {
    int row;
    int col;
    int oriention;
} Rat;

Rat pikachu; // fast asffff boiiiiiiiiii
Square map[16][16]; // starts off top left, api starts bottom left
Queue q1;
Queue q2;


bool isQueueEmpty(Queue q) {
    return q.size == 0;
}

bool isQueueFull(Queue q) {
    return q.size == MAX_QUEUE_SIZE;
}

void enqueue(Square s, Queue q) {
    if (isQueueFull(q)) {
        printf("Queue is full!\n");
        return;
    }
    q.rear = (q.rear + 1) % MAX_QUEUE_SIZE;
    q.data[q.rear] = s;
    q.size++;
}

Square dequeue(Queue q) {
    Square s = {0, 0, 0, {0, 0, 0, 0}};
    if (isQueueEmpty(q)) {
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
void checkN(Square s, bool to) { 
    if(to){ // if going to the center use q1
        if (map[s.r][s.c].walls[0] == 0) { // if there isnt a wall north
        //enqueue(map[s.r - 1][s.c]);
            if (map[s.r - 1][s.c].val > s.val + 1) { // if the upper square's value > my square's value + 1
                map[s.r - 1][s.c].val = s.val + 1; // set upper square's value to my square's value + 1
                enqueue(map[s.r - 1][s.c], q1); // add upper square to queue 
                char* valStr = intToString(s.val + 1);
                API_setText(s.c, 15 - (s.r - 1), valStr); // diplay square in map
                free(valStr);
            }
        }
        if (map[s.r][s.c].walls[1] == 0) { // south
            //enqueue(map[s.r + 1][s.c]);
            if (map[s.r + 1][s.c].val > s.val + 1) {
                map[s.r + 1][s.c].val = s.val + 1;
                enqueue(map[s.r + 1][s.c], q1);
                char* valStr = intToString(map[s.r + 1][s.c].val);
                API_setText(s.c, 15 - (s.r + 1), valStr);
                free(valStr);
            }
        }
        if (map[s.r][s.c].walls[2] == 0) { // if there isnt a wall east
            //enqueue(map[s.r][s.c + 1]);
            if (map[s.r][s.c + 1].val > s.val + 1) { // if the cell to my right has a value greater than mine +1
                map[s.r][s.c + 1].val = s.val + 1; // set the right square's value to mine + 1
                enqueue(map[s.r][s.c + 1], q1); // add it to the queue
                char* valStr = intToString(s.val + 1);
                API_setText(s.c + 1, 15 - s.r, valStr); // display it on the map
                free(valStr);
            }
        }
        if (map[s.r][s.c].walls[3] == 0) { //west
            if (map[s.r][s.c - 1].val > s.val + 1) {
                map[s.r][s.c - 1].val = s.val + 1;
                enqueue(map[s.r][s.c - 1], q1);
                char* valStr = intToString(s.val + 1);
                API_setText(s.c - 1, 15 - s.r, valStr);
                free(valStr);
            }
        }
    }
    else{
        if (map[s.r][s.c].walls[0] == 0) { // if there isnt a wall north
            //enqueue(map[s.r - 1][s.c]);
            if (map[s.r - 1][s.c].val_b > s.val_b + 1) { // if the upper square's value > my square's value + 1
                map[s.r - 1][s.c].val_b = s.val_b + 1; // set upper square's value to my square's value + 1
                enqueue(map[s.r - 1][s.c], q2); // add upper square to queue 
                char* valStr = intToString(s.val_b + 1);
                API_setText(s.c, 15 - (s.r - 1), valStr); // diplay square in map
                free(valStr);
            }
        }
        if (map[s.r][s.c].walls[1] == 0) { // south
            //enqueue(map[s.r + 1][s.c]);
            if (map[s.r + 1][s.c].val_b > s.val_b + 1) {
                map[s.r + 1][s.c].val_b = s.val_b + 1;
                enqueue(map[s.r + 1][s.c], q2);
                char* valStr = intToString(map[s.r + 1][s.c].val_b);
                API_setText(s.c, 15 - (s.r + 1), valStr);
                free(valStr);
            }
        }
        if (map[s.r][s.c].walls[2] == 0) { // if there isnt a wall east
            //enqueue(map[s.r][s.c + 1]);
            if (map[s.r][s.c + 1].val_b > s.val_b + 1) { // if the cell to my right has a value greater than mine +1
                map[s.r][s.c + 1].val_b = s.val_b + 1; // set the right square's value to mine + 1
                enqueue(map[s.r][s.c + 1], q2); // add it to the queue
                char* valStr = intToString(s.val_b + 1);
                API_setText(s.c + 1, 15 - s.r, valStr); // display it on the map
                free(valStr);
            }
        }
        if (map[s.r][s.c].walls[3] == 0) { //west
            if (map[s.r][s.c - 1].val_b > s.val_b + 1) {
                map[s.r][s.c - 1].val_b = s.val_b + 1;
                enqueue(map[s.r][s.c - 1], q2);
                char* valStr = intToString(s.val_b + 1);
                API_setText(s.c - 1, 15 - s.r, valStr);
                free(valStr);
            }
        }
    }
}

void makeSquare(int row, int col, int val, int pared[4], int val_b){
    map[row][col].r = row;
    map[row][col].c = col;
    map[row][col].val = val;
    map[row][col].val_b = val_b;
    for(int i = 0; i < 4; i++){
        map[row][col].walls[i] = pared[i];
    }
    API_setText(map[row][col].c, 15 - map[row][col].r, intToString(map[row][col].val));
}

void addWall(int row, int col, int dir) {
    map[row][col].walls[dir] = 1;

    // Update the corresponding wall in the adjacent square
    if (dir == 0 && row > 0) { // North wall
        map[row - 1][col].walls[1] = 1; // Set the south wall of the square above
    } 
    else if (dir == 1 && row < 15) { // South wall
        map[row + 1][col].walls[0] = 1; // Set the north wall of the square below
    } 
    else if (dir == 2 && col < 15) { // East wall
        map[row][col + 1].walls[3] = 1; // Set the west wall of the square to the right
    } 
    else if (dir == 3 && col > 0) { // West wall
        map[row][col - 1].walls[2] = 1; // Set the east wall of the square to the left
    }

    // Use the API to display the wall in the visualizer
    if (dir == 0) {
        API_setWall(map[row][col].c, 15 - map[row][col].r, 'n');
    } 
    else if (dir == 1) {
        API_setWall(map[row][col].c, 15 - map[row][col].r, 's');
    } 
    else if (dir == 2) {
        API_setWall(map[row][col].c, 15 - map[row][col].r, 'e');
    } 
    else if (dir == 3) {
        API_setWall(map[row][col].c, 15 - map[row][col].r, 'w');
    }
}

void restart(){   // floodfill only works fresh, so restart
    makeSquare(7,7,0, map[7][7].walls, 2000); // top left
    enqueue(map[7][7], q1);

    makeSquare(7,8,0, map[7][8].walls, 2000); // top right
    enqueue(map[7][8], q1);

    makeSquare(8,7,0, map[8][7].walls, 2000);// bottom left
    enqueue(map[8][7], q1);
     
    makeSquare(8,8,0,map[8][8].walls, 2000); // bottom right
    enqueue(map[8][8], q1);

    makeSquare(15,0,2000,map[15][0].walls, 0);
    enqueue(map[15][0], q2);
    for (int col = 0; col < 16; col++) {
        for (int row = 15; row >= 0; row--) {
            if(row == 7 && col == 7){

            }
            else if(row ==7 && col == 8){

            }
            else if(row == 8 && col == 7){

            }
            else if(row == 8 && col == 8){
                
            }
            else{
                makeSquare(row, col, 2000, map[row][col].walls, 2000);
            }
        }
    }
}
// true for going false for returning
void floodFill(Queue q, bool to){
    while (!isQueueEmpty(q)) {
        Square s = dequeue(q);
        checkN(map[s.r][s.c], to);
    }
}

void mouseWalls(Queue q, bool to){ 
    if(API_wallFront()){
        addWall(pikachu.row, pikachu.col, pikachu.oriention);
    }
    if(API_wallRight()){
        if(pikachu.oriention == 0){ // if facing north 
            addWall(pikachu.row,pikachu.col,2); // place wall east
        }
        else if(pikachu.oriention == 1){
            addWall(pikachu.row,pikachu.col,3);
        }
        else if(pikachu.oriention == 2){
            addWall(pikachu.row,pikachu.col,1);
        }
        else if(pikachu.oriention == 3){
            addWall(pikachu.row,pikachu.col,0);
        }
    }
    if(API_wallLeft()){
        if(pikachu.oriention == 0){ // if facing north 
            addWall(pikachu.row,pikachu.col,3); // place wall west
        }
        else if(pikachu.oriention == 1){
            addWall(pikachu.row,pikachu.col,2);
        }
        else if(pikachu.oriention == 2){
            addWall(pikachu.row,pikachu.col,0);
        }
        else if(pikachu.oriention == 3){
            addWall(pikachu.row,pikachu.col,1);
        }
    }
    //map[pikachu.row][pikachu.col].visits++;
    restart();
    floodFill(q, to);
}

void ratMove(int destination){
    if(destination == pikachu.oriention){
        API_moveForward();
        if(destination == 0){
            pikachu.row--;
        }
        if(destination == 1){
            pikachu.row++;
        }
        if(destination == 2){
            pikachu.col++;
        }
        if(destination == 3){
            pikachu.col--;
        }
    }
    else{
        if(destination == 0){
            if(pikachu.oriention == 3){ // if facing west turn north
                    API_turnRight();
                }
                if(pikachu.oriention == 2){ // if facing east turn north
                    API_turnLeft();
                }
                if(pikachu.oriention == 1){ // if facing south turn north
                    API_turnLeft();
                    API_turnLeft();
                }
                pikachu.oriention = 0;
                pikachu.row--;
        }
        if (destination == 1){
            if(pikachu.oriention == 3){ // if facing west turn south
                    API_turnLeft();
                }
                if(pikachu.oriention == 2){ // if facing east turn south
                    API_turnRight();
                }
                if(pikachu.oriention == 0){ // if facing north turn south
                    API_turnLeft();
                    API_turnLeft();
                }
                pikachu.oriention = 1;
                pikachu.row++;
        }
        if(destination == 2){
            if(pikachu.oriention == 3){ // if facing west turn east
                    API_turnLeft();
                    API_turnLeft();
                }
                if(pikachu.oriention == 0){ // if facing north turn east
                    API_turnRight();
                }
                if(pikachu.oriention == 1){ // if facing south turn east
                    API_turnLeft();
                }
                pikachu.oriention = 2; //set orientation to east
                pikachu.col++;
        }
        if(destination == 3){
            if(pikachu.oriention == 2){ // if facing west turn east
                    API_turnRight();
                    API_turnRight();
                }
                if(pikachu.oriention == 0){ // if facing north turn west
                    API_turnLeft();
                }
                if(pikachu.oriention == 1){ // if facing south turn west
                    API_turnRight();
                }
                pikachu.oriention = 3;
                pikachu.col--;
        }
        API_moveForward();
    }
    map[pikachu.row][pikachu.col].visits++;
}

void ratNeighbors(Square s, Queue q, bool to){
    mouseWalls(q, to);
    if(to){
        if(map[s.r][s.c].walls[0] != 1){ // if there isnt a wall north
            if(map[s.r][s.c].val > map[s.r-1][s.c].val){   // if the northern square has a lower cost
                ratMove(0); //move north
                return;
            }
        }
        if(map[s.r][s.c].walls[1] != 1){ // if there isnt a wall south
            if(map[s.r][s.c].val > map[s.r+1][s.c].val){   // if the southern square has a lower cost
                ratMove(1); // move south
                return;
            }
        }

        if(map[s.r][s.c].walls[2] != 1){ // if there isnt a wall east
            if(map[s.r][s.c].val > map[s.r][s.c+1].val){   // if the eastern square has a lower cost
                ratMove(2); // move east
                return;
            }
        }

        if(map[s.r][s.c].walls[3] != 1){ // if there isnt a wall west
            if(map[s.r][s.c].val > map[s.r][s.c-1].val){   // if the western square has a lower cost
                ratMove(3); // move west
                return;
            }
        }
    }
    else{
        if(map[s.r][s.c].walls[0] != 1){ // if there isnt a wall north
            if(map[s.r][s.c].val > map[s.r-1][s.c].val){   // if the northern square has a lower cost
                ratMove(0); //move north
                return;
            }
        }

        if(map[s.r][s.c].walls[1] != 1){ // if there isnt a wall south
            if(map[s.r][s.c].val > map[s.r+1][s.c].val){   // if the southern square has a lower cost
                ratMove(1); // move south
                return;
            }
        }

        if(map[s.r][s.c].walls[2] != 1){ // if there isnt a wall east
            if(map[s.r][s.c].val > map[s.r][s.c+1].val){   // if the eastern square has a lower cost
                ratMove(2); // move east
                return;
            }
        }

        if(map[s.r][s.c].walls[3] != 1){ // if there isnt a wall west
            if(map[s.r][s.c].val > map[s.r][s.c-1].val){   // if the western square has a lower cost
                ratMove(3); // move west
                return;
            }
        }
    }
}

void checkVisits(Square s){
    if(map[s.r][s.c].visits == 1){ // first time visit
        API_setColor(map[s.r][s.c].c, 15 - map[s.r][s.c].r, 'G');
    }
    else if(map[s.r][s.c].visits == 2){ // second time visit
        API_setColor(map[s.r][s.c].c, 15 - map[s.r][s.c].r, 'Y');
    }
    if(map[s.r][s.c].visits == 3){ // third time visit
        API_setColor(map[s.r][s.c].c, 15 - map[s.r][s.c].r, 'R');
    }
}


int main() {
    //initialize queue
    q1.front = 0;
    q1.rear = -1;
    q1.size = 0;
    q2.front = 0;
    q2.rear = -1;
    q2.size = 0;
    //initialize map              
    for (int col = 0; col < 16; col++) {
        for (int row = 15; row >= 0; row--) {
            int walls[4] = {0,0,0,0};
            makeSquare(row, col, 2000, walls, 2000);
            map[row][col].visits = 0;
            if(col == 0){
                addWall(row, col, 3);
            }
            if(col == 15){
                addWall(row, col, 2);
            }
            if(row == 0){
                addWall(row, col, 0);
            }
            if(row == 15){
                addWall(row, col, 1);
            }
        }
    }

    
    int w[4] = {0,0,0,0}; // no walls
    
    makeSquare(7,7,0, w, 2000); // top left
    enqueue(map[7][7], q1);

    makeSquare(7,8,0, w, 2000); // top right
    enqueue(map[7][8], q1);

    makeSquare(8,7,0, w, 2000);// bottom left
    enqueue(map[8][7], q1);
     
    makeSquare(8,8,0,w, 2000); // bottom right
    enqueue(map[8][8], q1);
    
    int w2[4] = {0,1,0,1}; // bottom left has walls west and south
    makeSquare(15,0,2000,w2,0);
    enqueue(map[15][0], q2);
    //floodFill();
    pikachu.row = 15;
    pikachu.col = 0;
    pikachu.oriention = 0;// start mouse at bottom left square facing north
    map[15][0].visits = 1;
    //while(1){
    //    ratExplore(map[15][0]);
    //}
    
    checkVisits(map[pikachu.row][pikachu.col]);
    while(map[pikachu.row][pikachu.col].val != 0){
        ratNeighbors(map[pikachu.row][pikachu.col],q1, true);
        checkVisits(map[pikachu.row][pikachu.col]);
    }
    
    int i = 5;
    while(pikachu.col != 0 || pikachu.row != 15){
        ratNeighbors(map[pikachu.row][pikachu.col],q2, false);
        checkVisits(map[pikachu.row][pikachu.col]);
    }

    return 0;
}

