// Variant with SimpleGUI

#include <stdlib.h>
#include "MicroGlut.h"
#include "LoadTGA.h"
#define MAIN
#include "SpriteLight2.h"
#include "GL_utilities.h"
#include "VectorUtils4.h"
#include "SimpleGUI.h"
#include "iostream"
// uses framework OpenGL
// uses framework Cocoa

// Add more globals as needed

// Example of user controllable parameter
float someValue = 1.0;
float kAlignmentWeight = 0.1;
float kCohesionWeight = 0.05;
float kAvoidanceWeight = 0.2;
float kMaxDistance = 100.0;
float kSeparationDistance = 70.0;

vec3 CalcAvoidance(vec3 i_pos, vec3 j_pos) {
    vec3 avoidVec = vec3(0,0,0);

    float dist = Norm(i_pos - j_pos);
    vec3 diff = i_pos - j_pos;

    if(dist < kSeparationDistance){
        avoidVec = ScalarMult(diff, 1-dist/kSeparationDistance);
    }

    return avoidVec;
}

void SpriteBehavior() // Your code!
{
// Add your lab code here. You may edit anywhere you want, but most of it goes here.
// You can start from the global list gSpriteRoot.


    int counter;

    for(int i = 0; i < sprites.size(); i++) {

        // Food doesn't move
//        if(sprites[i].food == true){
//            continue;
//		}

        counter = 0;

        sprites[i].speedDiff = vec3(0,0,0);
        sprites[i].avgPos = vec3(0,0,0);
        sprites[i].avoidanceVec = vec3(0,0,0);

        for(int j = 0; j < sprites.size(); j++) {
            if(i == j){
                continue;
            }

            // Food attraction
            if(sprites[j].food == true){
                continue;
            }

            if(Norm(sprites[i].position - sprites[j].position) < kMaxDistance){
                // Cohesion
                sprites[i].avgPos += sprites[j].position - sprites[i].position;

                // Separation
                sprites[i].avoidanceVec += CalcAvoidance(sprites[i].position, sprites[j].position);

                // Alignment
                sprites[i].speedDiff += sprites[j].speed - sprites[i].speed;

                counter++;
            }



        }

        if(counter > 0){
            sprites[i].speedDiff = sprites[i].speedDiff / counter;
            sprites[i].avgPos = sprites[i].avgPos / counter;
            sprites[i].avoidanceVec = sprites[i].avoidanceVec / counter;
        }
        if(sprites[i].busig == true){
            vec3 random = vec3((((float)(rand() % 11 + 1) -6) ), (((float)(rand() % 11 + 1) -6) ), 0.0);
            sprites[i].position += random;
            //sprites[i].speed = vec3(1.5, 1.5, 0);
            //std::cout << (((float)(rand() % 11 + 1) -6) /10) << "\n";

        }


    }


    for(int i = 0; i < sprites.size(); i++){

        // Food doesn't move
        if(sprites[i].food == true){
            continue;
		}

        sprites[i].speed += sprites[i].speedDiff*kAlignmentWeight
                           + sprites[i].avgPos*kCohesionWeight
                           + sprites[i].avoidanceVec*kAvoidanceWeight;

        sprites[i].position += sprites[i].speed;
    }
}

// Drawing routine
void Display()
{
	glClearColor(0, 0, 0.2, 1);
	glClear(GL_COLOR_BUFFER_BIT+GL_DEPTH_BUFFER_BIT);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	DrawBackground();

	SpriteBehavior(); // Your code

// Loop though all sprites. (Several loops in real engine.)
	for (int i = 0; i < sprites.size(); i++)
	{
		// Your code
		// Example affecting sprites by a controllable parameter

		if(sprites[i].food == false){
            sprites[i].speed = normalize(sprites[i].speed) * someValue;
		}



		HandleSprite(&sprites[i]); // Default movement my speed. Callback in a real engine
		DrawSprite(&sprites[i]);
	}

	sgDraw();

	glutSwapBuffers();
}

