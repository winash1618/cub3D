# cub3D
This project is inspired by the world-famous Wolfenstein 3D game, which was the first FPS ever. It will enable you to explore ray-casting. Your goal will be to make a dynamic view inside a maze, in which you’ll have to find your way.


## Resources
- https://lodev.org/cgtutor/raycasting.html
- https://eastmanreference.com/complete-list-of-applescript-key-codes#:~:text=The%20enter%20key%20on%20most,accomplished%20by%20hitting%20fn%20%2B%20enter
- https://www.youtube.com/watch?v=NbSee-XM7WA

## gcc
- gcc -framework OpenGL -framework AppKit cub3d.c minilibx/libmlx.a && ./a.out


- gcc -framework OpenGL -framework AppKit parse.c minilibx/libmlx.a get_next_line/get_next_line.c get_next_line/get_next_line_utils.c -D BUFFER_SIZE=1 && ./a.out map.cub