# A skybox image merging utility

This is a utility for merging 6 cube map images into a single image. It works for Artemis Cosmos skyboxes, but may work for other things.

For help

```
boxey -h
```

## Examples

### blender created skybox
The blender template creates 6 images named 0001 through 0006

- 0001 = left
- 0002 = up
- 0003 = right
- 0004 = down
- 0005 = front
- 0006 = back

See the examples starter.blend for example camera positions.
The camera rig is created to avoid needing to rotate any of the images for this tool. For most optimal performance.

```
boxey -t 0 -d ./examples/better/ -o ./out/ex_b2.png
```

### Artemis 2.8 skybox
Artemis 2.8 expects files named skybox_LT, skybox_RT,  skybox_FR, skybox_BK, skybox_UP, skybox_DN 

```
boxey -t 1 -d ./examples/SB10/ -o ./out/ex_a.png
```


### Spacescape created skyboxes
Space scape is a utility for creating skyboxes 

[http://alexcpeterson.com/spacescape/](http://alexcpeterson.com/spacescape/)

Space scape create files named a save name ex. "skybox" skybox_left, skybox_right,  skybox_front, skybox_back, skybox_up, skybox_down

By default skybox is assume, but -f can override that

```
boxey -t 2 -d ./examples/spacescape/ -f box -o ./out/ex_s.png
```
