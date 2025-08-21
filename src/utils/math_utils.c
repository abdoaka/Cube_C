#include "../../includes/cub3rd.h"
#include <stdint.h>

uint32_t convert_rgb_to_rgba(int rgb_color)
{
    int r = (rgb_color >> 16) & 0xFF;
    int g = (rgb_color >> 8) & 0xFF;
    int b = rgb_color & 0xFF;
    
    // Try RGBA format first:
    return (r << 24) | (g << 16) | (b << 8) | 0xFF;  // RGBA
    
    // If colors look wrong, try this instead:
    // return (b << 24) | (g << 16) | (r << 8) | 0xFF;  // BGRA
}