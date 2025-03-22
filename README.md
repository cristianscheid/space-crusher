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

[c-badge]: https://img.shields.io/badge/C-C11-gray?style=for-the-badge&logo=data:image/svg+xml;base64,PHN2ZyB4bWxucz0iaHR0cDovL3d3dy53My5vcmcvMjAwMC9zdmciIHZpZXdCb3g9IjAgMCA0OCA0OCIgd2lkdGg9IjI0IiBoZWlnaHQ9IjI0IiBmaWxsLXJ1bGU9ImV2ZW5vZGQiIHhtbG5zOnY9Imh0dHBzOi8vdmVjdGEuaW8vbmFubyI+PHBhdGggZD0iTTI0IDBhMi41NiAyLjU2IDAgMCAwLTEuMjU0LjMyNkwzLjU0IDExLjEwN2MtLjc3Ni40MzUtMS4yNTQgMS4yNDEtMS4yNTQgMi4xMTJ2MjEuNTYyYTIuNDMgMi40MyAwIDAgMCAxLjI1NCAyLjExMmwxOS4yMDUgMTAuNzgxYy43NzUuNDM1IDEuNzMzLjQzNSAyLjUwOSAwTDQ0LjQ2IDM2Ljg5MmMuNzc2LS40MzUgMS4yNTQtMS4yNDEgMS4yNTQtMi4xMTJWMTMuMjE5YTIuNDIzIDIuNDIzIDAgMCAwLS4wMjItLjEyOWMtLjAzMi0uNDk0LS4xNDgtMS4wMDYtLjUzNi0xLjM5M2EyLjQyMyAyLjQyMyAwIDAgMC0uNjk2LS41ODlMMjUuMjU0LjMyNkMyNC44NjcuMTA4IDI0LjQzMyAwIDI0IDB6bTAgOGExNi4wMTEgMTYuMDExIDAgMCAxIDExLjMxMiA0LjY4OCAxNi4wMTEgMTYuMDExIDAgMCAxIDEuOTg3IDIuNDI0IDE2LjAxMSAxNi4wMTEgMCAwIDEgLjQ1NS43NjNMMzAuODMgMTkuODNsLS4xOTYtLjMwNC0uNDYtLjYxNi0uNTE4LS41NjctLjU2Ny0uNTE4LS42MTYtLjQ2LS42NjEtLjQwMmE3Ljk4IDcuOTggMCAwIDAtLjcwMS0uMzM1bC0uNzMyLS4yNjgtLjc2OC0uMjAxYTcuOTkgNy45OSAwIDAgMC0uNzk1LS4xMjFBOC4wNyA4LjA3IDAgMCAwIDI0IDE2bC0uODE3LjA0LS43OTUuMTIxYTcuOTggNy45OCAwIDAgMC0uNzY4LjIwMWwtLjczMi4yNjgtLjcwMS4zMzUtLjY2MS40MDItLjYxNi40NmMtLjE5OC4xNjMtLjM4Ni4zMzctLjU2Ny41MThsLS41MTguNTY3LS40Ni42MTYtLjQwMi42NjFhNy45OCA3Ljk4IDAgMCAwLS4zMzUuNzAxbC0uMjY4LjczMi0uMjAxLjc2OGE3Ljk5IDcuOTkgMCAwIDAtLjEyMS43OTVBOC4wNyA4LjA3IDAgMCAwIDE2IDI0bC4wNC44MTcuMTIxLjc5NWE3Ljk4IDcuOTggMCAwIDAgLjIwMS43NjhsLjI2OC43MzIuMzM1LjcwMS40MDIuNjYxLjQ2LjYxNmMuMTYzLjE5OC4zMzcuMzg2LjUxOC41NjdsLjU2Ny41MTguNjE2LjQ2LjY2MS40MDJhNy45OCA3Ljk4IDAgMCAwIC43MDEuMzM1bC43MzIuMjY4Ljc2OC4yMDFhNy45OSA3Ljk5IDAgMCAwIC43OTUuMTIxQTguMDcgOC4wNyAwIDAgMCAyNCAzMmwuODE3LS4wNC43OTUtLjEyMWE3Ljk4IDcuOTggMCAwIDAgLjc2OC0uMjAxbC43MzItLjI2OC43MDEtLjMzNS42NjEtLjQwMi42MTYtLjQ2Yy4xOTgtLjE2My4zODYtLjMzNy41NjctLjUxOGwuNTE4LS41NjcuNDYtLjYxNi4yNjMtLjQyNCA2Ljk5NSAzLjg0OGExNi4wMTEgMTYuMDExIDAgMCAxLS41OTQuOTkxIDE2LjAxMSAxNi4wMTEgMCAwIDEtMTAuMTc5IDYuODA0IDE2LjAxMSAxNi4wMTEgMCAwIDEtMTIuMDA5LTIuMzkzIDE2LjAxMSAxNi4wMTEgMCAwIDEtNi44MDQtMTAuMTc5QTE2LjAxMSAxNi4wMTEgMCAwIDEgMTAuNyAxNS4xMWExNi4wMTEgMTYuMDExIDAgMCAxIDEwLjE3OS02LjgwNEExNi4wMTEgMTYuMDExIDAgMCAxIDI0IDh6IiBmaWxsPSIjNWM2YmMwIi8+PC9zdmc+
[sdl-badge]: https://img.shields.io/badge/SDL-2.0-gray?style=for-the-badge&logo=data:image/png;base64,iVBORw0KGgoAAAANSUhEUgAAABgAAAAYCAMAAADXqc3KAAABLFBMVEUAAAAAAP+AgP9VVapAgL9mZsxVgNVtbbZgYL9VccZVar9bbchaacNVccZea7xhbcJdaMVYasFeb8Rcar9cab5ZbL9bbcJfa75daL9cbb5ebcFaab5basBbbL5ear9cbcBcbL9aasBdbMFbbMBcab5ba79cbL9dbMBbbMFcasBbbMFcasFbbL9da8BcbMBba8FdbMFca79basBdbMFcasFdasBbasFcbL9bar9bbMFcasBba8BcasFca79casFcbMBda8BcbMFba79ca8Bcar9ca8Bba8Bca8Bca8BbbMBca8Bda8Bca8Bba8Fca8BcasBca8Fca8Bca8Bca8Bca8Bba8BcasBca8Bca8Bca8Bca8Bca8Bca8Bca8Bca8Bca8Bca8Bca8Bca8D///+hr8keAAAAYnRSTlMAAQIDBAUGBwgJDA4REhMVFh0eJCcoKissLzEzNTs8PUBBQklLTFBVV1laW1xdYWJjZGVmZ3FzdHh7fX5/iIuOkpOUmZyen6mqrbKzt7jBwsTFys3S1Nrd3uPl6/X29/n7/D0ij78AAAABYktHRGNcvi2qAAAA5klEQVQYGc3BZ1bCQBQG0C8JVYOgokbBBhhLqCpGQbHEElvszoATAm//izCHOfjDFXAvJtRMyVxWjFwuqwLGCkLROQ3Angj61GZE1LXABUYKaaAbpLQ1k/X19e9hngtIzSS+6LOzCuYDNTrnApLRxtJzQGQzHyjRNReQlDcsIlElj/nALTW4gKT/YHjfuqMTNnBeyYvxgeM4CFke7If3pwP10nVvynFcuSEAid4mpIbVNA/L9apd3N/VMP/SwpgShRSDWvmoYWRqNo0/qaPHTgZj0wv5ja3tncrx6cVZMY5/InoSE+IXjFwmcP46rYcAAAAASUVORK5CYII=
