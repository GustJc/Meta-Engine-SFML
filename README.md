Meta Engine
============

This is a tool capable of taking a procedually generated map and running a BOT throught the map for a
determined number of times in order to obtain metrics relative to its appeal. 

Requirements
---------

This project is tested in both windows 7 and linux(Ubuntu 12.04) and requires the following
libraries:
* SFML 2.1
* SFGUI 0.9
* Lua 5.1
* Luabind 0.9.8 - (Compiled with Qt's mingw 4.8 in windows)

*Note: Use -Wno-unused-local-typedefs to hide lua's warnings in mingw 4.8*

Engine options
-------

In Progress

Commands and terminal
--------

The engine has an in-game terminal called by pressing ';' which has the following commands:
* return (returns to the previous interface)
* exit (Exits the engine)
* botDelay miliseconds (delay for bot thinking process)
* disableBot (disables the bot thinking)
* enableBot (enables bot processing)
* setFog true/false (activates or deactivates the fog-of-war)

Old Version - Testes de algoritmos procedurais
--------

Parametros
* w e -W -> Tamanho maximo e minimo da sala, seguido por um numero.
* s -> Numero de salas.
* M -> algoritmo de Miners.
* v e -V -> Numero de vidas minimas e maximas dos miners
* t -> Total de vida do sistema
* c -> Chance de criação de miners, sendo 10.000 o total.
