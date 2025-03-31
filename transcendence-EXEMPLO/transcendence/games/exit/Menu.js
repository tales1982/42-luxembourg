import * as THREE from 'three';

import * as constants from './constants.js';
import createText from './createText.js';
import translation from './languages.js';
import {presets} from './Player.js';


export class Menu {
	constructor({scene, camera, renderer, font, playersNb=3, language='en'}) {
		this.scene = scene;
		this.camera = camera;
		this.renderer = renderer;
		this.playersNb = playersNb;
		this.font = font;
		this.language = language;
		this.menu = new THREE.Object3D();
		this.scene.add(this.menu);
		this.yPos = -18;
		this.createMenu();
		this.inMenu = true;
	}

	createMenu() {
		const title = createText({font: this.font, message: constants.NAME, size: 5, depth: 1, frontColor: '#ffffff', sideColor: '#000000'});
		title.position.y = this.yPos;
		this.menu.add(title);
		const start = createText({font: this.font, message: translation['enterToStart'][this.language], size: 1.7, depth: 0.5, frontColor: '#ffffff', sideColor: '#000000'});
		start.position.x = -300;
		this.menu.add(start);
		var minYPos = this.createPlayersKeys();
		start.position.y = minYPos-4;
	}

	createPlayersKeys() {
		var ySpace = 3;
		var text = createText({font: this.font, message: translation['keys'][this.language], size: 2.2, depth: 0.2, frontColor: frontColor, sideColor: '#888888'});
		text.position.y = this.yPos - 6;
		text.position.x = -50;
		this.menu.add(text);
		var minYPos;

		for (let i = 0; i < this.playersNb; i++) {
			var frontColor = presets[i].color;
			var text = createText({font: this.font, message: presets[i].upKeyText+' '+presets[i].leftKeyText+' '+presets[i].downKeyText+' '+presets[i].rightKeyText, size: 1.6, depth: 0.2, frontColor: frontColor, sideColor: '#888888'});
			text.position.x = -100 - i*10;
			text.position.y = this.yPos - 10 - i*ySpace;
			this.menu.add(text);
			minYPos = text.position.y;
		}
		return minYPos
	}

	moveRightAllMeshes(dt, xPos=0, speed=80) {
		for (let mesh of this.menu.children) {
			if (mesh.position.x < xPos)
				mesh.position.x += speed * dt;
			else
				mesh.position.x = xPos;
		}
	}

	delete() {
		this.scene.remove(this.menu);
	}

	moveCameraToMenu(dt) {
		if (constants.DEBUG)
			return true;
		var hasMoved = true;
		if (this.camera.position.y > this.yPos-10) {
			this.camera.position.y -= 14 * dt;
			hasMoved = false;
		}
		if (this.camera.position.z < 20) {
			this.camera.position.z += 10 * dt;
			hasMoved = false;
		}
		if (this.camera.position.x > 0) {
			this.camera.position.x -= 10 * dt;
			hasMoved = false;
		}
		this.camera.rotation.y = 0;
		this.camera.rotation.z = 0;
		this.camera.rotation.x = 0;
		return hasMoved;
	}

	update(dt, keysJustPressed) {
		if (this.inMenu) {
			if (this.moveCameraToMenu(dt)) {
				this.moveRightAllMeshes(dt);

				if (keysJustPressed.includes(13)) {
					return false;
				}
				// this.delete();
			}
		}
		return true;
	}
}
