import * as THREE from 'three';

import * as constants from './constants.js';
import * as maps from './maps/maps.js';
import * as powerups from './powerups.js';
import Cube from './Cube.js';
import Player from './Player.js';
import MapData from './MapData.js';
import ParticlesSystem from './particles.js';


export default class Game {
	constructor(scene, camera, map, playersNb, isPowerupsOn) {
		this.scene = scene;
		this.camera = camera;
		this.mapData = new MapData(map.array);
		this.clock = new THREE.Clock();
		this.particlesSystem = new ParticlesSystem(scene);
		[this.walls, this.players, this.powerups] = this.loadMap(this.mapData, playersNb);

		this.activateSpawnAnimation();
		this.createPlane(map.backgroundColor)
		// powerups
		this.isPowerupsOn = isPowerupsOn;
		this.spawnPowerupsFrequency = 10; // seconds
		this.spawnPowerupsTimer = 0;
		this.allPowerups = [
			powerups.SlowPowerup,
			powerups.SlowPowerup,
			powerups.SlowPowerup, // to have more chance to spawn it
			powerups.LightsDownPowerup,
			powerups.DazedPowerup,
			powerups.DazedPowerup
		];
		this.defineCameraStartPos();
		this.winner = null; // the player who has won
	}

	delete() {
		for (let wall of this.walls) {
			wall.delete();
		}
		for (let player of this.players) {
			player.delete();
		}
		for (let powerup of this.powerups) {
			powerup.delete();
		}
		this.particlesSystem.delete();
		this.planeMesh.geometry.dispose();
		this.planeMesh.material.dispose();
		this.scene.remove(this.planeMesh);
	}

	defineCameraStartPos() {
		var mapHeight = this.mapData.getHeight();
		var mapWidth = this.mapData.getWidth();
		this.camera.rotation.y = 0;
		this.camera.rotation.z = 0;
		this.camera.rotation.x = 0;
		// this.camera.position.x = mapWidth/2;
		// this.camera.position.y = this.showSpawnAnimation ? -mapHeight/4 : mapHeight/2; //mapHeight/2;
		var maxMapSize = Math.max(mapHeight, mapWidth);
		this.cameraZTarget = Math.tan(constants.fov * Math.PI / 180/2) * maxMapSize/2;
		// this.camera.position.z = this.cameraZTarget;
	}

	createPlane(color=0xffffff) {
		const geometry = new THREE.PlaneGeometry(250, 150);
		const material = new THREE.MeshStandardMaterial({color: color, side: THREE.DoubleSide});
		const plane = new THREE.Mesh(geometry, material);
		plane.position.z = -0.5;
		plane.position.x += 25;
		plane.position.y += 25;

		plane.receiveShadow = true;
		this.scene.add(plane);
		this.planeMesh = plane;
	}

	activateSpawnAnimation(duration=4) {
		this.spawnAnimationFallHeight = 8;
		for (let i = 0; i < this.walls.length; i++) {
			let wall = this.walls[i];
			wall.mesh.position.z = this.spawnAnimationFallHeight;
			wall.mesh.material.opacity = 0;

		}
		this.showSpawnAnimation = true;
		this.currentSpawnAnimationTime = 0;
		this.spawnAnimationDuration = duration;
		// put all players invisible
		for (let player of this.players) {
			player.mesh.visible = false;
		}
	}

	desactivateSpawnAnimation() {
		this.showSpawnAnimation = false;
		for (let player of this.players) {
			player.mesh.visible = true;
		}
	}

	spawnAnimation(dt) {
		if (!this.showSpawnAnimation)
			return false;
		this.haveAllWallsFallen = true;
		// make walls fall
		for (let i = 0; i < this.walls.length; i++) {
			if (this.currentSpawnAnimationTime < i/this.walls.length*this.spawnAnimationDuration)
				continue;
			let wall = this.walls[i];
			wall.mesh.position.z -= 0.15;
			if (wall.mesh.position.z < 0)
				wall.mesh.position.z = 0;
			wall.mesh.material.opacity = 1 - wall.mesh.position.z/this.spawnAnimationFallHeight;

			if (wall.mesh.position.z > 0)
				this.haveAllWallsFallen = false;
		}
		// check if the spawn animation is over
		if (this.currentSpawnAnimationTime > this.spawnAnimationDuration) {
			if (this.haveAllWallsFallen)
				this.desactivateSpawnAnimation();
		} else { // make walls appear
			this.currentSpawnAnimationTime += dt;
			for (let i = 0; i < this.walls.length; i++) {
				let wall = this.walls[i];
				wall.mesh.visible = this.currentSpawnAnimationTime > i/this.walls.length*this.spawnAnimationDuration;
				wall.mesh.material.transparent = true;
			}
		}
		return true;
	}

