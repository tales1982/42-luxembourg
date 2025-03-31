import * as THREE from 'three';

import createText from './createText.js';
import translation from './languages.js';


class PlayerCreator {
	constructor(scene, camera, game, playerNb, playerName, font, language) {
		this.scene = scene;
		this.camera = camera;
		this.game = game;
		this.playerName = playerName;
		this.font = font;
		this.language = language;
		this.player = this.game.createHumanPlayer(playerNb, playerName);
		this.game.addPlayer(this.player);
		this.player.paddle.mesh.position.z = 240;
		// this.player.paddle.mesh.position.z = 285;
		// this.player.paddle.mesh.position.x -=24;
		// this.player.paddle.mesh.position.y -=24;

		this.fallSpeed = 0;
		this.gravity = 400;
	}

	setText({text, font=this.font, x=0, y=0, z=0}) {
		if (this.currentText == text)
			return;
		if (this.textObj) {
			this.textObj.traverse( function (child) {
				if (child.geometry)
					child.geometry.dispose();
			} );
			this.scene.remove(this.textObj);
		}
		this.textObj = createText({font: font, message: text});
		this.textObj.position.x = x;
		this.textObj.position.y = y;
		this.textObj.position.z = z;
		this.scene.add(this.textObj);
		this.currentText = text;
	}

	ifKeyValid(keyCode) {
		return keyCode >= 65 && keyCode <= 90 || keyCode == 38 || keyCode == 40;
	}

	askUpKey(keysJustPressed) {
		this.setText({
			text: this.playerName + translation['askKeyUp'][this.language],
			x: 0, y: 30, z: 250,
		});
		if (keysJustPressed.length > 0 && keysJustPressed[0] != this.keyDown && this.ifKeyValid(keysJustPressed[0]))
		{
			this.keyUp = keysJustPressed[0];
			this.player.setUpKeyCode(this.keyUp);
		}
	}

	askDownKey(keysJustPressed) {
		this.setText({
			text: this.playerName + translation['askKeyDown'][this.language],
			x: 0, y: 30, z: 250
		});
		if (keysJustPressed.length > 0 && keysJustPressed[0] != this.keyUp && this.ifKeyValid(keysJustPressed[0]))
		{
			this.keyDown = keysJustPressed[0];
			this.player.setDownKeyCode(this.keyDown);

		}
	}

	askPaddleMaterial(keysJustPressed) {
		// set the key string text
		var keyDownStr = String.fromCharCode(this.keyDown);
		if (this.keyDown == 40)
			keyDownStr = translation['directionalKeyDown'][this.language];
		else if (this.keyDown == 38)
			keyDownStr = translation['directionalKeyUp'][this.language];
		var keyUpStr = String.fromCharCode(this.keyUp);
		if (this.keyUp == 40)
			keyUpStr = translation['directionalKeyDown'][this.language];
		else if (this.keyUp == 38)
			keyUpStr = translation['directionalKeyUp'][this.language];

		this.setText({
			text:this.playerName + translation['askPaddleSkin'][this.language] +
					" (" + keyUpStr + "/"+ keyDownStr + ")",
				x: 0, y: 30, z: 253});

		if (keysJustPressed.length > 0)
		{
			if (keysJustPressed.includes(this.keyUp))
				this.player.paddle.changeSkin(1);
			else if (keysJustPressed.includes(this.keyDown))
				this.player.paddle.changeSkin(-1);
			else if (keysJustPressed[0] == 13)
			{
				this.color = true;
			}
		}
	}

	makePaddleFall(dt) {
		this.scene.remove(this.textObj);
		if (this.player.paddle.mesh.position.z > this.player.paddle.body.position.z)
		{
			this.player.paddle.mesh.position.z -= this.fallSpeed * dt;
			this.fallSpeed += this.gravity * dt;
			return true;
		}
		this.player.paddle.mesh.position.z = this.player.paddle.body.position.z;
		return false;
	}

	update(dt, keysJustPressed)
	{
		if (this.keyUp == null)
			this.askUpKey(keysJustPressed);
		else if (this.keyDown == null)
			this.askDownKey(keysJustPressed);
		else if (!this.color)
			this.askPaddleMaterial(keysJustPressed);
		else if (!this.makePaddleFall(dt))
			return true;
		return false;
	}
}

export default class Menu {
	constructor(scene, camera, font, game , humanPlayersName, AIPlayerNb, language) {
		this.scene = scene;
		this.camera = camera;
		this.game = game;
		this.font = font;
		this.language = language;
		this.humanPlayersName = humanPlayersName;
		this.humanPlayerNb = humanPlayersName.length;
		this.AIPlayerNb = AIPlayerNb;
		this.playersNb = this.humanPlayerNb + AIPlayerNb;

		this.clock = new THREE.Clock();

		this.camera.position.z = 308;
		this.isDesactivated = false;

		this.currentPlayer = 0;
		this.players = [];
		if (this.humanPlayerNb > 0) {
			var humanPlayerName = this.humanPlayersName.shift();
			this.currentPlayerCreator = new PlayerCreator(scene, camera, game, this.currentPlayer, humanPlayerName, font, language);
			this.humanPlayerNb--;
		} else {
			this.currentPlayer--;
		}
	}

	zoomTo(dt, value)
	{
		if (this.camera.position.z > value)
		{
			this.camera.position.z -= 200 * dt;
			return false;
		}

		this.camera.position.z = value;
		return true;
	}

	update(keysJustPressed)
	{
		if (this.isDesactivated)
			return false;
		var dt = this.clock.getDelta();
		this.game.background.update(dt);

		if (this.currentPlayer < this.playersNb || (this.playersNb==2 && this.currentPlayer==2))
		{
			if (!this.currentPlayerCreator || this.currentPlayerCreator.update(dt, keysJustPressed))
			{
				this.currentPlayer++;
				if (this.playersNb==2 && this.currentPlayer==1) { // special 2 player map
					this.currentPlayer++;
				}
				if (this.currentPlayer < this.playersNb || (this.playersNb==2 && this.currentPlayer==2)) {
					if ((this.currentPlayer%2!=0 && this.AIPlayerNb > 0) || this.humanPlayerNb == 0) {
						this.game.addPlayer(this.game.createAiPlayer(this.currentPlayer));
						this.AIPlayerNb--;
					} else {
						var humanPlayerName = this.humanPlayersName.shift();
						this.currentPlayerCreator = new PlayerCreator(this.scene, this.camera, this.game, this.currentPlayer, humanPlayerName, this.font, this.language);
						this.humanPlayerNb--;
					}
				}
			}
		}
		else if (this.zoomTo(dt, 86))
			{
				this.game.createNewRound();
				this.isDesactivated = true;
				return true;
			}
		return true;
	}
}
