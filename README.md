# Mint CE

A small Linux Mint-inspired desktop simulation for the TI-84 Plus CE, written in C. Four keyboard-operated views demonstrate a launcher, terminal command previews, a sample file listing, and system information on a 320×240 display.

It runs as a native calculator program. The terminal and files are simulated; it cannot boot Linux or execute Linux applications.

## Build

Install the [CE C/C++ Toolchain](https://ce-programming.github.io/toolchain/) and put its `bin` directory on your PATH:

```sh
make
```

The result is `bin/MINTCE.8xp`. GraphX and KeypadC come from the toolchain; the repository does not vendor the toolchain or its dependencies. The release copy also includes the rebuilt program under `release/`.

Transfer the program using TI Connect CE. Your calculator must support running native CE programs; the launch procedure depends on its OS version and installed launcher. This release was compiled locally but has not been run on a physical calculator during the release review.

## Controls

| Key | Action |
| --- | --- |
| Left / Right | Switch columns in the 2×2 launcher |
| Up / Down | Switch rows |
| 2nd / Enter | Open the selected view |
| Clear | Return to desktop; exit from desktop |
| Left / Right in terminal | Select a command preview |

The terminal offers `neofetch`, `uname -a`, `free`, and `clear` previews. Reported Linux details are illustrative. The Files view is a sample listing and does not enumerate calculator variables.

## Implementation

`src/main.c` defines a fixed palette, small drawing helpers, and independent view loops. Key release handling prevents a held Enter from immediately activating the next view. The launcher uses a real 2×2 layout so arrow navigation matches the visible arrangement. Idle terminal input waits avoid repeatedly repainting the screen.

Before a hardware release, check every launcher direction, opening and closing all four views, holding Enter/Clear, terminal selection, and returning to the calculator OS. The current build emits upstream linker warnings about GNU-stack metadata; it completes successfully.

MIT licensed source. Linux Mint is referenced as the visual inspiration; the project is independently developed and is not affiliated with Linux Mint.
