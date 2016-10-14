COMP2012H Project2 - Tetris

Made By:
Cheng Ho Kei (12219689)
Chan Nok Hin (20349103)

The project program has been divided into logic and interface part.

Logic:

* Game manager: Contain information about the game, such as score, level, the current/next block and the current base. Act as a entrance from the UI to the game logic.

* Cube: Basic unit of tetris. Represent a square with x, y coordinate and color.

* Block: Class that contains several Cubes to construct different kinds of block. It handles the rotation and translation of the block.

* Base: A class containing all the Cubes that are landed on it

* Util: A class to convert the Cubes's enum color (abstract) to the UI color (QColor)

Interface:

* GameWindow: Container of gameboard, score, level and preview window. Its updateView() function will update all UI it contains.
   
* GameBoard & Preview window: Draw the tetris pieces
  
* GameController: Capture user input and redirect to the logic part
  
   

