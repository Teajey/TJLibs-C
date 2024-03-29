#ifndef TJUTIL_H
#define TJUTIL_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

#if __x86_64__
#define PTR_T uint64_t
#else
#define PTR_T uint32_t
#endif

typedef struct TJList
{
	void *elements;
	size_t length;
	size_t elementSize;
} TJList;

void TJList_addArray(TJList *list, void *array, size_t arrLength);
void TJList_add(TJList *list, void *element);
void TJList_init(TJList *list, void *initArray, size_t elementSize, size_t length);
void TJList_destroy(TJList *list);
void *TJList_get(TJList *list, size_t index);

enum AnchorPoints
{
	TOP = 0b0011,
	LEFT = 0b0110,
	CENTER = 0b1111,
	BOTTOM = 0b1100,
	RIGHT = 0b1001
};

typedef struct vector
{
	float x;
	float y;
} vector;

//--TJUtil
double constrain(double n, double low, double high);
uint32_t argbToHex(int a, int r, int g, int b);
void hexToARGB(uint32_t hex, uint8_t *a, uint8_t *r, uint8_t *g, uint8_t *b);
uint32_t rgbToHex(int r, int g, int b);
void hexToRGB(uint32_t hex, uint8_t *r, uint8_t *g, uint8_t *b);
uint32_t mcToHex(int m);
void hexToMC(uint32_t hex, uint8_t *m);
double lerp(double start, double end, double tween);
uint32_t lerpColor(uint32_t rgbFrom, uint32_t rgbTo, double tween);
uint32_t randomColor(uint32_t min, uint32_t max);
float randomFloat(float min, float max);
uint16_t randomInt(uint16_t min, uint16_t max);
float dist(float x1, float y1, float x2, float y2);
float vecdist(vector v1, vector v2);
float map(float n, float start1, float stop1, float start2, float stop2, bool withinBounds);
int wrapMod(int n, int mod);

#endif