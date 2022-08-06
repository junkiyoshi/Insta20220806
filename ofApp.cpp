#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(255);
	ofEnableDepthTest();

	auto ico_sphere = ofIcoSpherePrimitive(150, 4);
	this->sphere_mesh = ico_sphere.getMesh();

	this->noise_param = ofRandom(1000);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->noise_param += 0.005;

	this->draw_sphere_mesh = this->sphere_mesh;

	for (auto& vertex : this->draw_sphere_mesh.getVertices()) {

		auto noise_value = ofNoise(glm::vec4(vertex * 0.025, noise_param));
		auto noise_param = (noise_value < 0.7 ? 1 : ofMap(noise_value, 0.7, 1, 1, 8));
		noise_param = std::pow(1.5, noise_param);
		auto noise_radius = 150 * noise_param;

		vertex = glm::normalize(vertex) * noise_radius;
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(180);
	ofRotateY(ofGetFrameNum() * 0.5);
	ofRotateX(ofGetFrameNum() * 0.5);

	ofSetColor(0);
	this->draw_sphere_mesh.draw();

	ofSetColor(255);
	this->draw_sphere_mesh.drawWireframe();

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}