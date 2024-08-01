# Patching an ISO Using a Patch File

Patch files allow for easy distribution of tww-gz builds without needing to distribute entire ISO files.

1. Download the [ROM Hack Compiler](https://github.com/zsrtp/romhack-compiler/releases)
  - Make sure to download the GameCube version denoted by "gc"
    - `romhack-vx.x.x-r2-windows-x64-gc.zip` for Windows
    - `romhack-vx.x.x-r2-linux-x64-gc.zip` for Linux  
<br/>

2. Place a TWW ISO in the same folder as the ROM Hack Compiler executeable  
<br/>

- Rename the ISO to the Game ID that corresponds to the version
  - NTSCJ: `GZLJ01.iso`
  - NTSCE: `GZLE01.iso`
  - PAL: `GZLP01.iso`  
<br/>

3. Place a patch file in the same folder as the ROM Hack Compiler and ISO  
<br/>

4. Open a Command Line/Terminal in the folder that contains the ISO, compiler, and patch file
  - On windows, you can click on the folder path bar at the top of windows explorer and type "cmd" and hit enter to open a Command Prompt in the current folder  
<br/>

5. Run the following command (this example is for Windows): `romhack.exe apply <patch-filename> <input ISO name> <output ISO name>`
- The patched rom will be created with the filename as `<output ISO name>` from above