#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/fb.h>
#include <string.h>

int main(void)
{
    int fbfd = 0;
    struct fb_var_screeninfo vinfo;
    struct fb_fix_screeninfo finfo;
    uint32_t *fbp = 0; 

    fbfd = open("/dev/fb0", O_RDWR);
    if (fbfd == -1)
    {
        perror("Error: cannot open framebuffer device");
        return 1;
    }

    if (ioctl(fbfd, FBIOGET_FSCREENINFO, &finfo) == -1)
    {
        perror("Error reading fixed information");
        return 1;
    }

    if (ioctl(fbfd, FBIOGET_VSCREENINFO, &vinfo) == -1)
    {
        perror("Error reading variable information");
        return 1;
    }

    long screensize = vinfo.yres_virtual * finfo.line_length;

    fbp = (uint32_t *)mmap(0, screensize, PROT_READ | PROT_WRITE, MAP_SHARED, fbfd, 0);

    uint32_t *backup_buffer = malloc(screensize);

    if ((intptr_t)fbp == -1)
    {
        perror("Error: failed to map framebuffer device to memory");
        return 1;
    }

    printf("The screen is %dx%d, %d bits per pixel\n", vinfo.xres, vinfo.yres, vinfo.bits_per_pixel);

    uint32_t color = 0x00FF0000; 

    memcpy(backup_buffer, fbp, screensize);

    for (int y = 0; y < vinfo.yres; y++)
    {
        for (int x = 0; x < vinfo.xres; x++)
        {

            long location = (x + vinfo.xoffset) + (y + vinfo.yoffset) * vinfo.xres;

            fbp[location] = color;
        }
    }

    sleep(3);

    memcpy(fbp, backup_buffer, screensize);

    free(backup_buffer);

    munmap(fbp, screensize);
    close(fbfd);

    return 0;
}