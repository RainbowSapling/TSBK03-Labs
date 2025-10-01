#ifndef _SPRITELIGHT_
#define _SPRITELIGHT_

// SpriteLight - Heavily simplified sprite engine
// by Ingemar Ragnemalm 2009

// What does a mogwai say when it sees a can of soda?
// Eeek! Sprite light! Sprite light!

#include "LoadTGA.h"
#include "VectorUtils4.h"
#include <vector>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct SpriteRec
{
	vec3 position; // OBS! Really 2D, declared as vec3 to make functions like normalizations compatible.
	TextureData *face;
	vec3 speed;
	GLfloat rotation;
	struct SpriteRec *next;

	// Add custom sprite data here as needed
	vec3 speedDiff;
	vec3 avgPos;
	vec3 avoidanceVec;
	bool busig;
	bool food;

} SpriteRec, *SpritePtr;

// Globals: The sprite list, background texture and viewport dimensions (virtual or real pixels)
//extern SpritePtr gSpriteRoot;
extern std::vector<SpriteRec> sprites;
extern GLuint backgroundTexID;
extern long gWidth, gHeight;

// Functions
TextureData *GetFace(const char *fileName);
int NewSprite(TextureData *f, GLfloat h, GLfloat v, GLfloat hs, GLfloat vs, bool busig, bool food);
void HandleSprite(SpritePtr sp);
void DrawSprite(SpritePtr sp);
void DrawBackground();

void InitSpriteLight();


#ifdef __cplusplus
}
#endif

#endif
