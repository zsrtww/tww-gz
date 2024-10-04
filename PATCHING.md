# Patching an ISO Using a Patch File

Patch files allow for easy distribution of tww-gz builds without needing to distribute entire ISO files.  

## In Browser Using Web Romhack Patcher
This is the preferred method, super streamlined and automated

1. Go to the [ISO Patcher](https://geckopatcher.net/) website
<br/>

2. Provide your own ISO (JP,ENG,PAL) as well as the corresponding patch provided with this release.
<br/>

3. Press the Patch button and an iso names "output.iso" will appear in your downloads when complete. Rename however you desire.
<br/>

## On Personal Computer Using Command Prompt or .bat Script

(Note that stable releases include a .bat script for patching on Windows that automates this process, skipping steps 5 and 6)
1. Download the [ROM Hack Compiler](https://github.com/zsrtp/romhack-compiler/releases)  
  Make sure to download the GameCube version denoted by "gc"
    - `romhack-vx.x.x-r2-windows-x64-gc.zip` for Windows
    - `romhack-vx.x.x-r2-linux-x64-gc.zip` for Linux  
<br/>

2. Place a TWW ISO in the same folder as the ROM Hack Compiler executeable, and rename it according to the following:  
    - NTSCJ (JP): `GZLJ01.iso`
    - NTSCU (ENG): `GZLE01.iso`
    - PAL: `GZLP01.iso`  
<br/>

3. Place the corresponding patch file provided to use in the same folder as the ROM Hack Compiler + ISO  
<br/>

4. Run the .bat Script here and a patched rom will be created in the same folder.

Do the steps bellow if not using the .bat script

5. Open a Command Prompt/Terminal in the folder that contains the ISO, compiler, and patch file
    - On windows, you can click on the folder path bar at the top of Windows Explorer and type "cmd" and hit enter to open a Command Prompt in the current folder  
<br/>

6. Run the following command (this example is for Windows): `romhack.exe apply <patch-filename> <input ISO name> <output ISO name>`
    - The patched rom will be created with the filename as <output ISO name> from above
