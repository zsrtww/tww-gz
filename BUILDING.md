# Building

For simply using tww-gz as is, patch your ISO using the romhack-patcher application, which is included in our official releases.

These instructions are meant for people that want to make their own custom builds or need an alternate method for building the rom.

## Compiling

1.  Clone the repo locally.

```bash
git clone https://github.com/zsrtww/tww-gz.git
```

2.  Copy your The Wind Waker NTSC-J ISO into the root 'tww-gz' folder.  You will need to rename the ISO to GZLJ01.iso.  No other version of the game will work.

    - The ISO can be ripped from your disc (which you obviously have) by using CleanRip, a Wii Homebrew app.

3.  Install DevKitPro which can be found on [windows here](https://github.com/devkitPro/installer/releases), or for mac/linux read [this guide](https://devkitpro.org/wiki/Getting_Started)

4.  Download the latest version of the [Romhack Compiler](https://github.com/zsrtp/romhack-compiler/releases). Install the gc version, since The Wind Waker is a Gamecube game.

    - Put the romhack compiler in the root of your `tww-gz` folder.
    - The rom will only work built with the command line.
        - Note:  Do NOT use powershell on windows, only the command prompt.

5.  Launch a terminal and go to the root 'tww-gz' directory.

6.  Run `make` to compile the code.

7.  Run `romhack build --raw` to create a new ISO with our changes applied.

    - The new .iso file is located at `build/twwgz.iso`.

## Using Patches

Patch files are a convenient way to share your changes with others.

- To create a patch, run:

  ```
  romhack build --raw --patch
  ```

  The new patch file is located at `build/twwgz.patch`.

- To apply a patch, run:

  ```
  romhack apply <example.patch> <input.iso> <output.iso>
  ```

  Your patched ISO will be named \<output.iso>.