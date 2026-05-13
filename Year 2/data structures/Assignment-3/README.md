# Data-Structures-Assignment-3

This repository contains a C++ implementation of a binary search tree (BST) for managing data on games played by different players. It consists of two main classes, GamesPlayedTree and PlayersTree, which represent the trees for games and players, respectively.
Features
GamesPlayedTree Class

This class manages information on individual games played by a player, with data on:

    gameID: Unique identifier for each game.
    hoursPlayed: Total hours played.
    achievementsUnlocked: Total number of achievements unlocked.

Key Methods

    insert: Inserts a game into the tree by its gameID.
    findgamesPlayed: Finds a game by gameID.
    removeNode: Removes a game from the tree.
    printTree: Displays all games in an in-order traversal.
    hasPlayed: Checks if a particular game has been played by searching for the gameID.
    showNLayers: Shows games up to a certain layer in the tree.
    saveGamesPlayedData: Saves the game data to a file.

PlayersTree Class

This class manages data for individual players, including:

    playerID: Unique identifier for each player.
    name: Player's name.
    phoneNumber: Player's phone number.
    email: Player's email.
    password: Player's password.

Each player has a GamesPlayedTree instance, which stores data on all games played by that player.
Key Methods

    insert: Inserts a player into the tree by playerID.
    findPlayer: Finds a player by playerID.
    removeNode: Removes a player from the tree.
    printTree: Displays all players and their games in an in-order traversal.
    savePlayersData: Saves player data, along with their game information, to a file.
    showNLayers: Shows players up to a certain layer in the tree.
    showLayerNumber: Displays the layer of a specific player based on their playerID.

Dependencies

This code requires the following standard libraries:

    <iostream> for console output.
    <string> for handling player and game data.
    <fstream> for file input/output.

Usage

    Instantiate the Trees: Create instances of GamesPlayedTree and PlayersTree to manage game and player data.
    Insert Data: Use insert methods to add games and players to the trees.
    Find and Remove Nodes: Use findgamesPlayed, findPlayer, and removeNode to search for and manage nodes in the trees.
    Display Data: Use printTree, showNLayers, and showLayerNumber to display tree data in the console.
    Save Data: Use saveGamesPlayedData and savePlayersData to save tree data to text files.
