#include "ofApp.h"

const float gravity = 9.81 * 200; //arbitrary gravity change  
const float bounce = 0.8; //menor a un para que disminuya el rebote.
const float piso = 871;

//Tarea Hacer Animaciones y que la lista vaya cambiando de elementos con las teclas.
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
	inventory.push_back(hands);
	Entity sword = Entity();
	sword.name = "ESPADA";
	inventory.push_back(sword);
	Entity poison = Entity();
	poison.name = "VENENO";
	inventory.push_back(poison);
	currentItem = &hands;
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

		// Actualiza la posici�n con las velocidades
		gameObjects[i].posX += gameObjects[i].velX * ofGetLastFrameTime();
		gameObjects[i].posY += gameObjects[i].velY * ofGetLastFrameTime();

		// Verifica si toc� el piso
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
		// Define los offsets seg�n el �ndice de animaci�n
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

	// Incrementa el �ndice de animaci�n
	animationIndex += animationSpeed * deltaTime;
	if (animationIndex >= 3) animationIndex = 0;

	std::cout << animationIndex << "\n";

	if (weaponIndex < minWeapon)
		weaponIndex = minWeapon;
	if (weaponIndex > maxWeapon)
		weaponIndex = maxWeapon;

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
	}
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
