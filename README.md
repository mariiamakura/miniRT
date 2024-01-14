# miniRT
A simple RayTracing application in collaboration with [Luiz](https://github.com/lbaron42)

![scrinshoot](example.gif)

## how to install and compile

```
git clone <repository SSH/URL>
cd <repository>
make
```
## execution
Valid tests can be found in /scenes folder. Example:

```
./miniRT scenes/majorTest.rt
```

## camera movement
Camera movement and rotation can be done by using those keys:
| Key | Movement | Rotation |
|----------|----------|----------|
| MLX_KEY_W | z | |
| MLX_KEY_S | -z | |
| MLX_KEY_D | x | |
| MLX_KEY_A | -x | |
| MLX_KEY_SPACE | y | |
| MLX_KEY_LEFT_SHIFT | -y | |
| MLX_KEY_KP_4 | | z |
| MLX_KEY_KP_6 | | -z |
| MLX_KEY_KP_8 | | -y |
| MLX_KEY_KP_2 | | y |
| MLX_KEY_KP_7 | | x |
| MLX_KEY_KP_9 | | -x |

Perfomance of the application can be impoved by increasing number of threads in include/miniRT.h file:

```
# define NUM_THREADS 100
```