void Reshape(int h, int v)
{
	glViewport(0, 0, h, v);
	gWidth = h;
	gHeight = v;
}

void Key(unsigned char key,
         __attribute__((unused)) int x,
         __attribute__((unused)) int y)
{
  switch (key)
  {
    case '+':
    	someValue += 0.1;
    	printf("someValue = %f\n", someValue);
    	break;
    case '-':
    	if (someValue > 0.5) someValue -= 0.1;
    	printf("someValue = %f\n", someValue);
    	break;
    case '1':
    	kCohesionWeight -= 0.01;
    	printf("CohesionWeight = %f\n", kCohesionWeight);
    	break;
    case '2':
    	kCohesionWeight += 0.01;
    	printf("CohesionWeight = %f\n", kCohesionWeight);
    	break;
    case '3':
    	kAvoidanceWeight -= 0.01;
    	printf("AvoidanceWeight = %f\n", kAvoidanceWeight);
    	break;
    case '4':
    	kAvoidanceWeight += 0.01;
    	printf("AvoidanceWeight = %f\n", kAvoidanceWeight);
    	break;
    case '5':
    	kAlignmentWeight -= 0.01;
    	printf("AlignmentWeight = %f\n", kAlignmentWeight);
    	break;
    case '6':
    	kAlignmentWeight += 0.01;
    	printf("AlignmentWeight = %f\n", kAlignmentWeight);
    	break;
    case 0x1b:
      exit(0);
  }
}

void Init()
{
	TextureData *sheepFace, *blackieFace, *dogFace, *foodFace;

	LoadTGATextureSimple("bilder/leaves.tga", &backgroundTexID); // Background

	sheepFace = GetFace("bilder/sheep.tga"); // A sheep
	blackieFace = GetFace("bilder/blackie.tga"); // A black sheep
	dogFace = GetFace("bilder/dog.tga"); // A dog
	foodFace = GetFace("bilder/mat.tga"); // Food

	NewSprite(sheepFace, 100, 400, 0, -1, false, false);
	NewSprite(sheepFace, 100, 100, 0, 1, false, false);
	NewSprite(sheepFace, 600, 400, 0, -1, false, false);
	NewSprite(dogFace, 600, 200, 0, 1, false, false);
	NewSprite(dogFace, 400, 300, 1, 0, false, false);
	NewSprite(blackieFace, 600, 100, 1, -0.5, true, false);
	NewSprite(foodFace, 400, 100, 0.0, 0.0, false, true);

	sgCreateStaticString(20, 40, "Slider and float display");
	sgCreateSlider(-1, -1, 200, &someValue, 0.5, 5);
	sgCreateDisplayFloat(-1, -1, "Speed: ", &someValue);
	sgCreateDisplayFloat(-1, -1, "CohesionWeight: ", &kCohesionWeight);
	sgCreateDisplayFloat(-1, -1, "AvoidanceWeight: ", &kAvoidanceWeight);
	sgCreateDisplayFloat(-1, -1, "AlignmentWeight: ", &kAlignmentWeight);

	// Always fix the colors if it looks bad.
        sgSetFrameColor(0,0,0);
        sgSetBackgroundColor(1, 1, 1, 0.5);
        sgSetTextColor(0, 0, 0);
}

void mouse(int button, int state, int x, int y)
{
	sgMouse(state, x, y);
	glutPostRedisplay();
}

void drag(int x, int y)
{
	sgMouseDrag(x, y);
	glutPostRedisplay();
}

int main(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(800, 600);
	glutInitContextVersion(3, 2);
	glutCreateWindow("Lab 4 Flocking");

	glutDisplayFunc(Display);
	glutRepeatingTimer(20); // Should match the screen synch
	glutReshapeFunc(Reshape);
	glutKeyboardFunc(Key);
	glutMouseFunc(mouse);
	glutMotionFunc(drag);

	InitSpriteLight();
	Init();

	glutMainLoop();
	return 0;
}
