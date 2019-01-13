#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(39);
	ofSetColor(39);

	ofNoFill();
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);

	this->len_min = 14;
	this->len_max = 72;

	for (int x = this->len_max * 0.5; x < ofGetWidth(); x += this->len_max) {

		for (int y = this->len_max * 0.5; y < ofGetHeight(); y += this->len_max) {

			this->rect_locations.push_back(glm::vec2(x, y));
		}
	}

	for (int i = 0; i < this->rect_locations.size(); i++) {

		vector<float> rect_len;
		this->rect_lens.push_back(rect_len);
	}
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);

	this->agent_locations.clear();
	for (int i = 0; i < 8; i++) {

		agent_locations.push_back(glm::vec2(
			ofMap(ofNoise(ofRandom(10000), ofGetFrameNum() * 0.005), 0, 1, 0, ofGetWidth()),
			ofMap(ofNoise(ofRandom(10000), ofGetFrameNum() * 0.005), 0, 1, 0, ofGetHeight())
		));
	}

	for (int i = 0; i < this->rect_locations.size(); i++) {

		for (int l = this->rect_lens[i].size() - 1; l > -1; l--) {

			this->rect_lens[i][l] += 3;
			if (this->rect_lens[i][l] > this->len_max) {

				this->rect_lens[i].erase(this->rect_lens[i].begin() + l);
			}
		}
	}

	for (int i = 0; i < this->agent_locations.size(); i++) {

		for (int rect_index = 0; rect_index < this->rect_locations.size(); rect_index++) {

			if (this->agent_locations[i].x > this->rect_locations[rect_index].x - this->len_max * 0.5 && this->agent_locations[i].x < this->rect_locations[rect_index].x + this->len_max * 0.5 &&
				this->agent_locations[i].y > this->rect_locations[rect_index].y - this->len_max * 0.5 && this->agent_locations[i].y < this->rect_locations[rect_index].y + this->len_max * 0.5) {

				this->rect_lens[rect_index].push_back(this->len_min);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofNoFill();
	for (int i = 0; i < this->rect_locations.size(); i++) {

		for (int l = this->rect_lens[i].size() - 1; l > -1; l--) {

			ofSetColor(239);
			//ofSetColor(239, ofMap(this->rect_lens[i][l], this->len_min, this->len_max, 255, 32));
			ofDrawRectangle(this->rect_locations[i], this->rect_lens[i][l], this->rect_lens[i][l]);
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}