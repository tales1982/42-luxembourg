import * as constants from './constants.js';
import Game from './Game'
import Menu from './Menu.js';
import createText from './createText.js';
import translation from './languages.js';


export var forceStopGame = null;

export default class Tournament {
	constructor(scene, physicsWorld, camera, font, humanPlayersName, language) {
		this.scene = scene;
		this.physicsWorld = physicsWorld;
		this.camera = camera;
		this.realPlayersNb = humanPlayersName.length;
		this.game = new Game(scene, physicsWorld, camera, font, humanPlayersName.length, 0);
		forceStopGame = false;
		this.font = font;
		this.language = language;
		this.menu = new Menu(scene, camera, font, this.game, humanPlayersName, 0, language);
		this.winner = null;
	}

	showText({text, size=8, y=0}) {
		if (this.currentText == text)
			return;
		// delete previous text
		if (this.textMesh) {
			this.textMesh.traverse( function (child) {
				if (child.geometry)
					child.geometry.dispose();
			} );
			this.scene.remove(this.textMesh);
		}
		if (!text)
			return;
		// create new text
		this.currentText = text;
		this.textMesh = createText({font: this.font, message: text, size: size, sideColor: "#000000", fontColor: "#ffffff", shadow: true});
		this.textMesh.position.z = 8;
		this.textMesh.position.y = y;
		this.scene.add(this.textMesh);
	}

	copyPlayerAttributes(player, newPlayer) {
		// newPlayer.health = player.health;// to keep the health
		newPlayer.downKeyCode = player.downKeyCode;
		newPlayer.upKeyCode = player.upKeyCode;
		newPlayer.paddle.mesh.material = player.paddle.mesh.material; // ? clone?
	}

	createNewGame(excludePlayer) {
		this.showText({text: excludePlayer.name + translation['playerOut'][this.language], y:constants.FIELD_DIAMETER/2+4});
		var players = this.game.players.filter((player) => player != excludePlayer);
		this.realPlayersNb = players.length;
		this.game.delete()
		this.game = new Game(this.scene, this.physicsWorld, this.camera, this.font, players.length, 0, 5);
		for (var i = 0; i < players.length; i++) {
			var playerNb = i;
			if (players.length == 2 && i == 1)
				playerNb = 2;
			var player = this.game.createHumanPlayer(playerNb, players[i].name);
			this.copyPlayerAttributes(players[i], player);
			this.game.addPlayer(player);
		}

		this.game.createNewRound();
	}

	manageGoal() {
		var goalPlayer = this.game.getGoalPlayer();
		if (goalPlayer == null)
			return;
		if (goalPlayer.health > 0) {
			this.game.createNewRound();
			return;
		}
		// one player is dead
		if (this.game.playersNb == 2) {
			var winner = this.game.players.filter((player) => player.health > 0)[0];
			if (winner) {
				this.winner = winner;
				this.showText({text:winner.name + translation['winAndContinue'][this.language], size:5});
			}
			else
				this.showText({text: translation['lostAgainstNobody'][this.language], size:4});

			return
		}
		this.createNewGame(goalPlayer);
	}

	update(dt, keysdown, keysJustPressed) {
		if (this.menu.update(keysJustPressed) == true)
			return true;
		this.game.update(dt, keysdown);

		this.manageGoal();

		if (this.winner && keysdown.includes(13)) {
			return false;
		}
		if (forceStopGame) {
			// ? TODO free ?
			return false;
		}
		return true;
	}
}
