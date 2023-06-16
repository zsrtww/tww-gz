# tww-gz
The Wind Waker (SD) ROM hack to practice speedrunning.

Patch your ISO using the romhack-patcher application, which is included in our official releases.

⚠️ tww-gz is still in early development.<br>
If you have questions or need help, ask in the [#practice-rom-development](https://discord.com/channels/136347487710609409/830218819695673405) channel of the [Wind Waker Speedrunning Discord](https://discord.gg/Sj5aehU).

## Features

Use L + R + D-pad down to open the main menu which contains the following options:

```
cheats menu:
- infinite air                  // Always have max air
- infinite arrows               // Always have max arrows
- infinite bombs                // Always have max bombs
- infinite hearts               // Always have full hearts
- infinite magic                // Always have full magic
- infinite rupees               // Always have infinite rupees
- moon jump                     // Hold R+A to moon jump
- storage                       // Press D-pad right to get storage
- normal collision              // Hold L+D-pad down to get normal collision
- chest storage                 // Hold L+D-pad right to get chest storage
- door cancel                   // Hold L+D-pad left to get door cancel
- quarter heart                 // Hold R+D-pad left to reduce health to quarter heart
- fast movement                 // Hold D-pad left to get super speed
- upcharge                      // Hold X + Z to get negative speed for upcharge

flags menu:
- important flags menu		//Flags that are most relevant or important
- cutscene flags menu		//Cutscene flags
- *quest flags menu		//Flags related to certain sidequests and heart pieces

important flags menu:
- Watched FF2 Helmaroc Cutscene // Switches to animation set 2, among other things
- Have Hurricane Spin		// Gives Hurricane Spin
- Endless Night			// Activates Endless Night, incompatible with having Nayru's Pearl

inventory menu:
- amounts menu                  // Modify amounts for health, magic, etc.
- item inventory menu           // Modify item inventory menu
- quest status menu             // Modify quest status menu
- *spoils menu                  // Modify spoils bag items/amounts
- *delivery bag menu            // Modify delivery bag

amounts menu:
- health                        // Modify the current health by quarter
- bombs                         // Modify the current bomb count
- arrows                        // Modify the current arrow count
- rupees                        // Modify the current rupee count
- magic                         // Modify the current magic amount
- heart pieces                  // Modify the current heart pieces collected

item inventory menu:
- Telescope                     // Add/remove telescope to/from inventory
- Sail                          // Add/remove sail to/from inventory
- Wind Waker                    // Add/remove wind waker to/from inventory
- Grappling Hook                // Add/remove grappling hook to/from inventory
- Spoils Bag                    // Add/remove spoils bag to/from inventory
- Boomerang                     // Add/remove boomerang to/from inventory
- Deku Leaf                     // Add/remove deku leaf to/from inventory
- Tingle Tuner                  // Add/remove tingle tuner to/from inventory
- Progressive Picto Box         // Add/remove/upgrade picto box
- Iron Boots                    // Add/remove iron boots to/from inventory
- Magic Armor                   // Add/remove magic armor to/from inventory
- Bait Bag                      // Add/remove bait bag to/from inventory
- Progressive Bow               // Add/remove/upgrade bow
- Bombs                         // Add/remove bombs to/from inventory
- Bottle 1                      // Add/remove bottle 1 to/from inventory
- Bottle 2                      // Add/remove bottle 2 to/from inventory
- Bottle 3                      // Add/remove bottle 3 to/from inventory
- Bottle 4                      // Add/remove bottle 4 to/from inventory
- Delivery Bag                  // Add/remove delivery bag to/from inventory
- Hookshot                      // Add/remove hookshot to/from inventory
- Skull Hammer                  // Add/remove skull hammer to/from inventory

quest status menu:
- Sword                         // Add/remove/upgrade sword
- Shield                        // Add/remove/upgrade shield
- Magic                         // Add/remove/upgrade magic
- Quiver                        // Add/remove/upgrade quiver
- Bomb Bag                      // Add/remove/upgrade bomb bag
- Power Bracelets               // Add/remove power bracelets from inventory
- Pirate's Charm                // Add/remove pirate's charm from inventory
- Hero's Charm                  // Add/remove hero's charm from inventory
- Wind's Requiem                // Add/remove wind's requiem from songs list
- Ballad of Gales               // Add/remove ballad of gales from songs list
- Command Melody                // Add/remove command melody from songs list
- Earth God's Lyric             // Add/remove earth god's lyric from songs list
- Wind God's Aria               // Add/remove wind god's aria from songs list
- Song of Passing               // Add/remove song of passing from songs list
- Din's Pearl                   // Add/remove din's pearl from inventory
- Farore's Pearl                // Add/remove farore's pearl from inventory
- Nayru's Pearl                 // Add/remove nayru's pearl from inventory
- Triforce Piece 1              // Add/remove triforce piece 1 from inventory
- Triforce Piece 2              // Add/remove triforce piece 2 from inventory
- Triforce Piece 3              // Add/remove triforce piece 3 from inventory
- Triforce Piece 4              // Add/remove triforce piece 4 from inventory
- Triforce Piece 5              // Add/remove triforce piece 5 from inventory
- Triforce Piece 6              // Add/remove triforce piece 6 from inventory
- Triforce Piece 7              // Add/remove triforce piece 7 from inventory
- Triforce Piece 8              // Add/remove triforce piece 8 from inventory

memory menu:
- memory editor menu            // View/edit memory
- watches menu                  // Manage memory watches

*practice menu:

*scene menu:

settings menu:
- cursor color                  // Change cursor color
- font                          // Change font
- drop shadows                  // Add shadows to all font characters
- save card                     // Save settings to memory card
- load card                     // Load settings from memory card
- delete card                   // Delete settings on memory card

tools menu:
- link debug info               // Display position and angle data for Link
- teleport                      // R+D-pad up to save position. R+D-pad down to load
- area reload                   // Reload the current room by pressing L + R + A + Start
- map select                    // Load Map Select by holding D-pad down + Y + Z
- zombie hover info             // Display A and B button presses per second
- input viewer                  // Show current inputs
```

\* - feature not implemented yet

### Planned Features

```
- spoils menu
- delivery bag menu
- built-in practice saves for all major speedrun categories
- more flags in the flags menu
- modifiable wallet capacity
- full health cheat
```

## Building

See [BUILDING.md](./BUILDING.md) to learn how to create local builds.

## Acknowledgements
Credits to everyone involved in the making of tww-gz, this includes PK_Slam, CGF95, Glubbers_, and TakaRikka.

Taka deserves a special congratulations for the work done, providing us with the entire framework ported over from [Twilight Princess' Practice Rom](https://tpgz.io). Without Taka's help, this project would likely have never gotten off the ground.

And special thanks to TrogWW, for the work he's done previously on earlier renditions of the practice rom, and for all the work he's done for the Wind Waker community.

Thank you to the teams behind the Romhack Compiler and DevKitPro, without them this would not be nearly as readily possible as it is.

Thank you to the TPGZ dev team, who's work we were graciously allowed to use for the base of our own practice rom.

And finally, thank you to the Wind Waker community being so awesome.
