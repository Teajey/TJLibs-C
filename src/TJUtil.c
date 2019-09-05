#include "../include/TJUtil.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

double constrain(double n, double low, double high)
{
    if (low > high)
    { //Swap values
        low = low + high;
        high = low - high;
        low = low - high;
    }
    return fmax(fmin(n, high), low);
}

uint32_t argbToHex(int a, int r, int g, int b)
{
    a = constrain(a, 0, 255);
    r = constrain(r, 0, 255);
    g = constrain(g, 0, 255);
    b = constrain(b, 0, 255);
    return (a << 24) | (r << 16) | (g << 8) | b;
}

void hexToARGB(uint32_t hex, uint8_t *a, uint8_t *r, uint8_t *g, uint8_t *b)
{
    if (a != NULL)
        *a = (hex & 0xFF000000) >> 24;
    *r = (hex & 0xFF0000) >> 16;
    *g = (hex & 0xFF00) >> 8;
    *b = hex & 0xFF;
}

uint32_t rgbToHex(int r, int g, int b)
{
    return argbToHex(255, r, g, b);
}

void hexToRGB(uint32_t hex, uint8_t *r, uint8_t *g, uint8_t *b)
{
    return hexToARGB(hex, NULL, r, g, b);
}

uint32_t mcToHex(int m)
{
    return rgbToHex(m, m, m);
}

void hexToMC(uint32_t hex, uint8_t *m)
{
    uint8_t r = *m, g = *m, b = *m;
    return hexToRGB(hex, &r, &g, &b);
}

double lerp(double start, double end, double tween)
{
    double result = start + (end - start) * tween;
    return result;
}

uint32_t lerpColor(uint32_t argbFrom, uint32_t argbTo, double tween)
{
    uint8_t
        a,
        r, g, b,
        a2, r2, g2, b2;
    hexToARGB(argbFrom, &a, &r, &g, &b);
    hexToARGB(argbTo, &a2, &r2, &g2, &b2);
    a = constrain(lerp(a, a2, tween), a, a2);
    r = constrain(lerp(r, r2, tween), r, r2);
    g = constrain(lerp(g, g2, tween), g, g2);
    b = constrain(lerp(b, b2, tween), b, b2);
    return argbToHex(a, r, g, b);
}

uint32_t randomColor(uint32_t min, uint32_t max)
{
    uint8_t
        aMin,
        rMin, gMin, bMin,
        aMax, rMax, gMax, bMax;
    hexToARGB(min, &aMin, &rMin, &gMin, &bMin);
    hexToARGB(max, &aMax, &rMax, &gMax, &bMax);
    aMin = randomInt(aMin, aMax);
    rMin = randomInt(rMin, rMax);
    gMin = randomInt(gMin, gMax);
    bMin = randomInt(bMin, bMax);
    return argbToHex(aMin, rMin, gMin, bMin);
}

float randomFloat(float min, float max)
{
    float r = (float)rand() / RAND_MAX;
    r *= max - min;
    r += min;
    return r;
}

uint16_t randomInt(uint16_t min, uint16_t max)
{
    uint16_t r = rand();
    r %= max - min;
    r += min;
    return r;
}

float dist(float x1, float y1, float x2, float y2)
{
    float distX = x2 - x1;
    float distY = y2 - y1;
    float sqrdX = distX * distX;
    float sqrdY = distY * distY;
    return sqrt(sqrdX + sqrdY);
}

float vecdist(vector v1, vector v2)
{
    return dist(v1.x, v1.y, v2.x, v2.y);
}

float map(float n, float start1, float stop1, float start2, float stop2, bool withinBounds)
{
    float newval = (n - start1) / (stop1 - start1) * (stop2 - start2) + start2;
    if (!withinBounds)
    {
        return newval;
    }
    if (start2 < stop2)
    {
        return constrain(newval, start2, stop2);
    }
    else
    {
        return constrain(newval, stop2, start2);
    }
}

int wrapMod(int n, int mod)
{
    return (n % mod + mod) % mod;
}