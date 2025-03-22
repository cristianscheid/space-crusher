# Space Crusher

## Project Status

Development is currently on hold due to time constraints. However, plans for future updates remain in place, including new levels, a main menu, refined gameplay mechanics, and more dynamic enemy and asteroid movements to elevate the gameplay experience.

## Description

Space Crusher is a 2D space shooter game being developed from scratch using the C programming language and the SDL (Simple DirectMedia Layer) library. In this game, players control a spaceship, navigating through space while dodging asteroids and battling against various enemies.

## Features

- Spaceship movement and shooting based on player input.
- Collision detection for the spaceship, enemies, bullets, and asteroids.
- Health bar decrease upon collisions with enemy bullets.
- Sandbox level for testing and demonstration purposes.

## Built With

![C][c-badge]
![SDL][sdl-badge]

## Visuals

https://github.com/user-attachments/assets/ca299c9f-9e42-453f-a0e4-ba1ce25b53a2

## Installation

To get started with this project, follow the steps below:

1. **Install build tools and SDL libraries**

   - Debian/Ubuntu:

     ```
     sudo apt install gcc make libsdl2-dev libsdl2-image-dev
     ```

   - Fedora/RHEL/CentOS:

     ```
     sudo dnf install gcc make SDL2-devel SDL2_image-devel
     ```

   - OpenSUSE:

     ```
     sudo zypper install gcc make SDL2-devel SDL2_image-devel
     ```

   - Arch Linux:

     ```
     sudo pacman -S gcc make sdl2 sdl2_image
     ```

   - If your Linux distribution is not listed, you can find instructions for installing the SDL libraries from source [here](https://lazyfoo.net/tutorials/SDL/01_hello_SDL/linux/index.php).

2. **Clone the repository**

   ```
   git clone https://github.com/cristianscheid/space-crusher.git
   cd space-crusher
   ```

3. **Build the project**

   ```
   make
   ```

4. **Run the executable**

   ```
   ./build/space-crusher
   ```

## Usage

Once the game is running, you can control the spaceship using the arrow keys to move and the spacebar to shoot. To exit the game, simply close the window.

### Running and Debugging with Visual Studio Code

To run or debug the project with Visual Studio Code, follow these steps:

- Open the `space-crusher` project folder in Visual Studio Code.

- Install the `C/C++` extension by Microsoft from the Extensions tab (Ctrl+Shift+X).

- Go to the Run and Debug tab (Ctrl+Shift+D).

- Select "Debug Space Crusher" or "Run Space Crusher" from the dropdown at the top, next to the play icon.

- Click the play icon to start. If you're debugging, remember to set breakpoints.

## Acknowledgment

Special thanks to the asset creators at [OpenGameArt](https://opengameart.org) for their contributions to this project. Below is a list of the assets used:

- Spaceships:

  - https://opengameart.org/content/2d-spaceship-pack

- Background:

  - https://opengameart.org/content/space-background-6

- Laser:

  - https://opengameart.org/content/assets-free-laser-bullets-pack-2020

- Explosion:

  - https://opengameart.org/content/blasteroids-art-pack-cc-by-30

- Asteroids:

  - https://opengameart.org/content/asteroids-set-01
  - https://opengameart.org/content/asteroids-set-02

## License

Distributed under the MIT License. See LICENSE.txt for more information.

<!-- Badges for 'Built With' section -->

[c-badge]: https://img.shields.io/badge/C-C11-gray?style=for-the-badge&logo=data:image/svg+xml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHZpZXdCb3g9IjAgMCA0OCA0OCIgd2lkdGg9IjI0IiBoZWlnaHQ9IjI0IiBmaWxsLXJ1bGU9ImV2ZW5vZGQiIHhtbG5zOnY9Imh0dHBzOi8vdmVjdGEuaW8vbmFubyI+PHBhdGggZD0iTTI0IDBhMi41NiAyLjU2IDAgMCAwLTEuMjU0LjMyNkwzLjU0IDExLjEwN2MtLjc3Ni40MzUtMS4yNTQgMS4yNDEtMS4yNTQgMi4xMTJ2MjEuNTYyYTIuNDMgMi40MyAwIDAgMCAxLjI1NCAyLjExMmwxOS4yMDUgMTAuNzgxYy43NzUuNDM1IDEuNzMzLjQzNSAyLjUwOSAwTDQ0LjQ2IDM2Ljg5MmMuNzc2LS40MzUgMS4yNTQtMS4yNDEgMS4yNTQtMi4xMTJWMTMuMjE5YTIuNDIzIDIuNDIzIDAgMCAwLS4wMjItLjEyOWMtLjAzMi0uNDk0LS4xNDgtMS4wMDYtLjUzNi0xLjM5M2EyLjQyMyAyLjQyMyAwIDAgMC0uNjk2LS41ODlMMjUuMjU0LjMyNkMyNC44NjcuMTA4IDI0LjQzMyAwIDI0IDB6bTAgOGExNi4wMTEgMTYuMDExIDAgMCAxIDExLjMxMiA0LjY4OCAxNi4wMTEgMTYuMDExIDAgMCAxIDEuOTg3IDIuNDI0IDE2LjAxMSAxNi4wMTEgMCAwIDEgLjQ1NS43NjNMMzAuODMgMTkuODNsLS4xOTYtLjMwNC0uNDYtLjYxNi0uNTE4LS41NjctLjU2Ny0uNTE4LS42MTYtLjQ2LS42NjEtLjQwMmE3Ljk4IDcuOTggMCAwIDAtLjcwMS0uMzM1bC0uNzMyLS4yNjgtLjc2OC0uMjAxYTcuOTkgNy45OSAwIDAgMC0uNzk1LS4xMjFBOC4wNyA4LjA3IDAgMCAwIDI0IDE2bC0uODE3LjA0LS43OTUuMTIxYTcuOTggNy45OCAwIDAgMC0uNzY4LjIwMWwtLjczMi4yNjgtLjcwMS4zMzUtLjY2MS40MDItLjYxNi40NmMtLjE5OC4xNjMtLjM4Ni4zMzctLjU2Ny41MThsLS41MTguNTY3LS40Ni42MTYtLjQwMi42NjFhNy45OCA3Ljk4IDAgMCAwLS4zMzUuNzAxbC0uMjY4LjczMi0uMjAxLjc2OGE3Ljk5IDcuOTkgMCAwIDAtLjEyMS43OTVBOC4wNyA4LjA3IDAgMCAwIDE2IDI0bC4wNC44MTcuMTIxLjc5NWE3Ljk4IDcuOTggMCAwIDAgLjIwMS43NjhsLjI2OC43MzIuMzM1LjcwMS40MDIuNjYxLjQ2LjYxNmMuMTYzLjE5OC4zMzcuMzg2LjUxOC41NjdsLjU2Ny41MTguNjE2LjQ2LjY2MS40MDJhNy45OCA3Ljk4IDAgMCAwIC43MDEuMzM1bC43MzIuMjY4Ljc2OC4yMDFhNy45OSA3Ljk5IDAgMCAwIC43OTUuMTIxQTguMDcgOC4wNyAwIDAgMCAyNCAzMmwuODE3LS4wNC43OTUtLjEyMWE3Ljk4IDcuOTggMCAwIDAgLjc2OC0uMjAxbC43MzItLjI2OC43MDEtLjMzNS42NjEtLjQwMi42MTYtLjQ2Yy4xOTgtLjE2My4zODYtLjMzNy41NjctLjUxOGwuNTE4LS41NjcuNDYtLjYxNi4yNjMtLjQyNCA2Ljk5NSAzLjg0OGExNi4wMTEgMTYuMDExIDAgMCAxLS41OTQuOTkxIDE2LjAxMSAxNi4wMTEgMCAwIDEtMTAuMTc5IDYuODA0IDE2LjAxMSAxNi4wMTEgMCAwIDEtMTIuMDA5LTIuMzkzIDE2LjAxMSAxNi4wMTEgMCAwIDEtNi44MDQtMTAuMTc5QTE2LjAxMSAxNi4wMTEgMCAwIDEgMTAuNyAxNS4xMWExNi4wMTEgMTYuMDExIDAgMCAxIDEwLjE3OS02LjgwNEExNi4wMTEgMTYuMDExIDAgMCAxIDI0IDh6IiBmaWxsPSIjZmZmIi8+PC9zdmc+
[sdl-badge]: https://img.shields.io/badge/SDL-2.0-gray?style=for-the-badge&logo=data:image/png;base64,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
