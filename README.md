First draft on open project thoughts and timeline

Our goal is to create a video game based on the quite popular genre hybrid Rogue-Like. It is a very broad type of game, but the main idea behind it is always the same. A playthrough that isn’t too long (can be finished in an hour or so) but a huge replayability. Each time you run through the game, you’ll encounter different enemies, bosses, objects, map layout, and finishing a playthrough is rewarding in itself for the player as it unlocks new objects/enemies/levels in order to alter the gameplay for the next run. The death is permanent, and once your character dies, you have to restart from the beginning.

There are quite a few games available that use this concept. Overall, Rogue Legacy, Binding of Isaac, Faster Than Light depict it very well as they all offer this kind of gameplay. However, not a game is similar to the other. For example, Rogue Legacy is a 2D scrolling game with plateformer elements. Isaac is a 2D game where the gameplay is more inspired by “shoot them up” kind of games, and the view is overworld. Faster Than Light is an overworld game aswell, but the gameplay revolves more around unit-management.

On the topic of our game, we are looking to create a 2D scrolling game with procedural-based map construction, using already existing tools such as a C++ open-sourced graphic and physics engine, in order to focus more heavily on the game itself. 

Basic ideas we are looking to implement for our game:

2D scrolling game with different levels that grant rewards when you complete them, with a final boss at the end of the game.
* Action and skill based game, real-time movement and fights. 
* Enemies that you have to fight in order to gain rewards but that deal damage to you.
* Plateformer elements, such as hard to reach chests or rooms.
* Different starting characters, depicting the classic different starting classes in most Fantasy games : warrior, mage, thief, ranger, and a “hard mode” kind of class (beggar)
* A leveling feature, making your character more resilient and stronger the more you play it.
* Skilltree to level and unlock new skills for each class.
* Items that modify the gameplay.
* Inventory, in order to manage items you get every playthrough
* Single money that will be used to unlock skills, level up your character and buy items.

I - Level-based game design
	Each playthrough, you’ll have to go through 10 different maps each linked by an entrance room and an exit room guarded by a boss. It is not possible to go back to a previous level after starting the next one. Each level will offer different environment and enemies. The map will be loaded procedurally, by linking a certain number of rooms (the higher the level, the more rooms there will be). Rooms (or tiles) will be pre-determined in order to avoid impossible-to-cross kind of rooms. Each level will also have secrets rooms, bringing different advantages, such as the possibility to save or retrieve an already saved item, buy items for the current run, or cash in your current money in order to use it to unlock new abilities for one of the characters.

II - A real time game
	The game will offer real-time based gameplay, contrary to turn-based gameplay. Core of it will be ability to move left and right, jump, and attack.

III - Character
	Each character will be different in its starting gameplay. The warrior is a resilient character that dishes out damage to enemies close to him, and has a strong armor. The ranger uses bow or crossbow, allowing him to damage enemies from a distance, and has a medium armor. Mages will carry robes, so very low armor, but incredibly powerful spells to get rid of enemies. The beggar will carry no armor, maybe a weapon, and relies heavily on player skill to finish the first levels before getting his own gear for the run.

IV - Enemies
Enemies will spawn in each room of a level until they are killed. Once a room is cleaned, coming back into it will not create new enemies. Each kind of enemy will be different, either ranged or melee, with varying HP, damage, movespeed, and special abilities. They will move by themselves according to their AI and attack the character “on sight” with projectiles, ranged attack or melee weapons. Dodging their attacks and killing them will grant money to the player. Upon a certain number of blows, the character dies and lose all its current items and accumulated experience.

V - Boss
	Boss will be special enemies with a special moveset that will require the player to place himself correctly in order not to get hit by anything. Damage will be high, HP will be high, but the reward is high aswell. Plus, it’s a must-kill enemy if you want to advance in the game.

VI - Leveling 
	At the end of each run, you can permanently invest the money you saved from your previous runs in order to improve one of the character (besides the beggar). Each level will grant bonus armor, damage, HP. Some levels will also grant access to a new rank of skills (1 - 5 - 10 - 20)

VII - Skillset
	At the beginning of each run, you can choose which skills to equip your character. Each class will have different skillset that require to be unlocked with money. There are 3 levels for each skills.	(WIP)



VIII - Items
	Items will be core within the gameplay. They will require a class and a level to be carried. The character can equip a number of items. head armor, chest armor, weapon, ring. These items can bring simply better stats, or can completely change gameplay. For example, equipping a new weapon can change the moveset of the character, or give him bonus skills.  Some items will also allow to bend the games rules.
Items are uniques and usable only during the current run. They are lost upon death or when the run ends.

IX - Inventory
	The inventory will be accessible via the menu during a run. It will contain all the equipment the player found during the playthrough. Part of it can be equipped, the remainder will be kept in the inventory and it won’t affect the gameplay. If the inventory is full, the player has to drop an item on the ground before taking another one. Items on the ground can be looted again.

X - Money
	Money (or experience) will be the only currency in the game. It will be looted from regular monsters, and in bigger quantity from secret rooms or bosses. It can be used 3 different ways.
Shop : During the run, the player might encounter a secret room which contains a vendor selling items. The player can use the currency he found during the current run to buy.
Leveling : All the money the player will have saved during a run can be stocked and used in order to level the different characters.
Skillset : In the same way the money is used for leveling, the player can buy or upgrade the skills available for each character.
All money not saved is lost upon death of the character during a run. If the run is complete, all the money is saved.

XI - Chest
	The chest will be in a special room, hidden from plain sight. But some clues might help the player finding it.
Once the player reaches the chest, he can store an item in it. The item will be retrievable for next runs, until it is picked up again. The chest can only contain one slot, so the player will have to chose which item he wants to save. The chest will also allow the player to save its current money, in order to use it in next runs. In the later levels, an optional boss will have to be beaten in order to access the chest.
