# A skybox image merging utility

For help

```
boxey -h
```

## Examples

### blender created skybox
The blender template creates 6 images named 0001 through 0006

See the examples starter.blend for example camera positions.

```
boxey -t 0 -d ./examples/better/ -o ./out/ex_b2.png
```

### Artemis 2.8 skybox
Artemis 2.8 expects files named skybox_LT, skybox_RT,  skybox_FR, skybox_BK, skybox_UP, skybox_DN 

```
boxey -t 1 -d ./examples/SB10/ -o ./out/ex_a.png
```


### Spacescape created skyboxes
Space scape create files named a save name ex. "skybox" skybox_left, skybox_right,  skybox_front, skybox_back, skybox_up, skybox_down

By default skybox is assume, but -f can override that

```
boxey -t 2 -d ./examples/spacescape/ -f box -o ./out/ex_a.png
```
