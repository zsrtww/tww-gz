A lot of this is just taken from https://github.com/LagoLunatic/WW-Hacking-Docs/blob/ce486623c919634980921fe26cc597dcde357c76/RAM%20Map.txt for having a local reference. Ty Lago/Crain for the hard work.

Link X-pos: 803D78FC
Link Y-pos: 803D7900
Link Z-pos: 803D7904
Link Facing Angle: 803EA3D2
Link's pointer: 803AD860
Link Speed: P->803AD860
Link Animation Frame Cycle: P->803AD860
Acceleration: P->803AD860

Held item pointer? (has a question mark by it in DME lol): 804C4CB4

Link health: 803B810B

Current stage: 803BD23C
Room: 803B583B
Spawn: 803B9245


Arrow count: 803B8171

803C4C44-803C4C58 - Inventory. (dSv_player_item_c)
  Controls which items are in which slots on the inventory screen. Each slot is one byte.
  If the byte is FF it means no item is in the slot.
  Otherwise the byte is the item ID of the item in that slot.
  The order of slots is from left to right, then top to bottom.
Each inventory slot:
803C4C44,1 - Telescope (20)
803C4C45,1 - Sail (78)
803C4C46,1 - Wind Waker (22)
803C4C47,1 - Grappling Hook (25)
803C4C48,1 - Spoils Bag (24)
803C4C49,1 - Boomerang (2D)
803C4C4A,1 - Deku Leaf (34)
803C4C4B,1 - Tingle Tuner (21)
803C4C4C,1 - Picto Box (23, 26)
803C4C4D,1 - Iron Boots (29)
803C4C4E,1 - Magic Armor (2A)
803C4C4F,1 - Bait Bag (2C)
803C4C50,1 - Bow (27, 35, 36)
803C4C51,1 - Bombs (31)
803C4C52,1 - Bottle 1
803C4C53,1 - Bottle 2
803C4C54,1 - Bottle 3
803C4C55,1 - Bottle 4
  Bottle item IDs:
    50 - Empty Bottle
    51 - Red Potion
    52 - Green Potion
    53 - Blue Potion
    54 - Elixir Soup (1/2)
    55 - Elixir Soup
    56 - Bottled Water
    57 - Fairy in Bottle
    58 - Forest Firefly
    59 - Forest Water
803C4C56,1 - Delivery Bag (30)
803C4C57,1 - Hookshot (2F)
803C4C58,1 - Skull Hammer (33)

803C4C59-803C4C6D - List of bitfields of which items you own.
803C4C59,1 - Bitfield of whether you own the telescope + what bottle contents you have ever owned at an point.
  0 - Telescope
  1 - Unused bottle contents item 4F
  2 - Empty Bottle
  3 - Red Potion
  4 - Green Potion
  5 - Blue Potion
  6 - Elixir Soup (1/2)
  7 - Elixir Soup
803C4C5A,1 - Bitfield of whether you own the sail + what bottle contents you have ever owned at an point.
  0 - Boat's Sail
  1 - Bottled Water
  2 - Fairy in Bottle
  3 - Forest Firefly
  4 - Forest Water
  5 - Unused bottle contents item 5A
  6 - Unused bottle contents item 5B
  7 - Unused bottle contents item 5C
803C4C5B,1 - Bitfield of whether you own the wind waker + what bottle contents you have ever owned at an point.
  0 - Wind Waker
  1 - Unused bottle contents item 5D
  2 - Unused bottle contents item 5E
  3 - Unused bottle contents item 5F
  4 - Unused bottle contents item 60
  5 - 
  6 - 
  7 - 
803C4C5C,1 - Bitfield of whether you own the grappling hook.
  0 - Grappling Hook
803C4C5D,1 - Bitfield of whether you own the spoils bag.
  0 - Spoils Bag
803C4C5E,1 - Bitfield of whether you own the boomerang.
  0 - Boomerang
803C4C5F,1 - Bitfield of whether you own the deku leaf.
  0 - Deku Leaf
803C4C60,1 - Bitfield of whether you own the tingle tuner.
  0 - Tingle Tuner
803C4C61,1 - Bitfield of what picto boxes you own.
  0 - Picto Box
  1 - Deluxe Picto Box
803C4C62,1 - Bitfield of whether you own the iron boots.
  0 - Iron Boots
803C4C63,1 - Bitfield of whether you own magic armor.
  0 - Magic Armor
803C4C64,1 - Bitfield of whether you own the bait bag.
  0 - Bait Bag
