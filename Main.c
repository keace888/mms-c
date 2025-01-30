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
    int parallel;
    int walls[4]; // 0 = north, 1 = south, 2 = east, 3 = west
    int visits;
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

typedef struct {
    int oriention;
    int value;
    int visits;
} AS; // accessible square

Rat pikachu; // fast asffff boiiiiiiiiii
Square map[16][16]; // starts off top left, api starts bottom left
Queue q;
Queue q2;


bool isQueueEmpty2() {

    //start of test
    fprintf(stderr,"I am in isQueueuEmpty2()");
    //end of test

    return q2.size == 0;
}

bool isQueueFull2() {

    //start of test
    fprintf(stderr,"I am in isQueueuFull2()");
    //end of test

    return q2.size == MAX_QUEUE_SIZE;
}




bool isQueueEmpty() {

    //start of test
    //fprintf(stderr,"I am in isQueueuEmpty()");
    //end of test

    return q.size == 0;
}

bool isQueueFull() {

    //start of test
    //fprintf(stderr,"I am in isQueueuFull()");
    //end of test

    return q.size == MAX_QUEUE_SIZE;
}

void enqueue(Square s) {

    //start of test
    //fprintf(stderr,"I am in enqueue()");
    //end of test

    if (isQueueFull()) {
        printf("Queue is full!\n");
        return;
    }
    q.rear = (q.rear + 1) % MAX_QUEUE_SIZE;
    q.data[q.rear] = s;
    q.size++;
}

void enqueue2(Square s) {

    //start of test
    //fprintf(stderr,"I am in enqueue2()\n");
    //end of test

    if (isQueueFull2()) {
        printf("Queue is full!\n");
        return;
    }
    q2.rear = (q2.rear + 1) % MAX_QUEUE_SIZE;
    q2.data[q2.rear] = s;
    q2.size++;

    //testing
    //end of test

}

Square dequeue2() {

    //start of test
    fprintf(stderr,"I am in dequeue2()");
    //end of test


    Square s = {0, 0, 0, 0,{0, 0, 0, 0}};
    if (isQueueEmpty2()) {
        printf("Queue is empty!\n");
        return s;
    }
    s = q2.data[q2.front];
    q2.front = (q2.front + 1) % MAX_QUEUE_SIZE;
    q2.size--;
    return s;
}





Square dequeue() {

    //start of test
    //fprintf(stderr,"I am in dequeue()");
    //end of test


    Square s = {0, 0, 0, 0,{0, 0, 0, 0}};
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

    //start of test
    //fprintf(stderr,"I am in intToString()");
    //end of test


    char* str = (char*)malloc(11 * sizeof(char));
    if (str != NULL) {
        sprintf(str, "%d", num);
    }
    return str;
}

