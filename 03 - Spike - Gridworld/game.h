#include <iostream>
#include <array>
#include <vector>
#include <map>
#include "map.h"

class Game
{
public:
    Map* map;
    
    Game(){
        map = new Map();
    }
    void Start()
    {
        running = true;
        std::cout << "Welcome to GridWorld: Quantised Excitement. Fate is waiting for You!" << std::endl;
        std::cout << "Valid Commands: N,S,W and E for direction. Q to quite the game." << std::endl;
        player = map->FindStart();

        map->Draw(player);
        AwaitInput();
    }
    void Stop()
    {
        running = false;
    }

private:
    void AwaitInput()
    {
        if (running){
            map->PrintAvailableDirections(player);
            std::string input;
            std::cin >> input;
            HandleCommand(input[0]);
        }
    }
    void HandleCommand(char command)
    {
        switch (command){
            case 'N': case 'E': case 'S': case 'W':
                MovePlayer(command);
                break;
            case 'Q':
                running = false;
                break;
            default:
                std::cout << "Invalid Command: Please try again!" << std::endl;
        };
        AwaitInput();
    };
    void RequestPlayAgain(){
        std::string playAgain;
        std::cout << "Would You Like to Play Again? (Y/N)";
        std::cin >> playAgain;
        if (playAgain == "Y"){
            Start();
        } else if (playAgain == "N"){
            Stop();
        } else {
            RequestPlayAgain();
        }
    }
    void Die(std::string message){
        std::cout << message << std::endl;
        std::cout << "YOU HAVE DIED!" <<  std::endl;
        std::cout << "Thanks for playing. Maybe next time!" <<  std::endl;
        RequestPlayAgain();
    }
    void Win(std::string message){
        std::cout << message << std::endl;
        std::cout << "YOU WIN!" <<  std::endl;
        std::cout << "Thanks for playing. There probably won't be a next time. " << std::endl;
        RequestPlayAgain();
    }
    void OnLand(){
        map->Draw(player);
        char location = map->Get(player);
        switch (location){
            case 68: //D
                Die("Arrrrgh... you've fallen down a pit.");
                break;
            case 71: //G
                Win("Wow - You've discovered a large chest filled with GOLD coins.");
                break;
        };
    };
    void MovePlayer(char dir, int steps = 1)
    {
        std::array<int,2> xyDir = map->DirectionToXY(dir);
        if (map->CanMoveDirection(player,xyDir)){
            std::cout << "Moved Player " << dir << "!" << std::endl;
            player[0] += xyDir[0] * steps;
            player[1] += xyDir[1] * steps;
            OnLand();
        } else {
            std::cout << "Player cannot move here. Please try again!" << std::endl;
        }
    };

    std::array<int, 2> player; // x,y represented as [0,1], position of player
    bool running;
};