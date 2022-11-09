# tww-gz
Name pending.
The Wind Waker (SD) ROM hack to practice speedrunning.

This Practice ROM is in very early development. If you've come across this page (somehow) prior to the first release and are looking for a workable practice ROM
please use "tww.zip" pinned in the "Rom hacks" channel in the wind waker speedrun discord https://discord.gg/Sj5aehU

This practice rom requires the NTSC-J ISO to run (GZLJ-01)

You MUST name your iso GZLJ01.iso or the script will not work to read and patch your iso.

WHAT YOU NEED (aside from the code given here)

Firstly, you'll need the iso for the game. This can be ripped from your disc (which you obviously have) by using CleanRip, a Wii Homebrew app. After you get the iso, place it into the root of your `tww-gz` folder.

From there, you'll need DevKitPro which you can find on [windows here](https://github.com/devkitPro/installer/releases), or for mac/linux read [this guide](https://devkitpro.org/wiki/Getting_Started)

Next, you'll need the latest version of the [Romhack Compiler](https://github.com/zsrtp/romhack-compiler/releases). Install the gc version, since wind waker is a gamecube game.

You'll need to put the romhack compiler in the root of your `tww-gz` folder

BUILDING THE ROM

Currently, the rom will only work built with the command line, note: do NOT use powershell on windows, only the command prompt.

After launching the command prompt, make your way to the root directory of your GZ folder

`make`

followed by

`romhack build --raw`

From here you should have a .iso file in your `build` folder labeled twwgz.iso


CREDITS:
Credits to everyone involved in the making of tww-gz, this includes CGF95, Glubbers_, and TakaRikka.

Taka deserves a special congratulations for the work done, providing us with the entire framework ported over from [Twilight Princess' Practice Rom](https://tpgz.io). Without Taka's help, this project would likely have never gotten off the ground.

And special thanks to TrogWW, for the work he's done previously on earlier renditions of the practice rom, and for all the work he's done for the Wind Waker community.

Thank you to the teams behind the Romhack Compiler and DevKitPro, without them this would not be nearly as readily possible as it is.

Thank you to the TPGZ dev team, who's work we were graciously allowed to use for the base of our own practice rom.

And finally, thank you to the Wind Waker community being so awesome.
