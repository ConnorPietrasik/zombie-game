# Zombie Game (Title Pending) - WIP

Just a simple little zombie game I'm making for fun using SFML, and making my own assets.

## Map Format
To create a map just make a text file with your desired options and save it with a .map extension in the maps folder. Any options not specified will be default. 
List of currently supported options, and their formats (type them as shown, "option: parameters"):
```
dimensions: width(int) height(int)
background_texture: path_to_background_texture(string)
spawn_location: spawn.left(int) spawn.top(int) spawn.width(int) spawn.height(int)
bullet_textures: path_to_bullet_textures_dir(string)
zombie_count: num(int)
zombie_textures: path_to_zombie_textures_dir(string)
```
<sub><sup>Note: entities only need one texture in the directory, but can include more for some animation  
Note2: location and dimension integers are in pixels  
Note3: spawn_location can be repeated as many times as desired to create more possible spawning locations.</sup></sub>  
