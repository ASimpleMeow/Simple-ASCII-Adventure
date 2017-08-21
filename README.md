# Simple ASCII Adventure Game
---
_A small C++ ASCII RPG game project_

## Introduction
### Brief Description
In this project I plan to make a Rogue/Dwarven Fortress style game using ASCII graphics and coded in C++ language. 

## Development Aims
+ Player moving around in the world of ASCII
+ Battle a variety of enemies
+ Level up to become stronger through battle
+ Wield diverse set of equipment which would be obtained from battle or bought in a shop with gold (from enemies).
+ Have multiple levels (screens) which the player can access
+ Have simple narrative cutscenes of text

## Restrictions/Problems
The big issue I will be having would be cross-platform support, for the time being I'm focusing on Windows OS and using Windows libraries for development. However once I achieve a certain level of progress where I am satisfied, I will try make this game platform-independant, or at least be runnable on Linux systems.

## Technologies used
1. Unreal Engine 4
2. Visual Studio
3. C++

## Potential Future Additions
### Procedural Generation
I hope to make some parts of the game, such as level layout, to be procedurally generated. However this addition is unlikely to be implemented in the foreseeable future due to various reasons.

### Towns and NPCs
This is more feasible for me to implement, but will be left till last until all major mechanics of the game are implemented and are mostly bug free.

## User Guide
### ASCII key

| ASCII | Tile Type    |
| :-------: | :--------------: |
| @     | Player       |
| #     | Wall         |
| .     | Floor/Ground |
| g     | Goblin       |
| S     | Snake        |
| B     | Bandit       |
| O     | Ogre         |
| D     | Dragon       |

### Controls

| Key | Action     |
| :-----: | :------------: |
| w   | Move Up    |
| a   | Move Left  |
| s   | Move Down  |
| d   | Move Right |

### Battle
Running into an enemy will initiate a battle between you and that enemy. You will attack first, your **attack** stat will determine the maximum output damage you deliver.
_(**NOTE** The enemies defence will affect the damage they recieve, so your damage output will not always be the damage dealt and vise versa)_
Once your attack is finished, the enemy will counter you with their own attack in the similar fashion as described above.