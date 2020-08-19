# Zombie Game (Title Pending)

Just a simple little zombie game I'm making for fun using SFML, and making my own assets

## Support
If anything goes wrong, please send an email to cpzombiedev@gmail.com with a detailed description of your problem. Please be sure to attach the log file.

## Map Creation
If you want to make your own map, you can! Just make a text file with your desired options, and save it with a .map extension in the maps folder. Any options not specified will be default. List of currently supported options, and their formats (type them as shown, "option: parameters"):
```
dimensions: width(int) height(int)
background_texture: path_to_background_texture(string)
spawn_location: spawn.left(int) spawn.top(int) spawn.width(int) spawn.height(int)
bullet_textures: path_to_bullet_texture1(string) path_to_bullet_texture2(string) ...
zombie_count: num(int)
zombie_textures: path_to_zombie_texture1(string) path_to_zombie_texture2(string) ...

```
Note: entities only need one texture, but can include more for some animation  
Note2: location and dimension integers are in pixels  
Note3: spawn_location can be repeated as many times as desired to create more possible spawning locations. 