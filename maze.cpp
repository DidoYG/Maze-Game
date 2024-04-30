#include <iostream>
#include <vector>
#include <windows.h>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random> 
using namespace std;

int getRandSt(vector<int> positions){
    random_device rd;
    mt19937 rng(rd());

    shuffle(positions.begin(), positions.end(), rng);

    srand(static_cast<unsigned int>(time(nullptr)));

    int randomIndex = rand() % positions.size();

    return positions[randomIndex];
}

int getRandFi(vector<int> positions){
    srand(static_cast<unsigned int>(time(nullptr)));

    int randomIndex = rand() % positions.size();

    return positions[randomIndex];
}

string getRandDir(vector<string> directions){
    srand(static_cast<unsigned int>(time(nullptr)));

    int randomIndex = rand() % directions.size();

    return directions[randomIndex];
}

void drawMaze(vector<string> maze, int mazeSize){
    system("cls");
    cout << "Moves:" << endl;
    cout << "8 - Up" << endl;
    cout << "4 - Left" << endl;
    cout << "6 - Right" << endl;
    cout << "2 - Down" << endl << endl;

    for(int i = 0; i < maze.size(); i++){
        if(i % mazeSize == 0){
            cout << endl;
            cout << maze[i];
        }
        else{
            cout << maze[i];
        }
    }

    cout << endl << endl << "> ";
}

void logic(vector<string> maze, int mazeSize, int playerPos){
    bool inMaze = true;
    char input;

    while(inMaze){

        drawMaze(maze, mazeSize);
        cin >> input;

        if(maze[playerPos - mazeSize] == "FI" && input == '8'){
            inMaze = false;
            break;
        }
        else if(maze[playerPos + mazeSize] == "FI" && input == '2'){
            inMaze = false;
            break;
        }
        else if(maze[playerPos + 1] == "FI" && input == '6'){
            inMaze = false;
            break;
        }
        else if(maze[playerPos - 1] == "FI" && input == '4'){
            inMaze = false;
            break;
        }

        if(maze[playerPos - mazeSize] != "[]" && input == '8'){
            maze[playerPos - mazeSize] = ":)";
            maze[playerPos] = "  ";
            playerPos -= mazeSize;
        }
        else if(maze[playerPos + mazeSize] != "[]" && input == '2'){
            maze[playerPos + mazeSize] = ":)";
            maze[playerPos] = "  ";
            playerPos += mazeSize;
        }
        else if(maze[playerPos + 1] != "[]" && input == '6'){
            maze[playerPos + 1] = ":)";
            maze[playerPos] = "  ";
            playerPos += 1;
        }
        else if(maze[playerPos - 1] != "[]" && input == '4'){
            maze[playerPos - 1] = ":)";
            maze[playerPos] = "  ";
            playerPos -= 1;
        }

    }

    system("cls");
    cout << "You found the exit!";
}

void generate(vector<string> maze, vector<string> directions, int mazeSize, int path, int playerPos, int finishPos){
    string dir, temp;
    int cycles = 0, row = 2, divider = 30;
    vector<string> originalMaze = maze;
    dir = getRandDir(directions);
    
    while( cycles / divider <= 20 ){

        cycles++;
        system("cls");
        cout << "Elapsed time: " << cycles / divider << " seconds" << endl;

        if( (dir == "Up") && ((path - 2*mazeSize) > 0) && (maze[path - mazeSize] == "[]") && (maze[path - 2*mazeSize] == "[]") ){
            maze[path - mazeSize] = "  ";
            path -= mazeSize;
            row--;
            dir = getRandDir(directions);

        }
        else{
            temp = dir;
            directions.erase(remove(directions.begin(), directions.end(), dir), directions.end());
            dir = getRandDir(directions);
            directions.insert(directions.begin(), temp);

        }

        if( (dir == "Down") && (path + (2*mazeSize) < (mazeSize*mazeSize)) && (maze[path + mazeSize] == "[]") && (maze[path + 2*mazeSize] == "[]") ){
            maze[path + mazeSize] = "  ";
            path += mazeSize;
            row++;
            dir = getRandDir(directions);

        }
        else{
            temp = dir;
            directions.erase(remove(directions.begin(), directions.end(), dir), directions.end());
            dir = getRandDir(directions);
            directions.push_back(temp);

        }

        if( (dir == "Left") && ( ((path - 1) % mazeSize) != 0) && (maze[path - 1] == "[]") && (maze[path - 2] == "[]") ){
            maze[path - 1] = "  ";
            path -= 1;
            dir = getRandDir(directions);

        }
        else{
            temp = dir;
            directions.erase(remove(directions.begin(), directions.end(), dir), directions.end());
            dir = getRandDir(directions);
            directions.insert(directions.begin(), temp);

        }

        if( (dir == "Right") && ( ((path + 2) % mazeSize) != 0) && (maze[path + 1] == "[]") && (maze[path + 2] == "[]") ){
            maze[path + 1] = "  ";
            path += 1;
            dir = getRandDir(directions);

        }
        else{
            temp = dir;
            directions.erase(remove(directions.begin(), directions.end(), dir), directions.end());
            dir = getRandDir(directions);
            directions.push_back(temp);
        }


        if( ( (cycles / divider) >= 10 && row <= (mazeSize / 2) ) ){
            int distance = mazeSize - 1 - row;

            while(distance > 0){
                path += mazeSize;
                maze[path] = "  ";
                row++;
                distance--;
            }
        }

        if(row == mazeSize - 1 && path > finishPos){
            int distance = path - finishPos;

            while(distance > 1){
                path -= 1;
                maze[path] = "  ";
                distance--;
            } 
        }
        else if(row == mazeSize - 1 && path < finishPos){
            int distance = finishPos - path;

            while(distance > 1){
                path += 1;
                maze[path] = "  ";
                distance--;
            }
        }


        if( (maze[path + mazeSize] == "FI") ){
            path += mazeSize;
            break;
        }
        else if( (maze[path - 1] == "FI") ){
            path--;
            break;
        }
        else if( (maze[path + 1] == "FI") ){
            path++;
            break;
        }

    } 
    
    logic(maze, mazeSize, playerPos);
}

int main() {
    vector<string> maze;
    vector<int> stPositions;
    vector<int> fiPositions;
    vector<string> directions = {"Up", "Down", "Left", "Right"};
    int mazeSize, st, fi, path;
    
    system("cls");
    cout << "Enter a size for the maze: ";
    cin >> mazeSize;

    for(int i = 0; i < mazeSize*mazeSize; i++){
        maze.push_back("[]");

        if(i > mazeSize && i < 2*mazeSize - 1){
            stPositions.push_back(i);
        }

        if(i > mazeSize*mazeSize - mazeSize*2 && i < mazeSize*mazeSize - mazeSize - 1){
            fiPositions.push_back(i);
        }
    }

    st = getRandSt(stPositions);
    fi = getRandFi(fiPositions);
    path = st;

    maze[st] = ":)";
    maze[fi] = "FI";

    generate(maze, directions, mazeSize, path, st, fi);

    return 0;

}