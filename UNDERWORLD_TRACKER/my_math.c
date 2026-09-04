#include "my_math.h"

bool CheckCollisionPointRec(Vector2D point, Rectangle rec)
{
    if ((point.x >= rec.x) && (point.x <= rec.x + rec.width) && (point.y >= rec.y) && point.y <= (rec.y + rec.length))
    return true;

    return false;
}

float Lerp (float start, float end, float t)
{
    return start + (end - start) * t;
}