// check neightbors
void checkN(Square s) { 

    //start of test
    //fprintf(stderr,"I am in checkN()");
    //end of test

    if (map[s.r][s.c].walls[0] == 0) { // if there isnt a wall north
        //enqueue(map[s.r - 1][s.c]);
        if (map[s.r - 1][s.c].val > s.val + 1) { // if the upper square's value > my square's value + 1
            map[s.r - 1][s.c].val = s.val + 1; // set upper square's value to my square's value + 1
            enqueue(map[s.r - 1][s.c]); // add upper square to queue 
            char* valStr = intToString(s.val + 1);
            API_setText(s.c, 15 - (s.r - 1), valStr); // diplay square in map
            free(valStr);
        }
    }
    if (map[s.r][s.c].walls[1] == 0) { // south
        //enqueue(map[s.r + 1][s.c]);
        if (map[s.r + 1][s.c].val > s.val + 1) {
            map[s.r + 1][s.c].val = s.val + 1;
            enqueue(map[s.r + 1][s.c]);
            char* valStr = intToString(map[s.r + 1][s.c].val);
            API_setText(s.c, 15 - (s.r + 1), valStr);
            free(valStr);
        }
    }
    if (map[s.r][s.c].walls[2] == 0) { // if there isnt a wall east
        //enqueue(map[s.r][s.c + 1]);
        if (map[s.r][s.c + 1].val > s.val + 1) { // if the cell to my right has a value greater than mine +1
            map[s.r][s.c + 1].val = s.val + 1; // set the right square's value to mine + 1
            enqueue(map[s.r][s.c + 1]); // add it to the queue
            char* valStr = intToString(s.val + 1);
            API_setText(s.c + 1, 15 - s.r, valStr); // display it on the map
            free(valStr);
        }
    }
    if (map[s.r][s.c].walls[3] == 0) { //west
        if (map[s.r][s.c - 1].val > s.val + 1) {
            map[s.r][s.c - 1].val = s.val + 1;
            enqueue(map[s.r][s.c - 1]);
            char* valStr = intToString(s.val + 1);
            API_setText(s.c - 1, 15 - s.r, valStr);
            free(valStr);
        }
    }
}
// check neightbors
void checkN2(Square s) { 

    //start of test
    //fprintf(stderr,"I am in checkN()");
    //end of test

    if (map[s.r][s.c].walls[0] == 0) { // if there isnt a wall north
        //enqueue(map[s.r - 1][s.c]);
        if (map[s.r - 1][s.c].parallel > s.parallel + 1) { // if the upper square's value > my square's value + 1
            map[s.r - 1][s.c].parallel = s.parallel + 1; // set upper square's value to my square's value + 1
            enqueue2(map[s.r - 1][s.c]); // add upper square to queue 
            char* valStr = intToString(s.parallel + 1);
            //API_setText(s.c, 15 - (s.r - 1), valStr); // diplay square in map
            free(valStr);
        }
    }
    if (map[s.r][s.c].walls[1] == 0) { // south
        //enqueue(map[s.r + 1][s.c]);
        if (map[s.r + 1][s.c].parallel > s.parallel + 1) {
            map[s.r + 1][s.c].parallel = s.parallel + 1;
            enqueue2(map[s.r + 1][s.c]);
            char* valStr = intToString(map[s.r + 1][s.c].parallel);
            //API_setText(s.c, 15 - (s.r + 1), valStr);
            free(valStr);
        }
    }
    if (map[s.r][s.c].walls[2] == 0) { // if there isnt a wall east
        //enqueue(map[s.r][s.c + 1]);
        if (map[s.r][s.c + 1].parallel > s.parallel + 1) { // if the cell to my right has a value greater than mine +1
            map[s.r][s.c + 1].parallel = s.parallel + 1; // set the right square's value to mine + 1
            enqueue2(map[s.r][s.c + 1]); // add it to the queue
            char* valStr = intToString(s.parallel + 1);
            //API_setText(s.c + 1, 15 - s.r, valStr); // display it on the map
            free(valStr);
        }
    }
    if (map[s.r][s.c].walls[3] == 0) { //west
        if (map[s.r][s.c - 1].parallel > s.parallel + 1) {
            map[s.r][s.c - 1].parallel = s.parallel + 1;
            enqueue2(map[s.r][s.c - 1]);
            char* valStr = intToString(s.parallel + 1);
            //API_setText(s.c - 1, 15 - s.r, valStr);
            free(valStr);
        }
    }
}

void makeSquare(int row, int col, int val, int parallel,int pared[4]){

    //start of test
    //fprintf(stderr,"I am in makeSquare()");
    //end of test

    map[row][col].r = row;
    map[row][col].c = col;
    map[row][col].val = val;
    map[row][col].parallel = parallel;
    for(int i = 0; i < 4; i++){
        map[row][col].walls[i] = pared[i];
    }
    API_setText(map[row][col].c, 15 - map[row][col].r, intToString(map[row][col].val));
}

void addWall(int row, int col, int dir) {

    //start of test
    //fprintf(stderr,"I am in addWall()");
    //end of test



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

    //start of test
    //fprint(stderr,"I am in restart()");
    //end of test


    makeSquare(15,0, 2000, 0, map[15][0].walls); // sets parallel value for start sqaure and adds to queue
    enqueue2(map[15][0]);

    makeSquare(7,7,0, 2000,map[7][7].walls); // top left
    enqueue(map[7][7]);

    makeSquare(7,8,0, 2000,map[7][8].walls); // top right
    enqueue(map[7][8]);

    makeSquare(8,7,0, 2000,map[8][7].walls);// bottom left
    enqueue(map[8][7]);
     
    makeSquare(8,8,0, 2000,map[8][8].walls); // bottom right
    enqueue(map[8][8]);
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
            else if(row == 15 && col == 0){

            }
            else{
                makeSquare(row, col, 2000, 2000,map[row][col].walls);
            }
        }
    }
}

