#include <iostream>
#include <chrono>
#include <thread>
#include <string>

#include "game.h"

void InputUpdateLoop(Game &game){
   while (game.running){
      char input = game.Input();
      game.Update(input);
   }
}

int main()
{
   Game game = Game();  
   game.Start();

   // handle input and updating of game through a separate thread
   std::thread inputUpdateThread(InputUpdateLoop,std::ref(game));
   
   // render the game on the main thread, this way, rendering is not paused by awaiting input through std::cin
   const unsigned int FPS = 500;
   while (game.running)
   {
      game.Render();
      std::this_thread::sleep_for(std::chrono::milliseconds(1000 / FPS));
   }

   inputUpdateThread.join();

   return 0;
};