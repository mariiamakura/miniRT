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



	else if (mlx_is_key_down((*rt)->window->mlx, MLX_KEY_W))
		m_dir.z = 1;
	else if (mlx_is_key_down((*rt)->window->mlx, MLX_KEY_S))
		m_dir.z = -1;
	else if (mlx_is_key_down((*rt)->window->mlx, MLX_KEY_D))
		m_dir.x = 1;
	else if (mlx_is_key_down((*rt)->window->mlx, MLX_KEY_A))
		m_dir.x = -1;
	else if (mlx_is_key_down((*rt)->window->mlx, MLX_KEY_SPACE))
		m_dir.y = 1;
	else if (mlx_is_key_down((*rt)->window->mlx, MLX_KEY_LEFT_SHIFT))
		m_dir.y = -1;


  	if (mlx_is_key_down((*rt)->window->mlx, MLX_KEY_KP_8))
		add_rot = ft_xy_rot_ox(cosf(rot_val), sinf(rot_val));
	else if (mlx_is_key_down((*rt)->window->mlx, MLX_KEY_KP_2))
		add_rot = ft_xy_rot_ox(cosf(-rot_val), sinf(-rot_val));
	else if (mlx_is_key_down((*rt)->window->mlx, MLX_KEY_KP_4))
		add_rot = ft_xy_rot_oy(cosf(-rot_val), sinf(-rot_val));
	else if (mlx_is_key_down((*rt)->window->mlx, MLX_KEY_KP_6))
		add_rot = ft_xy_rot_oy(cosf(rot_val), sinf(rot_val));
	else if (mlx_is_key_down((*rt)->window->mlx, MLX_KEY_KP_7))
		add_rot = ft_xy_rot_oz(cosf(rot_val), sinf(rot_val));
	else if (mlx_is_key_down((*rt)->window->mlx, MLX_KEY_KP_9))
		add_rot = ft_xy_rot_oz(cosf(-rot_val), sinf(-rot_val));
