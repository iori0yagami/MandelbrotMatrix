/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sabadri <sabadri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 14:57:31 by sabadri           #+#    #+#             */
/*   Updated: 2024/12/20 15:16:07 by sabadri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libc.h>
#include <mlx.h>
#include "fractol.h"

void my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
    char    *dst;

    dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
    *(unsigned int*)dst = color;
}
void generate_mandelbrot(t_data *data)
{
    int x, y;
    double real, imag;
    double real_temp;
    int max_iter = 100;
    double zoom = 0.5;
    double move_x = -0.3;
    double move_y = 0.3;
    int color;
    int i;
    for (y = 0; y < HEIGHT; y++)
    {
        for (x = 0; x < WIDTH; x++)
        {
            real = (x - (double)WIDTH / 2) / (0.5 * zoom * (double)WIDTH) + move_x;
            imag = (y - (double)HEIGHT / 2) / (0.5 * zoom * (double)HEIGHT) + move_y;

            int iteration = 0;
            double r = 0.0, i = 0.0;

            while (r * r + i * i <= 4.0 && iteration < max_iter)
            {
                double temp = r * r - i * i + real;
                i = 2 * r * i + imag;
                r = temp;
                iteration++;
            }
            if (iteration == max_iter)
                color = 0x00FFFFFF; 
            else 
                color = (iteration * 0xFF030507);
            my_mlx_pixel_put(data, x, y, color);
        }
    }
}

int main(int ac, char **av)
{
    void *mlx;
    void *mlx_win;
    t_data fractol;

    if (ac == 2 && !strncmp(av[1], "Mandelbrot", 10))
    {
        mlx = mlx_init();
        if (!mlx)
        {
            ft_error("MLX initialization failed");
            return (1);
        }

        mlx_win = mlx_new_window(mlx, WIDTH, HEIGHT, "Mandelbrot");

        fractol.img = mlx_new_image(mlx, WIDTH, HEIGHT);
        fractol.addr = mlx_get_data_addr(fractol.img, &fractol.bits_per_pixel, &fractol.line_length, &fractol.endian);

        generate_mandelbrot(&fractol);

        mlx_put_image_to_window(mlx, mlx_win, fractol.img, 0, 0);
        mlx_loop(mlx);
    }
    else
    {
        ft_error();
        return (1);
    }

    return (0);
}