	loadMap(mapData, playersNb) {
		const walls = [];
		const players = [];
		const _powerups = [];
		var mapHeight = mapData.getHeight();
		var mapWidth = mapData.getWidth();
		for (let y = 0; y < mapHeight; y++) {
			for (let x = 0; x < mapWidth; x++) {
				var cell = mapData.getCell(x, y);
				var color = null;
				if (cell === maps.RED)
					color = new THREE.Color('#c0392b');
				else if (cell === maps.ORANGE)
					color = new THREE.Color('#e67e22');
				else if (cell === maps.YELLOW)
					color = new THREE.Color('#f1c40f');
				else if (cell === maps.GREEN)
					color = new THREE.Color('#2ecc71');
				else if (cell === maps.LIGHTBLUE)
					color = new THREE.Color('#3ca4ff');
				else if (cell === maps.DARKBLUE)
					color = new THREE.Color('#2980b9');
				else if (cell === maps.WHITE)
					color = new THREE.Color('#ffffff');
				else if (cell === maps.GRAY)
					color = new THREE.Color('#7f8c8d');
				else if (cell === maps.BLACK)
					color = new THREE.Color(0, 0, 0);

				if (color) {
					const wall = new Cube({scene: this.scene, x: x, y: y, depth:1.1, color: color});
					walls.push(wall);
				}
				else if (cell === maps.PLAYER) {
					for (let i = 0; i < playersNb; i++) {
						const player = new Player({scene: this.scene, x: x, y: y, playerNb: i, particlesSystem: this.particlesSystem});
						players.push(player);
					}
				}
				// else if (cell === maps.POWERUP_SLOW) {
				// 	_powerups.push(new powerups.SlowPowerup({scene: this.scene, x: x, y: y, players: players, particlesSystem: this.particlesSystem}));
				// } else if (cell === maps.POWERUP_LIGHTSDOWN) {
				// 	_powerups.push(new powerups.LightsDownPowerup({scene: this.scene, x: x, y: y, players: players, particlesSystem: this.particlesSystem}));
				// } else if (cell === maps.POWERUP_DAZED) {
				// 	_powerups.push(new powerups.DazedPowerup({scene: this.scene, x: x, y: y, players: players, particlesSystem: this.particlesSystem}));
				// }
			}
		}
		// for (let y = 0; y < mapArray.length; y++) {
		// 	for (let x = 0; x < mapArray[y].length; x++) {
		// 		if (mapArray[y][x] === maps.WALL) {
		// 			const wall = new Cube({scene: this.scene, x: x, y: y, color: 0x00c0c0+x*20+y*20});
		// 			walls.push(wall);
		// 		}
		// 		else if (mapArray[y][x] === maps.PLAYER) {
		// 			const player = new Player({scene: this.scene, x: x, y: y});
		// 			players.push(player);
		// 		}
		// 	}
		// }
		return [walls, players, _powerups];
	}

	/** Stack players on top of each other when they are on the same position */
	stackPlayers(dt) {
		// make the gravity
		for (let player of this.players) {
			if (player.mesh.position.z > 0) {
				player.mesh.position.z -= 6 * dt;
				if (player.mesh.position.z < 0)
					player.mesh.position.z = 0;
			}
		}
		for (let i=0; i<this.players.length; i++)
		{
			let player1 = this.players[i];
			for (let j=i+1; j<this.players.length; j++) {
				let player2 = this.players[j];
				if (player1.mesh.position.x == player2.mesh.position.x && player1.mesh.position.y == player2.mesh.position.y) {
					if (player2.mesh.position.z < player1.mesh.position.z+player1.depth) {
						player2.mesh.position.z =  Math.min(player1.mesh.position.z+player1.depth, player2.mesh.position.z + 18 * dt);
					}
				}
			}
		}
	}

	spawnPowerup() {
		if (!this.isPowerupsOn)
			return;
		const pos = this.mapData.getRandomEmptyCell();
		if (pos !== null) {
			const PowerupClass = this.allPowerups[Math.floor(Math.random() * this.allPowerups.length)];
			this.powerups.push(new PowerupClass({scene: this.scene, x: pos.x, y: pos.y, players: this.players, particlesSystem: this.particlesSystem}));
		}
	}

	updatePowerups(dt) {
		// update
		for (let powerup of this.powerups) {
			powerup.update(dt);
			if (powerup.hasBeenActivated) {
				powerup.delete();
				this.powerups = this.powerups.filter(p => p != powerup);
			}
		}
		// create
		this.spawnPowerupsTimer += dt;
		if (this.spawnPowerupsTimer > this.spawnPowerupsFrequency) {
			this.spawnPowerupsTimer = 0;
			this.spawnPowerup();
		}

	}

	updateCamera(dt, {x=null, y=null, moveSpeed=.5, maxDistFromCenter=2}) {
		if (constants.DEBUG)
		return;
	// move the camera to Z target
	this.camera.position.z += (this.cameraZTarget - this.camera.position.z) * dt * moveSpeed/2;
	var mapCenterX = this.mapData.getWidth()/2;
	var mapCenterY = this.mapData.getHeight()/2;
	if (!x || !y) {
		// average position of the players
		var x = 0;
		var y = 0;
		for (let player of this.players) {
			x += player.position.x;
			y += player.position.y;
		}
		x /= this.players.length;
		y /= this.players.length;
	}
	// limit the camera to the map
	x = Math.min(Math.max(x, mapCenterX - maxDistFromCenter), mapCenterX + maxDistFromCenter);
	y = Math.min(Math.max(y, mapCenterY - maxDistFromCenter), mapCenterY + maxDistFromCenter);

	// slowly move the camera to the x, y
	this.camera.position.x += (x - this.camera.position.x) * dt * moveSpeed;
	this.camera.position.y += (y - this.camera.position.y) * dt * moveSpeed;
}

update(keysJustPressed) {
	var dt = this.clock.getDelta();
	this.particlesSystem.update(dt);
	if (!this.spawnAnimation(dt)) {
		for (let player of this.players) {
			player.update(dt, keysJustPressed, this.mapData, this.powerups, this.winner==null);
			if (player.hasWin) {
				this.winner = player;
				this.updateCamera(dt, {x: player.position.x, y: player.position.y, maxDistFromCenter: 8.5, moveSpeed: 2});
			}
		}
	}
		this.stackPlayers(dt);

		this.updatePowerups(dt);
		this.updateCamera(dt, {maxDistFromCenter: 1.5, moveSpeed: .6});


	}
}
