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

![C](https://img.shields.io/badge/C-11-gray?&style=for-the-badge)
![SDL](https://img.shields.io/badge/SDL-2.0-gray?&style=for-the-badge)

## Visuals

https://github.com/user-attachments/assets/3e2f366a-ae1f-41ac-88ca-ad17770a3e6a

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

- Install the **C/C++** extension by Microsoft from the Extensions tab (Ctrl+Shift+X).

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
