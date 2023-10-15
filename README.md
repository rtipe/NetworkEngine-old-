# Network Engine for R-Type Project

![R-Type Logo](./assets/Doc/LogoRtype.png)

## Introduction

This README document outlines the development and use of a network engine for our R-Type project. As part of our project, we created a network engine to enable multiplayer functionality in the game. This document provides an overview of the network engine, its features, and how it was integrated into the R-Type project.

## Network Engine Features

Our network engine is designed to provide the following key features:

- **Multiplayer Support:** The engine enables multiple players to connect and play the R-Type game together in real-time.

- **Client-Server Architecture:** It follows a client-server architecture, where a central server manages the game state and communication between clients.

- **Game Synchronization:** The engine ensures that all connected clients are in sync with the game state, including player positions, enemy behavior, and power-ups.

- **Reliable Communication:** It uses reliable communication protocols to ensure that data is transmitted accurately and without loss.

- **Scalability:** The network engine is designed to be scalable, allowing for a smooth gaming experience even with a large number of players.

## Integration with R-Type

The network engine is seamlessly integrated into the R-Type game project. It enables players to connect to a server and participate in multiplayer matches. The engine handles the transfer of game data, including player actions and game events, to ensure a consistent gaming experience for all players.

## Building and Running

1. Create a build directory at the root:
    ```bash
    mkdir build
    cd build

2. Compile in this directory:
    ```bash
    cmake ..
    make

3. Go to the bin directory created by the compilation:
    ```bash
    cd bin

4. Execute the binary in the root of the repository:
    ```bash
    mv project ../../
    cd ../../
    ./project

## Conclusion

The development of our network engine has been a crucial aspect of our R-Type project. It has allowed us to create a multiplayer gaming experience, enabling players to connect and play the game together. This achievement highlights our skills in network programming, game development, and project management.

## Contributors

- abdelkader.mazouz@peitech.eu
- vincent.ballandi@epitech.eu
- younes1.bahri@epitech.eu
- swann.lagoute@epitech.eu
- simon.vermeulen@epitech.eu
