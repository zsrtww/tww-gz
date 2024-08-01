# tww-gz
The Wind Waker (SD) ROM hack to practice speedrunning.

To patch an ISO with a patch file, see: [PATCHING.md](./PATCHING.md)  
To build the project from source, see: [BUILDING.md](./BUILDING.md)  
For acknowledgements, see: [THANKS.md](./THANKS.md)  

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

---

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
Modify various parts of the inventory:
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
| Joy Pendants        | Modify the current Joy Pendants count
| Skull Necklaces     | Modify the current Skull Necklaces count
| Boko Baba Seeds     | Modify the current Boko Baba Seeds count
| Golden Feathers     | Modify the current Golden Feathers count
| Knights Crests      | Modify the current Knights Crests count
| Red Chu Jelly       | Modify the current Red Chu Jelly count
| Green Chu Jelly     | Modify the current Green Chu Jelly count
| Blue Chu Jelly      | Modify the current Blue Chu Jelly count

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
<summary>Spoils Bag - Modify Spoils Bag Item Slots</summary>
<br>  
 
| Flag Name           | Description                   
| :--                 | :--    
| Slot 1              | Modify Item in Spoils Bag slot 1
| Slot 2              | Modify Item in Spoils Bag slot 2
| Slot 3              | Modify Item in Spoils Bag slot 3
| Slot 4              | Modify Item in Spoils Bag slot 4
| Slot 5              | Modify Item in Spoils Bag slot 5
| Slot 6              | Modify Item in Spoils Bag slot 6
| Slot 7              | Modify Item in Spoils Bag slot 7
| Slot 8              | Modify Item in Spoils Bag slot 8

</details>

<details>
<summary>Delivery Bag - Modify Delivery Bag Item Slots</summary>
<br>  
 
| Flag Name           | Description                   
| :--                 | :--        
| Slot 1              | Modify Item in Delivery Bag slot 1
| Slot 2              | Modify Item in Delivery Bag slot 2
| Slot 3              | Modify Item in Delivery Bag slot 3
| Slot 4              | Modify Item in Delivery Bag slot 4
| Slot 5              | Modify Item in Delivery Bag slot 5
| Slot 6              | Modify Item in Delivery Bag slot 6
| Slot 7              | Modify Item in Delivery Bag slot 7
| Slot 8              | Modify Item in Delivery Bag slot 8

</details>

<details>
<summary>Bait Bag - Modify Bait Bag</summary>
<br>  
  
| Flag Name           | Description                   
| :--                 | :--        
| Slot 1              | Modify Item in Bait Bag slot 1
| Slot 2              | Modify Item in Bait Bag slot 2
| Slot 3              | Modify Item in Bait Bag slot 3
| Slot 4              | Modify Item in Bait Bag slot 4
| Slot 5              | Modify Item in Bait Bag slot 5
| Slot 6              | Modify Item in Bait Bag slot 6
| Slot 7              | Modify Item in Bait Bag slot 7
| Slot 8              | Modify Item in Bait Bag slot 8

</details>

<details>
<summary>Charts - Modify All Chart Types</summary>
<br>  
 
| Flag Name           | Description                   
| :--                 | :--        
| Special Charts      | Add/Remove Special charts
| Triforce Charts     | Add/Remove/Decipher/Complete Triforce charts
| All Charts          | Add/Remove all charts

</details>

---

### Memory

Watches: View and pin on-screen values at specific memory locations  
TODO: Explain more about how this works

Memory Editor: Edit values at specific memory locations  
TODO: Explain more about how this works

---

### Practice

The practice menu contains hacked save files which allow you to instantly warp to key points in a speedrun route.
The following categories are supported. Click the dropdown to view a list of each save:

<details>
<summary>Any% No MSS</summary>
<br>  

| Save                    | Description                   
| :--                     | :--    
| After Intro             | Just after the intro at bottom of watchtower
| Orca                    | Inside orca's house about to do sword tutorial
| Forest of Fairies       | Inside forest of fairies about to rescue tetra
| Ropes 1                 | Inside pirate ship about to play ropes 1 minigame
| Forsaken Fortress 1     | At start of ff1 before gossip stone cutscene
| Windfall                | At windfall island just finished talking to korl
| Bombs Swim              | At dragon roost island just got the wind waker
| Ropes 2                 | Inside pirate ship about to play ropes 2 minigame
| Forest Haven Swim       | At windfall island about to swim to forest haven
| Deku Tree Cutscene Skip | At forest haven about to do dtcs
| Quiver Swim             | At forest haven about to swim to thorned fairy island
| FF2 Swim                | At thorned fairy island about to swim to ff2
| Helmaroc Skip           | Inside ff2 tower at start of helmaroc king fight
| Barrier Skip            | Outside hyrule castle about to do barrier skip
| Trials Skip             | Inside ganon's tower about to do trials skip
| Puppet Ganon Fight      | Inside ganondorf's bedroom at start of puppet ganon fight
| Morth Hover             | Inside ganondorf's bedroom after fight at top of room
| Ganondorf               | On top of ganondorf's tower at start of ganondorf fight

</details>

<details>
<summary>Any%</summary>
<br>  
 
