/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vsync.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: het-taja <het-taja@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:00:51 by het-taja          #+#    #+#             */
/*   Updated: 2024/09/04 18:00:58 by het-taja         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <time.h>

void limit_frame_rate(int target_fps)
{
    static struct timespec last_frame_time;
    struct timespec current_time;
    long sleep_time;
    int nano_seconds_per_frame = 1000000000 / target_fps;

    clock_gettime(CLOCK_MONOTONIC, &current_time);

    // Calculate the elapsed time since the last frame
    long elapsed_time = (current_time.tv_sec - last_frame_time.tv_sec) * 1000000000L
                        + (current_time.tv_nsec - last_frame_time.tv_nsec);

    // Calculate how much time to sleep until the next frame
    sleep_time = nano_seconds_per_frame - elapsed_time;

    // If we need to sleep, do it
    if (sleep_time > 0)
    {
        struct timespec sleep_duration;
        sleep_duration.tv_sec = sleep_time / 1000000000;
        sleep_duration.tv_nsec = sleep_time % 1000000000;
        nanosleep(&sleep_duration, NULL);
    }

    // Update the last frame time
    clock_gettime(CLOCK_MONOTONIC, &last_frame_time);
}