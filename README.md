# I. GB_UE_UI
 Learning how to create, display, and remove UI elements from the screen during gameplay.
 
 
I used the UE-Only Content (UE-Only Content - Licensed for use only with and under the same terms as the Unreal Engine.) 
for educational purposes such as :

[Paragon: Terra](https://www.unrealengine.com/marketplace/en-US/product/paragon-terra?sessionInvalidated=true)

![Alt-текст](https://cdn1.epicgames.com/ue/product/Screenshot/TerraScreenshot3-1920x1080-8d471a8dd9d9c47f1c895ec87969ba3c.png?resize=1&w=1920 "Paragon: Terra")

[Infinity Blade: Ice Lands](https://www.unrealengine.com/marketplace/en-US/product/infinity-blade-ice-lands)

![Alt-текст](https://cdn1.epicgames.com/ue/product/Screenshot/IBIceLandsScreenshot02-1920x1080-70b0965fef3dd34e9554d94b07cd0748-1920x1080-c3ce4b241da459f4d0d01c800e83d8dc.png?resize=1&w=1920 "Infinity Blade: Ice Lands")

## Lesson 1. UMG: Introduction

- [X] 1. Collect the widget with a centered inscription "Game Over" on a red background.
- [X] 2. Display a widget on the screen when the player dies (or another game event occurs, NOT pressing the button).
- [X] 3. (**)Make the widget beautiful: replace the plain background with a picture, use a Rich Text Block instead of plain text.

[![Video HW1 part 1](https://img.youtube.com/vi/nYGZpavuhPo/0.jpg)](https://youtu.be/nYGZpavuhPo)
[![Video HW1 part 2](https://img.youtube.com/vi/GuoBnh1abMk/0.jpg)](https://youtu.be/GuoBnh1abMk)

## Lesson 2. UMG basic widgets and their features

- [X] 1. Collect the widget for the main menu
- [X] 2. Collect tank and enemy status widgets, widget to display health over the tank
- [X] 3. (**)add animations to widgets
- [X] 4. (**)look at various UI examples in the library and repeat the ones you like: https://www.gameuidatabase.com/index.php

[![Video HW2 part 1](https://img.youtube.com/vi/MycVuXNiSYI/0.jpg)](https://youtu.be/MycVuXNiSYI)
[![Video HW2 part 2](https://img.youtube.com/vi/geYGP1RkwXU/0.jpg)](https://youtu.be/geYGP1RkwXU)

## Lesson 3. UMG. Binding Widgets in C++ and Creating a Widget Manager

- [X] 1. Write in C++ logic for widgets created after the previous lesson: main menu, tank and enemy statuses.
- [X] 2. Display HP bars above the tank and enemies, showing the current level of health.
- [X] 3. (**)create a HUD manager that controls the display of the main menu, “Game Over” widget, the status of your tank.

[![Video HW3 part](https://img.youtube.com/vi/UyD73WaXxMI/0.jpg)](https://youtu.be/UyD73WaXxMI)

## Lesson 4. Slate: Basic class initialization and argument passing

- [ ] 1. Create a widget for the minimap, in which to override the OnPaint method and use MakeLines and MakeBox to draw a schematic map of the level.
*(MakeLines not used)
- [X] 2. Add an image of the player's position to the mini-map.
- [X] 3. (**)make the map dynamic, updating as the player moves.
- [ ] 4. (**)look into the library again and implement any widget for which UMG was not enough: https://www.gameuidatabase.com/index.php

[![Video HW4 part 1](https://img.youtube.com/vi/rnWolczr-ow/0.jpg)](https://youtu.be/rnWolczr-ow)
[![Video HW4 part 2](https://img.youtube.com/vi/ogJ-yzVk_PA/0.jpg)](https://youtu.be/ogJ-yzVk_PA)

## Lesson 5. Slate: Styles

- [X] 1. Create styles for the widgets already in the umg project.
- [X] 2. Create multiple color themes and apply them.
- [ ] 3. (**) make and apply a style to the minimap.

[![Video HW5](https://img.youtube.com/vi/u7loNA-ccAg/0.jpg)](https://youtu.be/u7loNA-ccAg)

## Lesson 6. Slate and UMG: Drag&Drop

- [X] 1. Creation of several types of objects for DragDrop
- [X] 2. During the game, it is possible to call a list of available objects and DragDrop to drag into the world
- [X] 3. when you hover over an object in the list, a popup (widget) appears with information about it
- [X] 4. (**) modify DragDrop so that the dragged widget is inserted before the widget it is above, if the cursor is above the top half of the widget, and after - if above the bottom

[![Video HW6 part 1](https://img.youtube.com/vi/w_X9RQixANI/0.jpg)](https://youtu.be/w_X9RQixANI)
[![Video HW6 part 2](https://img.youtube.com/vi/KXSEFxBYaRc/0.jpg)](https://youtu.be/KXSEFxBYaRc)

## Lesson 7. Inventory: Basic System

- [X] 1. Create your own inventory prototype.
- [X] 2. Set default items in inventory via date table instead of manually adding components to inventory. Create several different initial sets depending on the class chosen by the RPG player or any other parameter.
- [X] 3. (**)initialize a date table with a list of all items from the file.
- [X] 4. (**) split items into categories, each of which is displayed in a separate inventory tab, there is a tab with all items

[![Video HW7 part 1](https://img.youtube.com/vi/Ci1_UoE_fAI/0.jpg)](https://youtu.be/Ci1_UoE_fAI)
[![Video HW7 part 2](https://img.youtube.com/vi/gFu9d1ub3iI/0.jpg)](https://youtu.be/gFu9d1ub3iI)
[![Video HW7 part 3](https://img.youtube.com/vi/LaP8WKALCjc/0.jpg)](https://youtu.be/LaP8WKALCjc)

## Lesson 8. Inventory: Equipment

- [X] 1. Finish your own inventory prototype.
- [X] 2. Try on several items on the character at the same time, one from each category.
- [X] 3. (**) make chests with loot, the ability to take all items or part of them.
- [X] 4. (**)make consumable items that restore hp (once or over time) or give temporary buffs. RMB on an item in inventory - its use.

[![Video HW8 part 1](https://img.youtube.com/vi/4GoL7rfryl4/0.jpg)](https://youtu.be/4GoL7rfryl4)
[![Video HW8 part 2](https://img.youtube.com/vi/uyCvVTsoLHk/0.jpg)](https://youtu.be/uyCvVTsoLHk)
[![Video HW8 part 3](https://img.youtube.com/vi/V9F3Nv-nmtU/0.jpg)](https://youtu.be/V9F3Nv-nmtU)

# II. UE4 Plugins/Modules
 The prototype of the game created at the last course (UI) has been expanded, a quest system has been added, as well as saving and loading data. An add-on for the editor has been written, which will facilitate the work with the quest system.

## Lesson 1. What are plugins and modules

- [X] 1. Transfer part of the code responsible for the gameplay from your project to the plugin.
- [X] 2. Transfer some assets from your project to the plugin.
- [X] 3. (**)move inventory to the plugin.

## Lesson 2. Media Player

- [X] 1. Make a widget with the “Browse” button, when clicked, a file dialog opens with the ability to select an image or video.
- [X] 2. In the same widget, add an image that will display the selected content.
- [X] 3. (**)after downloading the content, resize the image to maintain the correct aspect ratio.

## Lesson 3. Quest System: Part 1
- [X] 1. Start your own quest system, make it a separate plugin.
- [X] 2. Add new interactive items.
- [X] 3. (**) Make goals of a different type: collecting items, killing enemies, etc.

## Lesson 4. Quest System: Part 2
- [X] 1. Finish your quest system.
- [X] 2. Add several quests with different types of goals and the order of their completion, test the quest system.
- [X] 3. (**) make a hint that the NPC has a quest for the player: a jumping exclamation mark above his head or any other.

## Lesson 5. Simple Editor Tool: Part 1
- [X] 1. Create plugin with Editor Standalone Window template.
- [X] 2. In the created tab, make a button, when clicked, quests are selected among the selected actors, and in the tab itself, information about these quests is displayed in an easy-to-read format.
- [X] 3. Transfer all functionality from the new plugin to the plugin with the quest system.
- [X] 4. (**)information about quests can not only be viewed, but also changed in the tab.

## Lesson 6. Simple Editor Tool: Part 2
- [X] 1. Write a tool that highlights all NPCs with quests if there are no NPCs among the selected actors.
- [X] 2. If there are NPCs among the selected actors, then instead highlight the areas and objects associated with the quests of these NPCs.
- [X] 3. Transfer all functionality from the new plugin to the plugin with the quest system.
- [X] 4. (**) in the toolkit you can change the highlight color.

## Lesson 7. Data saving: unreal system
- [X] 1. Save the state of your player (health level, number of rounds).
- [X] 2. Save the state of other objects on the map.
- [X] 3. (**) save inventory.

## Lesson 8. Saving data: working with files
- [X] 1. Extend the save manager as described in the case study.
- [X] 2. Save the progress of the quest system.
- [X] 3. (**) Save everything via FMemoryWriter/FMemoryReader and Serialize function
