#include "ofApp.h"

const float gravity = 20;  
const float bounce = 0.8; //menor a un para que disminuya el rebote.
const float piso = 850;
//--------------------------------------------------------------
void ofApp::setup(){
	posx = 0;
	posy = 0;
	radioCirculo = 20;

	Entity e = Entity();
	e.posX = 100;
	e.posY = 100;
	e.velX = 0;
	e.velY = 0;
	gameObjects.push_back(e);
	Entity e2 = Entity();
	e2.posX = 200;
	e2.posY = 200;
	e2.velX = 0;
	e2.velY = 0;
	gameObjects.push_back(e2);

	std::cout << gameObjects.size() << "\n";

}

//--------------------------------------------------------------
void ofApp::update()
{
	for (int i = 0; i < gameObjects.size(); i++)
	{
		// Aplica gravedad a la velocidad en Y
		gameObjects[i].velY += gravity * ofGetLastFrameTime();
		gameObjects[i].velX = 10;

		// Actualiza la posición con las velocidades
		gameObjects[i].posX += gameObjects[i].velX * ofGetLastFrameTime();
		gameObjects[i].posY += gameObjects[i].velY * ofGetLastFrameTime();

		// Verifica si tocó el piso
		if (gameObjects[i].posY >= piso) {
			gameObjects[i].posY = piso;
			gameObjects[i].velY = -gameObjects[i].velY * bounce; // Invierte la velocidad y reduce magnitud para rebote
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(ofColor::cornflowerBlue);

	ofSetColor(240, 12, 12);
	ofCircle(posx, posy, radioCirculo);

	if (gameObjects.size() > 0)
	{
		for (int i = 0; i < gameObjects.size(); i++)
		{
			gameObjects[i].draw();
		}
	}

}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

	posx = x;
	posy = y;

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
	posx = x;
	posy = y;
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

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

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
