#include <sys/time.h>
#include "cub3d.h"
// Helper function to get the current time in milliseconds
long long current_time_in_millis()
{
    struct timeval time;
    gettimeofday(&time, NULL);
    return (time.tv_sec * 1000LL + time.tv_usec / 1000LL);
}

// FPS counting function
void count_fps(t_game *game)
{
    static long long last_time = 0;
    static int frame_count = 0;

    long long current_time = current_time_in_millis();
    
    // If one second has passed
    if (current_time - last_time >= 1000)
    {
        game->fps = frame_count; // Set FPS to the number of frames in the last second
        frame_count = 0; // Reset frame count
        last_time = current_time; // Reset time to now
    }

    frame_count++; // Count frames rendered
}