# tww-gz
The Wind Waker (SD) ROM hack to practice speedrunning.

To patch an ISO with a patch file, see: PATCHING.md  
To build the project from source, see: [BUILDING.md](./BUILDING.md)  
For acknowledgements, see [THANKS.md](./THANKS.md)

If you have questions or need help, ask in the [#practice-rom-development](https://discord.com/channels/136347487710609409/830218819695673405) channel of the [Wind Waker Speedrunning Discord](https://discord.gg/Sj5aehU).

## Controls
| Button(s)          | Description   
| :---               | :---          
| L + R + D-pad down | Open menu     
| D-pad directions   | Navigate menus
| A                  | Select        
| B                  | Go back       

Some features have specific button combinations associated with them.
See the features section for more details.

## Features
- [Cheats](#Cheats)
- [Flags](#Flags)
- [Inventory](#Inventory)
- [Memory](#Memory)
- [Practice](#Practice)
- [Scene](#Scene)
- [Settings](#Settings)
- [Tools](#Tools)

### Cheats
Enable and disable specific cheats. Some cheats are applied constantly, and some need a button combination to use.
<details>
<summary>See the table below for a description of each cheat</summary>
<br>  

| Cheat             | Description                                        
| :---              | :---                                               
| Infinite air      | Always have max air                                
| Infinite arrows   | Always have max arrows                             
| Infinite bombs    | Always have max bombs                              
| Infinite hearts   | Always have full hearts                            
| Refill hearts     | Hold R+D-pad right to refill health                
| Infinite magic    | Always have full magic                             
| Refill magic      | Hold L+D-pad up to refill magic                    
| Infinite rupees   | Always have infinite rupees                        
| Moon jump         | Hold R+A to moon jump                              
| Storage           | Press D-pad right to get storage                   
| Normal collision  | Hold L+D-pad down to get normal collision          
| Chest storage     | Hold L+D-pad right to get chest storage            
| Door cancel       | Hold L+D-pad left to get door cancel               
| Quarter heart     | Hold R+D-pad left to reduce health to quarter heart
| Fast movement     | Hold D-pad left to get super speed                 
| Upcharge          | Hold X + Z to get negative speed for upcharge      

</details>  

---

### Flags
Set and unset various flags in the game.

<details>
<summary> General - Flags that are most relevant or important</summary>
<br>  

| Flag Name                   | Description                                                    
| :--                         | :--                                                            
| FF2 Helmaroc Cutscene       | Switches to animation set 2, among other things                
| FF1 Gossip Stone Trigger    | Sets Pirate Ship to layer 2 (Ropes 2) and Outset to layer 4    
| Endless Night		          | Activates Endless Night, incompatible with having Nayru's Pearl
| Raise ToTG                  | Raises Tower of the Gods                                       
| Load ToTG After T2Z         | Sets FF3 Layer and F&I Arrows at Mother & Child                
| Hyrule 3 Warp               | Opens golden warp to Hyrule 3                                  
| Hyrule Barrier              | Barrier Skip skip                                              
| Dark Portal                 | Opens dark portal between FF3 and Ganon's Tower                
| Sea Chart                   | Gives the sea chart                                            
</details>

<details>
<summary> Dungeons - Flags related to dungeon collectables</summary>
<br>  

| Flag Name           | Description                                                     
| :--                 | :--                                                             
| dungeon <"name">    | Change the dungeon being modified
| keys <"amount">	  | Modify the number of small keys
| boss key		      | Gives the boss key
| map                 | Gives the dungeon map
| compass             | Gives the dungeon compass
| partner             | Spawns Medli/Makar (ET/WT Only)
</details>

<details>
<summary> Savewarp - Flags related to savewarp locations (higher tiers take priortiy)</summary>
<br>  

| Flag Name                           | Description                                                     
| :--                                 | :--           
| Leaving Outset Cutscene             | Sets savewarp location to Pirate Ship (Overworld Travelling)
| Tetra Text After Getting Spoils Bag | Sets savewarp location to Pirate Ship (At FF1)
| Barrel Launch Cutscene		      | Sets savewarp location to FF1
| Post FF1 KorL Cutscene              | Sets savewarp location to Windfall, spawns KorL, and sets FoF to layer 2
| Enter KorL First Time               | Sets savewarp location to most recent loaded area                                                  

</details>

<details>
<summary> Tuner - Flags related to tingle tuner</summary>
<br>  

| Flag Name           | Description                                                     
| :--                 | :--                                                             
| Kooloo-Limpah 10s Balloon+Shield	| Adds the 10s Balloon+Shield to the Kooloo-Limpah pool
| Tingle Balloon Discount           | Gives Tingle Balloon Discount from 30 to 20 rupees
| Tings Discount                    | Gives 50 percent off discount for all tings
| Hand-Me-Down Tingle Tuner         | Unlocks the Hand-Me-Down Tingle Tuner item in the tuner shop

</details>

---

### Inventory
Modify various parts of the inventory
<details>
<summary>Amounts - Modify amounts for health, magic, etc.</summary>
<br>  

| Flag Name           | Description                   
| :--                 | :--        
| Health              | Modify the current health by quarter
| Bombs               | Modify the current bomb count
| Arrows              | Modify the current arrow count
| Rupees              | Modify the current rupee count
| Magic               | Modify the current magic amount
| Heart Pieces        | Modify the current heart pieces collected

</details>

<details>
<summary>Item Inventory - Modify Item Inventory Menu</summary>
<br>  

| Flag Name             | Description                   
| :--                   | :--        
| Telescope             | Add/remove telescope to/from inventory
| Sail                  | Add/remove sail to/from inventory
| Wind Waker            | Add/remove wind waker to/from inventory
| Grappling Hook        | Add/remove grappling hook to/from inventory
| Spoils Bag            | Add/remove spoils bag to/from inventory
| Boomerang             | Add/remove boomerang to/from inventory
| Deku Leaf             | Add/remove deku leaf to/from inventory
| Tingle Tuner          | Add/remove tingle tuner to/from inventory
| Progressive Picto Box | Add/remove/upgrade picto box
| Iron Boots            | Add/remove iron boots to/from inventory
| Magic Armor           | Add/remove magic armor to/from inventory
| Bait Bag              | Add/remove bait bag to/from inventory
| Progressive Bow       | Add/remove/upgrade bow
| Bombs                 | Add/remove bombs to/from inventory
| Bottle 1              | Add/remove bottle 1 to/from inventory
| Bottle 2              | Add/remove bottle 2 to/from inventory
| Bottle 3              | Add/remove bottle 3 to/from inventory
| Bottle 4              | Add/remove bottle 4 to/from inventory
| Delivery Bag          | Add/remove delivery bag to/from inventory
| Hookshot              | Add/remove hookshot to/from inventory
| Skull Hammer          | Add/remove skull hammer to/from inventory

</details>

<details>
<summary>Quest Status - Modify Quest Status Menu</summary>
<br>  

| Flag Name           | Description                   
| :--                 | :--        
| Sword               | Add/remove/upgrade sword
| Shield              | Add/remove/upgrade shield
| Magic               | Add/remove/upgrade magic
| Quiver              | Add/remove/upgrade quiver
| Hurricane Spin      | Add/remove Hurricane Spin
| Hero's Clothes      | Add/remove Hero's Clothes
| Bomb Bag            | Add/remove/upgrade bomb bag
| Power Bracelets     | Add/remove power bracelets from inventory
| Pirate's Charm      | Add/remove pirate's charm from inventory
| Hero's Charm        | Add/remove hero's charm from inventory
| Wind's Requiem      | Add/remove wind's requiem from songs list
| Ballad of Gales     | Add/remove ballad of gales from songs list
| Command Melody      | Add/remove command melody from songs list
| Earth God's Lyric   | Add/remove earth god's lyric from songs list
| Wind God's Aria     | Add/remove wind god's aria from songs list
| Song of Passing     | Add/remove song of passing from songs list
| Din's Pearl         | Add/remove din's pearl from inventory
| Farore's Pearl      | Add/remove farore's pearl from inventory
| Nayru's Pearl       | Add/remove nayru's pearl from inventory
| Triforce Piece 1    | Add/remove triforce piece 1 from inventory
| Triforce Piece 2    | Add/remove triforce piece 2 from inventory
| Triforce Piece 3    | Add/remove triforce piece 3 from inventory
| Triforce Piece 4    | Add/remove triforce piece 4 from inventory
| Triforce Piece 5    | Add/remove triforce piece 5 from inventory
| Triforce Piece 6    | Add/remove triforce piece 6 from inventory
| Triforce Piece 7    | Add/remove triforce piece 7 from inventory
| Triforce Piece 8    | Add/remove triforce piece 8 from inventory

</details>

<details>
<summary>Spoils Bag - Modify Spoils Bag Items/Amounts</summary>
<br>  

TODO: create table  
| Flag Name           | Description                   
| :--                 | :--        


</details>

<details>
<summary>Delivery Bag - Modify Delivery Bag</summary>
<br>  

TODO: create table  
| Flag Name           | Description                   
| :--                 | :--        


</details>

<details>
<summary>Spoils Bag - Modify Spoils Bag</summary>
<br>  

TODO: create table  
| Flag Name           | Description                   
| :--                 | :--        


</details>

<details>
<summary>Bait Bag - Modify Bait Bag</summary>
<br>  

TODO: create table  
| Flag Name           | Description                   
| :--                 | :--        


</details>

<details>
<summary>Charts - Modify All Chart Types</summary>
<br>  

TODO: create table  
| Flag Name           | Description                   
| :--                 | :--        


</details>

---

### Memory

- memory editor menu            // View/edit memory
- watches menu                  // Manage memory watches

---

### Practice

The practice menu contains hacked save files which allow you to instantly warp to key points.
The following categories are supported. Click the dropdown to view a list of each save:

- any% no mss menu              // Load an any% no mss save
- any% menu			            // Load an any% save
- all dungeons saves	        // Load an all dungeons save

---

### Scene

Changeor view various properties about the scene
| Option              | Description                   
| :--                 | :--    
| Disable BG Music    | Disable background music from playing    
| Freeze Time         | Freeze the current time of day 
| Wind Direction      | Change current wind direction
| Chart Set           | Change current chart set of file
| Current Hour        | Change current hour
| Current Minutes     | Change current minute
| Current Date        | Change current date/moon phase

<details>
<summary>Collision Viewer - view various types of collision</summary>
<br>  

| Option              | Description                   
| :--                 | :--    
| Attack Colliders    | View hitboxes; Colliders that hurt Target Colliders
| Target Colliders    | View hurtboxes; Colliders that get hurt by Attack Colliders
| Push Colliders      | View colliders that allow actors to bump/push into each other
| Ground Polys        | View floor collision polygons
| Roof Polys          | View ceiling collision polygons
| Wall Polys          | View wall collision polygons
| Poly Edges          | View edges of each polygon
| Poly Draw Raise     | Amount to raise the drawn polygons by
| Opcaity             | Transparency amount of collision viewer

</details>

---

### Settings

| Option                 | Description                   
| :--                    | :--    
| Cursor Color           | Change cursor color
| Font                   | Change font
| Drop Shadows           | Add shadows to all font characters
| Item Equip Priorities  | Adjust priorities on item equips in practice saves
| Save Card              | Save settings to memory card
| Load Card              | Load settings from memory card
| Delete Card            | Delete settings on memory card

---

### Tools

| Option                 | Description                   
| :--                    | :--    
| Link Debug Info        | Display position and angle data for Link
| Display Time Info      | Display current day, time and moon phase
| Teleport               | R+D-pad up to save position. R+D-pad down to load
| Area Reload            | Reload the current room by pressing L + R + A + Start
| Map Aelect             | Load Map Select by holding D-pad down + Y + Z
| Zombie Hover Info      | Display A and B button presses per second
| Input Viewer           | Show current inputs
| ESS Checker            | Change input viewer stick color based on distance from perfect ess
| Deadzone Checker       | Change input viewer stick coor if stick is in deadzone
| Intro Skip             | Skip lore segment of intro on start of new file
