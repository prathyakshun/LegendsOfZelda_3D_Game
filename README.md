Graphics Assignment-2 LEGENDS OF ZELDA
===================================

Legends of Zelda in OpenGL 3.

Prathyakshun Rajashankar - 20161107
===================================

This program contains code for the game "Pacman-Killer"

For running the game:
* cd into the build directory
* cmake ../
* make
* run the executable file

Controls and Views:
===================

W - Move Cannon Up
S - Move Cannon Down
A – Move player left
D – Move player right
SPACE – Jump
G - Man gets out of boat in the island
L - Release lock of the ship near the island    
P - Camera angle rotates clockwise
O - Camera angle rotates anti-clockwise
LeftArrow – Rotate boat/man left
RightArrow – Rotate boat/man right
UpArrow – Move boat/man forward
DownArrow – Move boat/man backward
Mouse Drag left – Drag in heli view
Mouse Drag right – Drag in heli view
Mouse click - Shoot

CHEATS:
T - Score += 10
Y - Life restored

VIEWS:
0 - standard look-ahead view from start location
1 - Top-View
2 - Tower-base View
3 - Follow-cam View
4 - Boat-view first person
5 - Side-View
6 - Tower-top View
7 - Follow-man View
8 - First-person man view
9 - Helio cam View

Rules:
======

Boat keeps moving and escapes from monsters. Monsters try attacking. Different monsters need different number of shots
to be killed. Monsters can be attacked with cannon.

Get the required score each level.

Find Treasure in an island in the sea.

Killing boss monster gives boost
Killing monster gives either health restorer on score-addder

Levels:
=======

Each level i requires i*10 points in 60 secs to be successfully completed. Following completion, the player is directed towards the next level. Failing to complete the level results in GAME OVER.

Timer in title bar and scoring done on the screen


Scoring:
========

Rock = +3
Borrel = =5
Boss monster = +7
Monster = +5
Gift1 = +10
fly monster = +100
Treasure = +1000

Gift2: Health = 10
Damage from enemies = -1 Health

Features
--------
* Boost - Gives fast speed for a time interval. Boost received on killing boss monster
* Gift - Restore health, Add score
* Environment following physics rules
* Wind - movement of sail with angle and boat.
* Barrels
* Monsters
* Boss monsters
* Cannon firing

Extra Features
--------------

* Unlimited levels, unlimited gameplay
* 10 Different views for better game-play experience.
* Time and Target on title bar
* Island with trees
* Man on boat and can be controlled
* Flying monsters with laser power
* Transparency in water
* FPS shooting with mouse
* Up-down movement of objects

License
-------

Copyright &copy; 2018 Prathyakshun Rajashankar <prathraja@gmail.com>
