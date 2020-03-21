# ChessSteps

A two-player chess game application was developed in the C++11 environment using an ObjectOriented code architecture. An abstract base class called ‘piece’ was used to define the functionalities
of each chess piece, from which the chess pieces inherited their private attributes (colour, current
square and number of moves) as well as the public methods used to act on the pieces. A second class
called ‘square’ was used to store the information retained in each square on the board. A cyclic
relationship dependency was used to connect the ‘piece’ and ‘square’ objects and ensure continuous
communication between these objects.


A second layer of interconnected classes was devised to implement the player and board related
features, named ‘player’ and ‘board’ respectively. The class ‘player’ was used to retain all
information collected from each player, namely its colour, name, remaining and captured pieces, and
the methods required to act on these attributes. The class ‘board’ was used to store the information
related to the current structure of the board in the form of a static self-attribute, to allow universal
access for all classes.


The third hierarchical layer of the architecture contained the class ‘session’. This class was used to
initialise one session the chess game and run the game through the methods implemented in the
previous layers. A main function was used to control the hierarchical implementation of the game
