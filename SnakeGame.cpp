#include <iostream>
#include <conio.h>
#include <windows.h>

using namespace std;

//function prototype 
void run();
void printMap();
void initMap();
void move (int directionx, int directiony);
void update();
void changeDirection (char key);
void clearScreen();
void generateFood();

char getMapValue (int value);

//map dimensions 
const int mapwidth = 20;
const int mapheight = 20;
const int Max_Size = 400;

//tile values for the map
int map[Max_Size];

//snake head details
int headXPos;
int headYPos;
int directionOfSnake;

//amount of food snake has already consume before game starts
int food = 4;

//determine if game is running or not
bool running;

int main () {

    run();
    return 0; 
}
//main game function
void run (){
    //initialize the map
    initMap();
    running = true;

    while(running) {
        //if a key is pressed
        if(kbhit()) {
            //change to direction determined by key pressed
            changeDirection(getch());
        }

        //update the map
        update();
        //clear the screen
        clearScreen();
        //print the map
        printMap();
        //delay 0.4 seconds
        Sleep(400);
    }
    //game text and making food decrease by 4 as its initial value is set
    cout << "\t\tGame Over!" << endl << "\t\tYour score is: " << food - 4;
    //stop console from closing instantly
    cin.ignore();
}

void changeDirection (char key){
    /*          
      W         1
    A + D     4 + 2
      S         3
    */
   switch(key) {
    case 'w':
        if(directionOfSnake != 2) directionOfSnake = 0;
        break;

    case 'd':
        if(directionOfSnake != 3) directionOfSnake = 1;
        break;

    case 's':
        if(directionOfSnake != 4) directionOfSnake = 2;
        break;

    case 'a':
        if(directionOfSnake != 5) directionOfSnake = 3;
        break;            
   }
}

void move (int dx, int dy){
    //moves snake head to new location
    //determine new head position
    int newX = headXPos + dx;
    int newY = headYPos + dy;

    //check if there is food present at location
    if(map[newX + newY * mapwidth] == -2){
        //increase food value i.e. snake body
        food++;

        //generate new food on map
        generateFood();
    }
    //check location is free
    else if(map[newX + newY * mapwidth] != 0){
        running = false;
    }

    //move head to new location 
    headXPos = newX;
    headYPos = newY;
    map[headXPos + headYPos * mapwidth] = food + 1;
}

void clearScreen() {
    system("cls"); //clear the screen
}

void generateFood (){
    //generates new food for snake on map
    int x = 0;
    int y = 0;

    do{
        //generate random x & y values within the map
        x = rand() % (mapwidth - 2) + 1;
        y = rand() % (mapheight - 2) + 1;

        //if location is not free try again
    } while(map[x + y * mapwidth] != 0);

    //place new food
    map[x + y * mapwidth] = -2;
}

void update() {
    //move in direction indicated
    switch(directionOfSnake) {
        case 0: move(-1, 0);
        break;

        case 1: move(0, 1);
        break;

        case 2: move(1, 0);
        break;

        case 3: move(0, -1);
        break; 
    }

    //reduce snake values on map by 1
    for(int i = 0; i < Max_Size; i++){
        if(map[i] > 0) map[i]--; 
    }
}

void initMap() { //initialize the map
    // Places the initial head location in center of map
    system("cls");
    headXPos = mapwidth / 2;
    headYPos = mapheight / 2;
    map[headXPos + headYPos * mapwidth] = 1;

    // Places top and bottom walls 
    for (int x = 0; x < mapwidth; ++x) {
        map[x] = -1;
        map[x + (mapheight - 1) * mapwidth] = -1;
    }

    // Places left and right walls
    for (int y = 0; y < mapheight; y++) {
        map[0 + y * mapwidth] = -1;
        map[(mapwidth - 1) + y * mapwidth] = -1;
    }

    // Generates first food
    generateFood();
}

// Prints the map to console
void printMap()
{
    for (int x = 0; x < mapwidth; ++x) {
        for (int y = 0; y < mapheight; ++y) {
            // Prints the value at current x,y location
            cout << getMapValue(map[x + y * mapwidth]);
        }
        // Ends the line for next x value
        cout << endl;
    }
}

// Returns graphical character for display from map value
char getMapValue(int value){
    // Returns a part of snake body
    if (value > 0) return 'o';

    switch (value) {
        // Return wall
    case -1: return 'X';
        // Return food
    case -2: return 'O';
    }

    // Return empty space
    return ' ';
}

