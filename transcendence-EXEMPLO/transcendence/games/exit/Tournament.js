import * as THREE from 'three';
import Game from './Game.js';
import * as maps from './maps/maps.js';
import * as constants from './constants.js';
import createText from './createText.js';
import { Menu } from './Menu.js';
import translation from './languages.js';


export var forceStopGame = null;

export default class Tournament {
	constructor(scene, camera, font, gameToWin=2, playersNb=3, isPowerupsOn=true, language='en') {
		forceStopGame = false;
		this.scene = scene;
		this.clock = new THREE.Clock();
		this.camera = camera;
		this.font = font;
		this.language = language;
		this.playersNb = playersNb;
		this.gameToWin = gameToWin; // number of games to win
		this.isPowerupsOn = isPowerupsOn;
		this.isOver = false;
		this.menu = new Menu({scene: scene, camera: camera, font: font, playersNb: playersNb, language: language});
		this.allMaps = maps.tournamentMap;
		this.scores = []
		for (let i = 0; i < playersNb; i++) {
			this.scores.push(0);
		}
	}

	createScoresTexts(showGameToWin=true) {
		// clear the previous texts
		if (this.scoresTexts) {
			for (let text of this.scoresTexts) {
				this.scene.remove(text);
			}
		}
		this.scoresTexts = [];
		var space = 1.6;
		for (let i = 0; i < this.scores.length; i++) {
			var frontColor = this.game.players[i].mesh.material.color;
			var text = createText({font: this.font, message: this.scores[i].toString(), size: 1.8, depth: 0.2, frontColor: frontColor, sideColor: '#888888'});
			text.position.x = i*space;
			text.position.y = -3;
			text.position.z = -.5;
			this.scene.add(text);
			this.scoresTexts.push(text);
		}
		if (showGameToWin) {
			var text = createText({font: this.font, message: '/'+this.gameToWin.toString(), size: 2, depth: 0.2, frontColor: '#ffffff', sideColor: '#888888'});
			text.position.x = (this.scores.length+.4)*space;
			text.position.y = -3;
			text.position.z = -.5;
			this.scene.add(text);
			this.scoresTexts.push(text);
		}
	}

	initNewGame() {
		var randomTournamentMap = this.allMaps[Math.floor(Math.random()*this.allMaps.length)];
		this.allMaps = this.allMaps.filter(map => map !== randomTournamentMap);
		if (this.allMaps.length == 0) { // all maps have been played
			this.allMaps = maps.tournamentMap;
		}
		// randomTournamentMap = maps.speedySquare; // To choose a specific map
		this.game = new Game(this.scene, this.camera, randomTournamentMap, this.playersNb, this.isPowerupsOn);
		this.createScoresTexts();
	}

	destroyGame() {
		this.game.delete();
		this.game = null;
	}

	delete() {
		if (this.game)
			this.game.delete();
		if (this.menu)
			this.menu.delete();
		if (this.helperText)
			this.scene.remove(this.helperText);
		if (this.scoresTexts) {
			for (let text of this.scoresTexts) {
				this.scene.remove(text);
			}
		}
	}

	onGameOver(winner) {
		if (this.helperText) {
			this.scene.remove(this.helperText);
			this.helperText = null;
		}
		this.scores[winner.playerNb]++;
		if (this.scores[winner.playerNb] >= this.gameToWin) {
			this.isOver = true;
			this.createScoresTexts(false);
			if (!constants.DEBUG)
				this.camera.position.x = 0;
		} else {
			this.destroyGame();
			this.initNewGame();
		}
	}

	showContinueText(winner, text=translation['pressEnter'][this.language], zOffset=1.5) {
		if (this.helperText) {
			this.helperText.traverse( function (child) {
				if (child.geometry)
					child.geometry.dispose();
			} );
			this.scene.remove(this.helperText);
		}

		this.helperText = createText({font: this.font, message: text, size: .7, depth: 0.2, frontColor: '#ffffff', sideColor: '#888888'});
		this.helperText.position.y = winner.mesh.position.y + 2;
		this.helperText.position.x = winner.mesh.position.x;
		this.helperText.position.z = zOffset;
		this.helperText.rotation.x = .2;
		this.scene.add(this.helperText);
	}

	winScreen(dt) {
		this.showContinueText(this.game.winner, translation['gameOver'][this.language], 2);
		this.game.particlesSystem.update(dt);
		for (let player of this.game.players) {
			player.update(dt, [], this.game.mapData, this.game.powerups, false);
		}
		var mapWidth = this.game.mapData.getWidth();
		for (var i = 0; i < this.scores.length; i++) {
			var player = this.game.players[i];
			if (player == this.game.winner) { // winner
				player.tpToPosition(i*1.5+mapWidth/2, -4);
				player.do360(dt);
			} else { // loosers
				player.tpToPosition(i*1.5+mapWidth/2, -2);
				player.mesh.position.z = 0;
				player.deceptionAnimation(dt);
				player.spotLight.intensity = player.spotLightIntensity/2;

			}
		}
		if (!constants.DEBUG) {
			this.camera.position.z = 5;
			if (this.camera.position.x < this.game.winner.mesh.position.x)
				this.camera.position.x += 3 * dt;
			this.camera.position.y = this.game.winner.mesh.position.y-3;
			this.camera.lookAt(this.game.winner.mesh.position);
			this.camera.rotation.x = .7;
			this.camera.rotation.y = 0;
			this.camera.rotation.z = 0;
		}
	}

	getScores() {
		return this.scores;
	}

	update(keysJustPressed) {
		var dt = this.clock.getDelta();
		if (this.menu  && !this.menu.update(dt, keysJustPressed)) {
			this.menu = null;
			this.initNewGame();
		} else {
			if (keysJustPressed.includes(46)) {
				this.game.players[0].position.x = -1;
				this.game.players[0].movingDirection.x = -1;
			}
			if (this.game && !this.isOver) {
				this.game.update(keysJustPressed);
				if (this.game.winner !== null) {
					this.showContinueText(this.game.winner);
					if (keysJustPressed.includes(13))
						this.onGameOver(this.game.winner);
				}
			}

			else if (this.isOver) {
				this.winScreen(dt);
				if (keysJustPressed.includes(13)) {
					this.delete();
					return false;
				}
			}
		}
		if (forceStopGame) {
			this.delete();
			return false;
		}
		return true;
	}
}
