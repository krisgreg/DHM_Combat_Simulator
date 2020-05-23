# DHM_Combat_Simulator
A combat simulator for the browser based game DiamondHunt Mobile https://diamondhunt.app/

# Changelog
## Changelog 1.12
#### Bugfixes
* Core stats display for player and enemy are now not always 0 again, whoops.
## Changelog 1.11
#### Sim
* Sim is now properly multithreaded. Exact performance increase depends on your hardware, but personally I am experiencing a 6x-100x increase in speed. Where really short fights are way more optimized than before.

Long fight before/after optimizations
>[![Image from Gyazo](https://i.gyazo.com/922787e9d3549ea80db362117d996bd8.png)](https://gyazo.com/922787e9d3549ea80db362117d996bd8)
>[![Image from Gyazo](https://i.gyazo.com/7b09bc604d3f59fdbd2915a6a1e27bb2.png)](https://gyazo.com/7b09bc604d3f59fdbd2915a6a1e27bb2)

Short fight before/after optimizations
>[![Image from Gyazo](https://i.gyazo.com/881661f2bcea1c2fd82ce6a9bd4ae22b.png)](https://gyazo.com/881661f2bcea1c2fd82ce6a9bd4ae22b)
>[![Image from Gyazo](https://i.gyazo.com/84f2f95c10c607d480830151d0ddde43.png)](https://gyazo.com/84f2f95c10c607d480830151d0ddde43)
#### Enemies
* Added Blood jungle pack.
#### Gear
* Added Elephant Cloak.
* Added Silver Scimitar.
* Added Super Jungle Shield.
#### Bugfixes
* Fixed a bug causing damaged reflected from Robot Mages charge attack to be immuned by his magic shield.
* Fixed a bug allowing the player evade charge attacks with the invis effect.
## Changelog 1.10
#### Sim
* Fixed a bug causing ranged poison weapons to be treated as melee after being equipped.
## Changelog 1.9
#### Sim
* Added some new visuals to stats for tracking damage done.
[![Image from Gyazo](https://i.gyazo.com/a976a7c630b854cb1d7ec568422f46c9.png)](https://gyazo.com/a976a7c630b854cb1d7ec568422f46c9)
* Started tracking ice damage done.
* AI will no longer poison with weapons the enemy can retaliate against.
## Changelog 1.8
#### Sim
* Fixed a bug that could cause the AI to re-equip it's ranged weapon after switching to a melee poison weapon to lifesteal with it.
## Changelog 1.7
#### General
* Learned there are fewer p's in triple than two.
#### Spells
* Implemented upgraded version of Sandstorm.
#### Enemies
* Added Blood Ocean mobs.
* All bird pack attack speeds increased from 4->2.
#### Gear
* Added Shark Fin.
* Added Ocean Soldier Helmet+.
## Changelog 1.6
#### Spells
* Added Sandstorm spell (upgraded version not implemented yet)
#### Enemies
* Added Blood Desert mobs.
* Castle Mage stats fixed, it accidentaly had 900 defence instead of hp.
* Blood Skeleton Ghost was missing his dodge chance.
* Ocean and Deep Ocean mobs are now immune to fire damage.
#### Gear
* Added Lizard Cloak.
* Added Ancient Oxygen Tank.
## Changelog 1.5
#### Sim
* Fixed an issue causing the enchanted scythe to not ignore ghosts defence.
* Added custom behavior for Blood HM fight. (Save thunder if enemy HP is less than 150, use lifesteal when at 15 hp or less, poison blood reaper with acc pot and skeleton ghost without)
* Made AI stop unequipping gear if reflect was active, if the spell was also upgraded. Oops
#### Enemies
* Added Blood Haunted Mansion fight
#### Gear
* Added Reaper Robes
## Changelog 1.4
#### Sim
* Fixed an issue causing the player not to take damage from drowning.
* Added stat to track average number of arrows used per fight (requested by Kuddel).
#### Enemies
* Added Tripplet mobs of Chickens, Fire Hawks, Ice Hawks, and all their Blood versions
## Changelog 1.3
#### New Feature
* Custom Gear Presets
 - You can now save sets of gear to be easily loaded with a single click from the new dropdown menu in the Gear Selector window inbetween sessions.
 - You can also copy presets to clipboard and load presets from clipboard, allowing you to easily share a gear setup by sending a message.
#### Sim
* AI now uses lightbulb on ticks where it will not be attacked, and switches to defence items on ticks where it will (if both a defence item and the lighbulb is selected for the back slot).
* Magic immune shield now blocks reflect from being used, instead of just negating the damage.
* AI now swaps to bear fur armor on ticks where it will not be attacked, and switches to best available armor on ticks where it will (if the current enemy requires cold resistance).
#### Enemies
* Blood NF mobs added (unsure about the exact strength of ice hawk attacks, currently set to 30-80 damage).
* Skeleton Mage 3 HP nerf (400->350HP).
* Fire and Ice Hawk attack speed reduced to 4.
#### Gear
* Ice Gloves added (unsure about proc rate, currently set to 50%).
* Enchanted Superbow added.
* Lightbulb now correctly has 1 defence.
#### Custom Enemies
* Added custom mechanics: 
    - Multi-hit (Blood Golem)
## Changelog 1.2
#### Sim
* Fixed an issue where Drowning and Freezing damage would be applied as an attack with 0 accuray if you had protection from it. (Oxygen/cold resistance)
* AI for Robot Mage updated to save thunder/freeze for charge ability and chain stun, increasing the winrate against this mob.
* AI updated to try and avoid using weapon types that would result in getting hit by retaliation damage. 
#### Custom Enemies
* Updated Cold Resistance and Oxygen requirements to support custom amounts of damage when not protected against.
* Added custom mechanics: 
    - Infection (Zombie)
    - Wound (Poison Tribe)
    - Swarm Attack (Piranhas)
    - Auto Attack Charge (Dragon)
    - Evade (Lizard)
    - Damage Retaliation (Pufferfish)
#### System
* The program will now launch at slightly smaller than your screens resolution instead of a fixed resolution of 1920x1080, to avoid issues on screens with lower resolutions.
* The console window is now removed from the release version.
* Added a taskbar icon for the program.
## Changelog 1.1
* Height scaling issues fixed.
## Changelog 1.0
The initial release of the DHM combat sim!
* All gear and mobs released as of today (3rd of october) is implemented for the sim. (BM Fire Mage might have inaccurate stats)
* Custom mobs are fairly limited atm, most of the ground work for more custom mechanics are complete and a patch to access these will (hopefully) be realeased in the comming days.