| Save                        | Description                                    
| :--                         | :--                                           
| Manual Superswim            | Just after the intro, at bottom of watchtower
| Post Manual Superswim       | After MSS at DRI
| Windfall                    | At Windfall Island, post FF1 cutscene
| Sail Skip                   | In KorL near Windfall, after Greatfish cutscene skip
| Ropes 2                     | Inside pirate ship, ropes 2 minigame state
| Forest Haven Swim           | At Windfall Island post bombs for swim to Forest Haven
| Deku Tree Cutscene Skip     | Inside Forest Haven for first time, for DTCS
| Leaf Hover                  | Inside Forest Haven, after DTCS with leaf spawned
| Post Leaf Swim              | Outside Forest Haven, quiver swim or FF2 PG skip swim
| FF2 Swim                    | At Thorned Fairy Island, FF2 swim assuming you got quiver
| Helmaroc Skip               | Inside FF2 Tower, at start of Helmaroc King fight
| Barrier Skip                | Outside Hyrule Castle, about to do barrier skip
| Trials Skip                 | Inside Ganon's Tower, in trials room for trials skip
| Light Arrow Skip            | In Phantom Ganon's room for light arrow skip
| Puppet Ganon Cutscene Skip  | At bottom Grand Staircase for Puppet Ganon cutscene skip
| Puppet Ganon Skip           | Bottom of Ganondorf's Bedroom for Puppet Ganon skip
| Puppet Ganon Fight          | Bottom of Ganondorf's Bedroom, at start of Puppet Ganon fight
| Morth Hover                 | Inside Ganondorf's Bedroom after fight, at top of room
| Ganondorf                   | On top of Ganondorf's Tower, at start of Ganondorf fight

</details>

<details>
<summary>All Dungeons</summary>
<br>  
 
| Save                                | Description                   
| :--                                 | :--        
| Manual Superswim                    | After intro at bottom of tower
| Post Manual Superswim               | After MSS at DRI
| Forsaken Fortress 1 Chest Storage   | FF1 in yellow rupee chest room
| Windfall                            | At Windfall, after FF1 cutscene for sail/tuner/GFCS
| Ropes 2                             | In pirate ship, ropes 2 state
| Forest Haven Swim                   | At Windfall for swim to Forest Haven
| Early Leaf Hover                    | Outside Forest Haven for hover to higher entrance
| Deku Tree Cutscene Skip             | Inside Forest Haven upper spawn for cutscene skip
| Forbidden Woods                     | Start of Forbidden Woods
| Kalle Demos                         | Kalle Demos boss fight
| Enter Dragon Roost Cavern           | Outside Forest Haven for swim to ETI/DRI
| Dragon Roost Cavern                 | Start of DRC
| DRC Miniboss                        | Outside area of DRC
| DRC Boss Key Skip                   | Inside DRC in boss door room for BK skip
| Gohma                               | Gohma boss fight
| Nayru's Pearl                       | At DRI after DRC for balloon swim to Outset
| Enter Tower of the Gods             | Outside Jabuun's Cave for swim to STI/NTI
| Tower of the Gods                   | Start of TOTG
| Darknut                             | Darknut miniboss
| TOTG Third Statue                   | TOTG after returning second statue
| Gohdan                              | Gohdan boss fight
| Puzzle Skip                         | Inside Hyrule Castle for puzzle skip
| Hyrule Escape                       | Inside Hyrule Castle after Master Sword for Hyrule escape
| Barrier Skip                        | Outside Hyrule Castle for barrier skip
| Trial Skip                          | Inside Ganon's Tower, in trials room for trials skip
| Boomerang Skip                      | In Phantom Ganon's room for boomerang skip
| Phantom Ganon                       | Phantom Ganon fight miniboss
| Enter Helmaroc                      | After Phantom Ganon fight for chest storage climb
| Hyrule 2 Skip                       | In Helm boss fight for EMS cutscene skip
| Early Wind God's Aria               | At Windfall after FF2 for swim to Gale Isle
| Power Bracelets                     | At Fire Mountain for power bracelets
| Early Earth Temple                  | At Headstone for early Earth Temple
| Earth Temple                        | Start of Earth Temple
| Song Stone Skip                     | In Earth Temple in song stone room
| Jalhalla                            | Jalhalla boss fight
| Iron Boots                          | At Headstone for swim to Ice Ring for Iron Boots
| Makar                               | At Ice Ring for swim to Forest Haven for Makar
| Enter Wind Temple                   | At Forest Haven for balloon swim to Gale Isle
| Wind Temple                         | Start of Wind Temple
| Wizzrobe                            | Wizzrobe miniboss
| After Hookshot                      | Wind Temple after Hookshot
| Molgera                             | Molgera boss fight
| Swim to Flight Control Platform     | At Gale Isle for swim to Flight Control Platform
| FCP Layer Manip                     | At Flight Control Platform for layer manip dark portal
| Puppet Ganon Cutscene Skip          | In Grand Staircase for Puppet Ganon cutscene skip
| Puppet Ganon Skip                   | In Puppet Ganon room on layer 8 for Puppet Ganon skip
| Puppet Ganon                        | Puppet Ganon fight if not doing PG skip
| Ganondorf                           | Ganondorf boss fight

</details>

---

### Scene

#### Change/view various properties of the scene

| Option              | Description                   
| :--                 | :--    
| Disable BG Music    | Disable background music from playing    
| Freeze Time         | Freeze the current time of day 
| Wind Direction      | Change current wind direction
| Chart Set           | Change current chart set of file
| Current Hour        | Change current hour
| Current Minutes     | Change current minute
| Current Date        | Change current date/moon phase
  
#### Collision Viewer - view various types of collision

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
