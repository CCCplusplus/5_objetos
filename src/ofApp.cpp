#include "ofApp.h"

const float gravity = 9.81 * 200; //arbitrary gravity change  
const float bounce = 0.8; //menor a un para que disminuya el rebote.
const float piso = 871;


//--------------------------------------------------------------
void ofApp::setup(){
	appstate = EAppState::menu;

	titlefont.load("press.ttf", 72);
	myfont.load("press.ttf", 48);
	mainmenu.setup();
	mainmenu.add(btnEjercicio1.setup("Pelotas Rebotando"));
	mainmenu.add(btnEjercicio2.setup("Tipo Lemmings"));
	mainmenu.setPosition(ofGetWidth() / 2 - mainmenu.getWidth() / 2,
		ofGetHeight() / 2 - mainmenu.getHeight() / 2);
	btnEjercicio1.addListener(this, &ofApp::OnBtn1Pressed);
	btnEjercicio2.addListener(this, &ofApp::OnBtn2Pressed);

}

void ofApp::SetupPelotas()
{
	posx = 0;
	posy = 0;
	radioCirculo = 20;

	Entity e = Entity();
	e.posX = 100;
	e.posY = 100;
	e.velX = 70;
	e.velY = 0;
	gameObjects.push_back(e);
	Entity e2 = Entity();
	e2.posX = 200;
	e2.posY = 200;
	e2.velX = 70;
	e2.velY = 0;
	gameObjects.push_back(e2);

	std::cout << gameObjects.size() << "\n";
}

void ofApp::SetupLemmings()
{
	posx = 0;
	posy = 0;
	radioCirculo = 20;
	playerSpriteImg.load("SpriteSheet.png");
	playerSize = ofVec2f(28, 30);
	playerSizeOffSet = ofVec2f(0, 2);
	Entity hands = Entity();
	hands.name = "MANOS";
	hands.sprite.load("blank.png");
	inventory.push_back(hands);
	Entity sword = Entity();
	sword.name = "ESPADA";
	sword.sprite.load("espada.png");
	inventory.push_back(sword);
	Entity poison = Entity();
	poison.name = "VENENO";
	poison.sprite.load("veneno.png");
	inventory.push_back(poison);
	currentItem = &hands;

	axe.sprite.load("hacha.png");
	axe.name = "Hacha";

	hammer.sprite.load("martillo.png");
	hammer.name = "Martillo";

	gun.sprite.load("pistola.png");
	gun.name = "pistola";

	lastSpawnTime = ofGetElapsedTimef();
}

//--------------------------------------------------------------
void ofApp::update()
{
	if (appstate == EAppState::pelotas) {
		UpdatePelotas();
	}
	else if (appstate == EAppState::menu) {
		
	}
	else if (appstate == EAppState::lemmings) {
		UpdateLemmings();
	}
}

void ofApp::UpdatePelotas()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		// Aplica gravedad a la velocidad en Y
		gameObjects[i].velY += gravity * ofGetLastFrameTime();

		// Actualiza la posición con las velocidades
		gameObjects[i].posX += gameObjects[i].velX * ofGetLastFrameTime();
		gameObjects[i].posY += gameObjects[i].velY * ofGetLastFrameTime();

		// Verifica si tocó el piso
		if (gameObjects[i].posY >= piso) {
			gameObjects[i].posY = piso;
			gameObjects[i].velY = -gameObjects[i].velY * bounce; // Invierte la velocidad y reduce magnitud para rebote
		}
		if (gameObjects[i].posX >= ofGetWidth())
		{
			gameObjects[i].posX = ofGetWidth();
			gameObjects[i].velX = -gameObjects[i].velX * 1;
		}
		if (gameObjects[i].posX <= 0)
		{
			gameObjects[i].posX = 0;
			gameObjects[i].velX = -gameObjects[i].velX * 1;
		}
	}
}

