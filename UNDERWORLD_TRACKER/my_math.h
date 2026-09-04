#ifndef MY_MATH_H    
#define MY_MATH_H

#include <stdbool.h>
typedef struct
{
    float x;
    float y;
} Vector2D;

typedef struct
{
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} RGBA_Colour;

typedef struct
{
    float x;
    float y;
    float width;
    float length;
} Rectangle;

bool CheckCollisionPointRec(Vector2D point, Rectangle rec);
float Lerp (float start, float end, float t);

#endif