803C4C65,1 - Bitfield of which types of arrows you own.
  0 - Regular arrows (Hero's Bow)
  1 - Fire and Ice Arrows
  2 - Light Arrow
803C4C66,1 - Bitfield of whether you own bombs.
  0 - Bombs
803C4C67,1 - ?
803C4C68,1 - ?
803C4C69,1 - ?
803C4C6A,1 - ?
803C4C6B,1 - Bitfield of whether you own the delivery bag.
  0 - Delivery Bag
803C4C6C,1 - Bitfield of whether you own the hookshot.
  0 - Hookshot
803C4C6D,1 - Bitfield of whether you own the skull hammer.
  0 - Skull Hammer

803C4C70,1 - ?
803C4C71,1 - Number of arrows you have.
803C4C72,1 - Number of bombs you have.
803C4C76,1 - ?
803C4C77,1 - Maximum number of arrows you can carry.
803C4C78,1 - Maximum number of bombs you can carry.

803C4C70,1 - ?
803C4C71,1 - Number of arrows you have.
803C4C72,1 - Number of bombs you have.
803C4C76,1 - ?
803C4C77,1 - Maximum number of arrows you can carry.
803C4C78,1 - Maximum number of bombs you can carry.

803C4DB4,4 - Player's partner's X pos.
803C4DB8,4 - Player's partner's Y pos.
803C4DBC,4 - Player's partner's Z pos.
803C4DC0,2 - Player's partner's rotation.
803C4DC2,1 - Player's partner's room number.
803C4DC3,1 - Player's partner's ID number.
  this is argument r4 to set__19dSv_player_priest_cFUcR4cXyzsSc
  1 - Makar
  2 - Medli
  3 - Servant of the Tower
  (There may be more IDs for different Servants of the Tower?)

Rel pointer: 803398DC
Rel ID (pointer data): 803398D8
Rel ID: 80372820
803B9218 - List of which files (maybe Rels specifically?) are currently loaded.
  Entry length 4. 0x1F6 entries in total.
  The index in this list is the actor ID.
  Each entry is a pointer to something? (e.g. 80ad4e30) Or 0 if it's invalid?

8035F9B8-8035F9F7 - List of Ballad of Gales warp destinations.
  Entry length 7. There are 9 entries in total.
  00,1: X pos of the sector on the sea chart (-3 to 3).
  01,1: Y pos of the sector on the sea chart (-3 to 3).
  02,1: Warp index of this warp.
  03,1: Warp index of the warp to the left of this one.
  04,1: Warp index of the warp to the right of this one.
  05,1: Warp index of the warp above this one.
  06,1: Warp index of the warp below this one.
  
8038DDAC,4 - Bitfield of damage types the player's sword should do? maybe?
80371DD4,4 - Bitfield of damage types for...? skull hammer maybe?

8039B5F4 - List of Wind Waker songs.
  7 bytes long.
  00,1: Number of notes in the song. (3, 4, or 6.)
  01,6: Array of song notes.
    0 - Center
    1 - Up
    2 - Right
    3 - Down
    4 - Left
    
803A4DF0 - Has info on the current controller input state. (g_mDoCPd_cpadInfo)
803A4DF0,4 - Control stick horizontal axis. Float from -1 to 1.
803A4DF4,4 - Control stick vertical axis. Float from -1 to 1.
803A4E00,4 - C-stick horizontal axis. Float from -1 to 1.
803A4E04,4 - C-stick vertical axis. Float from -1 to 1.
803A4E20,1 - Bitfield of whether certain buttons are currently being pressed down.
  01 - A button is down
  02 - L button is down
  04 - R button is down
  08 - Z button is down
  10 - D-pad up arrow button is down
  20 - D-pad down arrow button is down
  40 - D-pad right arrow button is down
  80 - D-pad left arrow button is down
803A4E21,1 - Bitfield of whether certain buttons are currently being pressed down.
  01 - ??? button is down
  02 - ??? button is down
  04 - ??? button is down
  08 - ??? button is down
  10 - Start button is down
  20 - Y button is down
  40 - X button is down
  80 - B button is down
803A4E22,1 - Bitfield of whether certain buttons were just pressed this frame.
  01 - A button was just pressed this frame
  02 - L button was just pressed this frame
  04 - R button was just pressed this frame
  08 - Z button was just pressed this frame
  10 - D-pad up arrow button was just pressed this frame
  20 - D-pad down arrow button was just pressed this frame
  40 - D-pad right arrow button was just pressed this frame
  80 - D-pad left arrow button was just pressed this frame
803A4E23,1 - Bitfield of whether certain buttons were just pressed this frame.
  01 - ??? button was just pressed this frame
  02 - ??? button was just pressed this frame
  04 - ??? button was just pressed this frame
  08 - ??? button was just pressed this frame
  10 - Start button was just pressed this frame
  20 - Y button was just pressed this frame
  40 - X button was just pressed this frame
  80 - B button was just pressed this frame
  
  803ED818,2 - Bitfield of currently pressed buttons. (For Pad.c)
803ED848,4 - Bitfield of currently pressed buttons. (For JUTGamePad.cpp)
  00000001 - D-pad left
  00000002 - D-pad right
  00000004 - D-pad down
  00000008 - D-pad up
  00000010 - Z
  00000020 - R
  00000040 - L
  00000100 - A
  00000200 - B
  00000400 - X
  00000800 - Y
  00001000 - Start
803ED84C,4 - Bitfield of buttons pressed this frame. (For JUTGamePad.cpp)
803F0F30,4 - Bitfield of currently pressed buttons. (For SIBios.c)
  
 803C4C08-803C4C1F - Current player status.
803C4C08,2 - Max HP (in quarters of hearts, counting heart pieces).
803C4C0A,2 - Current HP (in quarters of hearts).
803C4C0C,2 - Current num rupees.
803C4C11,1 - Index of the inventory slot corresponding to the item equipped on the X button, or FF for none.
803C4C12,1 - Index of the inventory slot corresponding to the item equipped on the Y button, or FF for none.
803C4C13,1 - Index of the inventory slot corresponding to the item equipped on the Z button, or FF for none.
  These determine what items on the inventory screen are highlighted in yellow.
  0x00-0x14 are normal items (index in list 803C4C44).
  0x18-0x1F are spoils (index in list 803C4C7E).
  0x24-0x2B are bait (index in list 803C4C86).
  0x30-0x37 are delivery bag items (index in list 803C4C8E).
803C4C16,1 - Currently equipped sword ID.
  38 - Hero's Sword
  39 - Master Sword (Powerless)
  3A - Master Sword (Half Power)
  3E - Master Sword (Full Power)
803C4C17,1 - Currently equipped shield ID.
  3B - Hero's Shield
  3C - Mirror Shield
803C4C18,1 - Current Power Bracelets ID. Should be 28 to own them.
803C4C1A,1 - Current wallet.
  0 - 200 Rupee Wallet
  1 - 1000 Rupee Wallet
  2 - 5000 Rupee Wallet
803C4C1B,1 - Max magic meter/MP.
803C4C1C,1 - Current magic meter/MP.

803C4C2C,4 - Current time in the day. (Float.)
  Ranges from 0.0 to 360.0.

803C4C38,8 - Stage name of the player's "return place" (where you will be placed when you reload your save).
  The 8th byte must be 00.
803C4C40,1 - Room number of the player's "return place" (where you will be placed when you reload your save).
803C4C41,1 - Spawn ID of the player's "return place" (where you will be placed when you reload your save).

803C4F88-803C4FAB - Stage ID 0 stage info (Sea)
803C4FAC-803C4FCF - Stage ID 1 stage info (Sea Alt)
803C4FD0-803C4FF3 - Stage ID 2 stage info (Forsaken Fortress)
803C4FF4-803C5017 - Stage ID 3 stage info (Dragon Roost Cavern)
803C5018-803C503B - Stage ID 4 stage info (Forbidden Woods)
803C503C-803C505F - Stage ID 5 stage info (Tower of the Gods)
803C5060-803C5083 - Stage ID 6 stage info (Earth Temple)
803C5084-803C50A7 - Stage ID 7 stage info (Wind Temple)
803C50A8-803C50CB - Stage ID 8 stage info (Ganon's Tower)
803C50CC-803C50EF - Stage ID 9 stage info (Hyrule)
803C50F0-803C5113 - Stage ID A stage info (Ship Interiors)
803C5114-803C5137 - Stage ID B stage info (Houses & Misc Places)
803C5138-803C515B - Stage ID C stage info (Cave Interiors)
803C515C-803C517F - Stage ID D stage info (More Cave Interiors & Ship Interiors)
803C5180-803C51A3 - Stage ID E stage info (This stage info's mem bit switches are used to keep track of Blue ChuChus being dead.)
803C51A4-803C51C7 - Stage ID F stage info (Test Maps)

  20,01: Number of small keys you currently have for this dungeon stage. (!! THIS dungeon stage !!)
  21,01: Bitfield of dungeon-specific flags for this dungeon stage.
    0 - Got dungeon map.
    1 - Got compass.
    2 - Got big key.
    3 - Boss is dead.
    4 - Heart container is taken.
    5 - Watched boss intro.
    
803C53A0,01 - Number of small keys you currently have in the current dungeon. (!! CURRENT dungeon !!)
803C53A1,01 - Bitfield of dungeon-specific flags for the current dungeon.
  0 - Got dungeon map.
  1 - Got compass.
  2 - Got big key.
  3 - Boss is dead.
  4 - Heart container is taken.
  5 - Watched boss intro.

803CA764,4 - Number of quarter hearts to add to the player's HP this frame.
  This is a float.
  Can be negative to damage the player.
803CA768,4 - Number of rupees to add to the player's wallet this frame.
  This is an int.
  Can be negative to take rupees away.
  
803E545A,2 - Wind angle. Every 0x4000 is equivalent to 90 degrees. Angle 0x0000 points straight east.
  Can just store to this to update wind direction on the fly.

803F6268,4 - Boomerang trail color. (RGBA)
803F62AC,4 - Normal sword slash trail color. (RGBA)
803F62B0,4 - Elixir soup sword slash trail color. (RGBA)
803F62B4,4 - Parrying sword slash trail color. (RGBA)
