# Building

For simply using tww-gz as is, patch your ISO using the romhack-patcher application, which is included in our official releases.

These instructions are meant for people that want to build from source for development work

## Setting Up Build Environment

The current build setup works best in a Linux environment. For Windows Users it is reccomended to use [WSL](https://learn.microsoft.com/en-us/windows/wsl/install). These instructions will assume the use of WSL within Windows, but can be easily adapted for use on native Linux.

Additionally, Dev Containers work with the [VSCode](https://code.visualstudio.com/) text editor. After VSCode is installed, install the following extensions:  
    - [WSL Extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-wsl)  
    - [Dev Containers](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-containers)

Lastly, [Docker](https://www.docker.com/products/docker-desktop/) will be needed to run the Dev Container. The desktop app for Docker works fine.  
  - After Docker Desktop is installed, ensure that the "Use the WSL 2 based engine" checkbox is enabled in settings  
<br/>  

After WSL and VSCode is installed, and a terminal is available, the following instructions can be used:

1. Fork the repo, and clone the repo locally.

    ```bash
    git clone https://github.com/<your-username>/tww-gz.git
    ```
<br/>  

2. Place the ROM Hack Compiler executeable into the root `tww-gz/` folder.
    - You can open a File Explorer window in the current WSL location by typing `explorer.exe .`  
<br/>  

3. Place a TWW ISO into the `isos` folder, and rename it according to the following:  
    - NTSCJ: `GZLJ01.iso`
    - NTSCE: `GZLE01.iso`
    - PAL: `GZLP01.iso`  
<br/>  

4. Type `code .` to open a VSCode Window from the `tww-gz/` root folder. Opening VSCode from WSL will open VSCode in a linked "WSL Mode", which is required for building.
<br/>  

5. After VSCode opens, there should be a pop-up in the bottom right corner of the screen that prompts you to restart VSCode in Dev Container mode. 
    - If this pop up does not appear, make sure all previous steps were followed correctly, including installing Docker and the proper VSCode extensions.  
<br/>  

6. At this point, VSCode tasks can be used to Build the project. This can be done by
    - Clicking Terminal > Run Task... > Select Task > Select Version
    - Running contrl+P, typing "task " and then typing or selecting an appropriate task  

    Note that the first time the task runs, the setup process can take a long time.  
<br/>

7. The resulting build artifacts will be generated in a corresponding build folder, for example in `build_ntscj/`