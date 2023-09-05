#pragma once

#include "ofMain.h"
#include <vector>
#include "Entity.h"
#include "ofxGui.h"

struct ItemSpawn {
	Entity itemEntity; // Entidad del item
	float spawnTime; // Tiempo para aparecer
};


class ofApp : public ofBaseApp{

	public:
		void setup();
		void SetupPelotas();
		void SetupLemmings();
		void update();
		void UpdatePelotas();
		void UpdateLemmings();
		void draw();
		void SpawnRandomItem();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

		float radioCirculo;

		std::vector<Entity> gameObjects;
		std::list<ItemSpawn> spawnedItems;

		enum EAppState {
			menu, pelotas, lemmings, mas
		}appstate;

		ofTrueTypeFont titlefont;
		ofTrueTypeFont myfont;
		ofxPanel mainmenu;
		ofxButton btnEjercicio1, btnEjercicio2;

		void OnBtn1Pressed();

		void OnBtn2Pressed();

		ofImage playerSpriteImg;
		float posx;
		float posy;
		ofVec2f playerSize;
		ofVec2f playerSizeOffSet;

		bool w, s, a, d;
		std::list<Entity> inventory;
		Entity* currentItem;
		ofImage bokuNoImage;

		int animationIndex = 0;
		float animationtransition = 0.0f;
		float animationSpeed = 7.5f; 
		char lastDirection = 0; 

		int weaponIndex = 0;
		int minWeapon = 0;
		int maxWeapon = 2;
		float lastSpawnTime;

		Entity axe, hammer, gun;
};