void floodFill(){

    //start of test
    //fprintf(stderr,"I am in floodFill()");
    //end of test


    while (!isQueueEmpty()) {
        Square s = dequeue();
        checkN(map[s.r][s.c]);
    }
}



void floodFill2(){

    //start of test
    //fprintf(stderr,"I am in floodFill()");
    //end of test


    while (!isQueueEmpty2()) {
        Square s = dequeue2();
        checkN2(map[s.r][s.c]);
    }
}

void mouseWalls(){ 

    //start of test
    //fprintf(stderr,"I am in mouseWalls()");
    //end of test


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
    floodFill();
    floodFill2();
}

void ratMove(int destination){

    //start of test
    //fprintf(stderr,"I am in ratMove()");
    //end of test


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

void ratNeighbors(Square s){

    //start of test
    //fprintf(stderr,"I am in ratNeighbors()");
    //end of test



    mouseWalls();
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

void ratNeighbors2(Square s){

    //start of test
    //fprintf(stderr,"I am in ratNeighbors()");
    //end of test



    mouseWalls();
    if(map[s.r][s.c].walls[0] != 1){ // if there isnt a wall north
        if(map[s.r][s.c].parallel > map[s.r-1][s.c].parallel){   // if the northern square has a lower cost
            ratMove(0); //move north
            return;
        }
    }

    if(map[s.r][s.c].walls[1] != 1){ // if there isnt a wall south
        if(map[s.r][s.c].parallel > map[s.r+1][s.c].parallel){   // if the southern square has a lower cost
            ratMove(1); // move south
            return;
        }
    }

    if(map[s.r][s.c].walls[2] != 1){ // if there isnt a wall east
        if(map[s.r][s.c].parallel > map[s.r][s.c+1].parallel){   // if the eastern square has a lower cost
            ratMove(2); // move east
            return;
        }
    }

    if(map[s.r][s.c].walls[3] != 1){ // if there isnt a wall west
        if(map[s.r][s.c].parallel > map[s.r][s.c-1].parallel){   // if the western square has a lower cost
            ratMove(3); // move west
            return;
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
    q.front = 0;
    q.rear = -1;
    q.size = 0;

    q2.front = 0;
    q2.rear = -1;
    q2.size = 0;
    //initialize map              
    for (int col = 0; col < 16; col++) {
        for (int row = 15; row >= 0; row--) {
            int walls[4] = {0,0,0,0};
            makeSquare(row, col, 2000, 2000, walls);
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
    int ligma[4] = {0,1,0,1};
    makeSquare(15, 0, 2000, 0, ligma);
    enqueue2(map[15][0]);


    int w[4] = {0,0,0,0}; // no walls
    
    makeSquare(7,7,0, 2000, w); // top left
    enqueue(map[7][7]);

    makeSquare(7,8,0, 2000, w); // top right
    enqueue(map[7][8]);

    makeSquare(8,7,0, 2000, w);// bottom left
    enqueue(map[8][7]);
     
    makeSquare(8,8,0, 2000,w); // bottom right
    enqueue(map[8][8]);
    
    
    //floodFill();
    pikachu.row = 15;
    pikachu.col = 0;
    pikachu.oriention = 0;// start mouse at bottom left square facing north
    map[15][0].visits = 1;
    
    checkVisits(map[pikachu.row][pikachu.col]);
    while(map[pikachu.row][pikachu.col].val != 0){
        ratNeighbors(map[pikachu.row][pikachu.col]);
        checkVisits(map[pikachu.row][pikachu.col]);
    }
    
    
    while(pikachu.col != 0 || pikachu.row != 15){
        ratNeighbors2(map[pikachu.row][pikachu.col]);
        checkVisits(map[pikachu.row][pikachu.col]);
    }
    

    
    return 0;
}