void ofApp::UpdateLemmings()
{
	float deltaTime = ofGetLastFrameTime();

	if (w) {
		if (lastDirection != 'w') {
			animationIndex = 0;
			lastDirection = 'w';
		}
		posy -= 100 * deltaTime;
		// Define los offsets según el índice de animación
		switch ((int)animationIndex) {
		case 0: playerSizeOffSet = ofVec2f(0, 98); break;
		case 1: playerSizeOffSet = ofVec2f(32, 96); break;
		case 2: playerSizeOffSet = ofVec2f(64, 98); break;
		}
	}
	else if (s) {
		if (lastDirection != 's') {
			animationIndex = 0;
			lastDirection = 's';
		}
		posy += 100 * deltaTime;
		switch ((int)animationIndex) {
		case 0: playerSizeOffSet = ofVec2f(0, 2); break;
		case 1: playerSizeOffSet = ofVec2f(32, 0); break;
		case 2: playerSizeOffSet = ofVec2f(64, 2); break;
		}
	}
	else if (a) {
		if (lastDirection != 'a') {
			animationIndex = 0;
			lastDirection = 'a';
		}
		posx -= 100 * deltaTime;
		switch ((int)animationIndex) {
		case 0: playerSizeOffSet = ofVec2f(0, 34); break;
		case 1: playerSizeOffSet = ofVec2f(32, 32); break;
		case 2: playerSizeOffSet = ofVec2f(64, 34); break;
		}
	}
	else if (d) {
		if (lastDirection != 'd') {
			animationIndex = 0;
			lastDirection = 'd';
		}
		posx += 100 * deltaTime;
		switch ((int)animationIndex) {
		case 0: playerSizeOffSet = ofVec2f(2, 66); break;
		case 1: playerSizeOffSet = ofVec2f(34, 64); break;
		case 2: playerSizeOffSet = ofVec2f(66, 66); break;
		}
	}

	// Incrementa el índice de animación
	if(w ^ a ^ s ^ d)
	animationtransition += animationSpeed * deltaTime;
	if (animationtransition >= 3) animationtransition = 0;

	if (animationtransition > 0 && animationtransition < 1)
		animationIndex = 0;
	if (animationtransition > 1 && animationtransition < 2)
		animationIndex = 1;
	if (animationtransition > 2 && animationtransition < 3)
		animationIndex = 2;
	if (animationtransition >= 3)
		animationIndex = 3;

	if (animationIndex >= 3) animationIndex = 0;

	if (weaponIndex < minWeapon)
		weaponIndex = maxWeapon;
	if (weaponIndex > maxWeapon)
		weaponIndex = minWeapon;

	std::list<Entity>::iterator it = inventory.begin();
	if (weaponIndex == 0 && it != inventory.end()) {
		currentItem = &(*it);
	}
	else if (weaponIndex == 1 && std::next(it) != inventory.end()) {
		currentItem = &(*std::next(it));
	}
	else if (weaponIndex == 2 && std::next(it, 2) != inventory.end()) {
		currentItem = &(*std::next(it, 2));
	}
	else if (weaponIndex == 3 && std::next(it, 3) != inventory.end()) {
		currentItem = &(*std::next(it, 3));
	}
	else if (weaponIndex == 4 && std::next(it, 4) != inventory.end()) {
		currentItem = &(*std::next(it, 4));
	}
	else if (weaponIndex == 5 && std::next(it, 5) != inventory.end()) {
		currentItem = &(*std::next(it, 5));
	}

	float currentTime = ofGetElapsedTimef();
	float spawnInterval = 5.0f;

	if (currentTime - lastSpawnTime > spawnInterval) {
		SpawnRandomItem();
		lastSpawnTime = currentTime;
	}

	for (auto it = spawnedItems.begin(); it != spawnedItems.end(); ) {
		if (currentTime >= it->spawnTime) {
			float distance = ofDist(it->itemEntity.posX, it->itemEntity.posY, posx, posy);
			if (distance < radioCirculo) {
				inventory.push_back(it->itemEntity);
				if(maxWeapon < 6)
				maxWeapon++;
				it = spawnedItems.erase(it);
			}
			else {
				++it;
			}
		}
		else {
			++it;
		}
	}
}


//--------------------------------------------------------------
void ofApp::draw(){

	ofCircle(posx, posy, radioCirculo);
	ofSetColor(240, 12, 12);

	if (appstate == EAppState::pelotas) {
		ofBackground(ofColor::cornflowerBlue);

		if (gameObjects.size() > 0)
		{
			for (int i = 0; i < gameObjects.size(); i++)
			{
				gameObjects[i].draw();
			}
		}
	}
	else if (appstate == EAppState::menu) {
		ofBackground(ofColor::hotPink);
		mainmenu.draw();
	}
	else if (appstate == EAppState::lemmings) {
		ofBackground(ofColor::lightBlue);
		ofSetColor(0, 0, 0);
		titlefont.drawString("ORE NO BUKI", 100, 100);
		ofSetColor(252, 252, 252);
		playerSpriteImg.drawSubsection(posx, posy, playerSize.x, playerSize.y, playerSizeOffSet.x, playerSizeOffSet.y);
		myfont.drawString(currentItem == nullptr ? "NULL" : currentItem->name.c_str(), posx, posy);
		if (currentItem && currentItem->sprite.isAllocated()) 
			currentItem->sprite.draw(posx+25, posy);
		for (auto& itemSpawn : spawnedItems) {
			float currentTime = ofGetElapsedTimef();
			if (currentTime >= itemSpawn.spawnTime) {
				itemSpawn.itemEntity.sprite.draw(itemSpawn.itemEntity.posX, itemSpawn.itemEntity.posY);
			}
		}
	}
}

void ofApp::SpawnRandomItem() {
	std::vector<Entity> items = { axe, hammer, gun };

	int randomIndex = ofRandom(items.size());
	Entity selectedItem = items[randomIndex];

	selectedItem.posX = ofRandom(ofGetWidth());
	selectedItem.posY = ofRandom(ofGetHeight());

	ItemSpawn newItem;
	newItem.itemEntity = selectedItem;
	newItem.spawnTime = ofGetElapsedTimef() + ofRandom(3, 10);

	spawnedItems.push_back(newItem);
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	if (key == 'w') w = true;
	if (key == 'a') a = true;
	if (key == 's') s = true;
	if (key == 'd') d = true;

	if (appstate == EAppState::lemmings) {
    if (key == 57357) { // Siguiente item
		weaponIndex++;
    }
    if (key == 57359) { // Item anterior
		weaponIndex--;
    }
}

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key)
{
	if (key == 'w') w = false;
	if (key == 'a') a = false;
	if (key == 's') s = false;
	if (key == 'd') d = false;
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button)
{
	//cambio de color cuando se instancie
	if (x >= 0 && y >= 0 && x <= ofGetWidth() && y <= ofGetHeight()) {
		Entity newEntity = Entity();
		newEntity.posX = x;
		newEntity.posY = y;
		newEntity.velX = 70;
		newEntity.velY = 70;
		newEntity.entityColor.set(ofRandom(255), ofRandom(255), ofRandom(255));
		gameObjects.push_back(newEntity);

	}
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

void ofApp::OnBtn1Pressed()
{
	appstate = EAppState::pelotas;
	SetupPelotas();
}

void ofApp::OnBtn2Pressed()
{
	appstate = EAppState::lemmings;
	SetupLemmings();
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
