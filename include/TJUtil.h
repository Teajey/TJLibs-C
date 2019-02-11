#ifndef _TJUTIL_H_
#define _TJUTIL_H_

#include <stdint.h>
#include <stdbool.h>

#if __x86_64__
#define PTR_T uint64_t
#else
#define PTR_T uint32_t
#endif

typedef struct TJList {
	PTR_T* elems;
	size_t length;
} TJList;

//--TJList
void TJList_create(TJList* list, void* ptrArr, size_t length);
void TJList_resize(TJList* list, size_t newLength);
void TJList_destroy(TJList* list);
void* TJList_get(TJList* list, size_t index);
void** TJList_array(TJList* list);
void TJList_add(TJList* list, void* elemAddr);
void TJList_insert(TJList* list, void* elem, size_t index);
void TJList_removeAt(TJList* list, size_t index);
void TJList_remove(TJList* list, void* elemAddr);
void TJList_printbin(TJList* list);

enum AnchorPoints {
	TOP = 0b0011,
	LEFT = 0b0110,
	CENTER = 0b1111,
	BOTTOM = 0b1100,
	RIGHT = 0b1001
};

typedef struct vector {
    float x;
    float y;
} vector;

//--TJUtil
double constrain(double n, double low, double high);
uint32_t argbToHex(int a, int r, int g, int b);
void hexToARGB(uint32_t hex, uint8_t* a, uint8_t* r, uint8_t* g, uint8_t* b);
uint32_t rgbToHex(int r, int g, int b);
void hexToRGB(uint32_t hex, uint8_t* r, uint8_t* g, uint8_t* b);
uint32_t mcToHex(int m);
void hexToMC(uint32_t hex, uint8_t* m);
double lerp(double start, double end, double tween);
uint32_t lerpColor(uint32_t rgbFrom, uint32_t rgbTo, double tween);
float randomFloat(float min, float max);
float dist(float x1, float y1, float x2, float y2);
float vecdist(vector v1, vector v2);
float map(float n, float start1, float stop1, float start2, float stop2, bool withinBounds);
int wrapMod(int n, int mod);

#endif