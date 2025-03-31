import * as THREE from 'three';

import * as maps from './maps/maps.js';
import * as particles from './particles.js';
import * as constants from './constants.js';
import Cube from './Cube.js';
import {LightsDownPowerup} from './powerups.js';


export const presets = [
	{
		color: '#ff0000',
		upKey: 87,
		leftKey: 65,
		downKey: 83,
		rightKey: 68,
		upKeyText: 'W',
		leftKeyText: 'A',
		downKeyText: 'S',
		rightKeyText: 'D'
	},
	{
		color: '#00ff00',
		upKey: 38,
		leftKey: 37,
		downKey: 40,
		rightKey: 39,
		upKeyText: 'UP',
		leftKeyText: 'LEFT',
		downKeyText: 'RIGHT',
		rightKeyText: 'DOWN'
	},
	{
		color: '#0000ff',
		upKey: 73,
		leftKey: 74,
		downKey: 75,
		rightKey: 76,
		upKeyText: 'I',
		leftKeyText: 'J',
		downKeyText: 'K',
		rightKeyText: 'L'
	},
	{
		color: '#ff00ff',
		upKey: 84,
		leftKey: 70,
		downKey: 71,
		rightKey: 72,
		upKeyText: 'T',
		leftKeyText: 'F',
		downKeyText: 'G',
		rightKeyText: 'H'
	}
]

export default class Player extends Cube {
	constructor({scene, x=0, y=0, depth=1, playerNb=0, preset=presets[playerNb], particlesSystem}) {
		super({scene: scene, x: x, y: y, depth: depth, color: preset.color});
		this.scene = scene;
		this.depth = depth;
		this.particlesSystem = particlesSystem;
		this.playerNb = playerNb;
		// position and movement
		this.keys = {
			up: preset.upKey,
			left: preset.leftKey,
			down: preset.downKey,
			right: preset.rightKey
		};
		this.position = new THREE.Vector2(x, y);
		this.movingDirection = new THREE.Vector2(0, 0);
		this.canMove = true;
		this.meshStartMovingVelocity = -8; // the mesh moving velocity will start at this amount
		this.meshCurrentMovingVelocity = this.meshStartMovingVelocity;
		this.meshMovingAcceleration = 15; // the mesh moving velocity will increase by this amount every frame
		// light
		this.spotLightIntensity = 155;
		this.spotLight = this.createSpotlight(this.spotLightIntensity);

		this.hasWin = false;
		// powerups
		//	 slow
		this.slowDuration = 0;
		this.slowedMeshMovingVelocity = 8;
		//	 lights down
		this.spotLightOffDuration = 0;
		//	 dazed effect
		this.dazedDuration = 0;
		this.dazedKeys = {up: this.keys.down, down: this.keys.up, left: this.keys.right, right: this.keys.left};
		this.defaultKeys = {up: this.keys.up, down: this.keys.down, left: this.keys.left, right: this.keys.right};
	}

	delete() {
		this.scene.remove(this.mesh);
		this.mesh.geometry.dispose();
		this.mesh.material.dispose()
		this.scene.remove(this.spotLight);
		this.scene.remove(this.spotLight.target);
		this.spotLight.dispose();
	}

	createSpotlight(intensity) {
		const color = this.mesh.material.color;
		var light = new THREE.SpotLight(color, intensity, 16, Math.PI/4, 0.5, 2);
		light.position.set(0, 0, 8);
		this.mesh.add(light);
		this.mesh.add(light.target);
		// helper
		if (constants.DEBUG)
			this.mesh.add(new THREE.SpotLightHelper(light));
		return light;
	}

	moveRight() {
		this.movingDirection.x = 1;
		this.canMove = false;
	}
	moveLeft() {
		this.movingDirection.x = -1;
		this.canMove = false;
	}
	moveUp() {
		this.movingDirection.y = 1;
		this.canMove = false;
	}
	moveDown() {
		this.movingDirection.y = -1;
		this.canMove = false;
	}

	setMovement(keysJustPressed) {
		if (this.canMove) {
			if (keysJustPressed.includes(this.keys.up)) {
				this.moveUp();
			}
			else if (keysJustPressed.includes(this.keys.down)) {
				this.moveDown();
			}
			else if (keysJustPressed.includes(this.keys.left)) {
				this.moveLeft();
			}
			else if (keysJustPressed.includes(this.keys.right)) {
				this.moveRight();
			}
		}
	}

	activatePowerup(powerups) {
		for (let powerup of powerups) {
			if (this.position.x == powerup.position.x && this.position.y == powerup.position.y) {
				powerup.activateByPlayer(this);
			}
		}
	}

	updateMovement(dt, mapData, keysJustPressed, powerups, registerMovements=true) {
		if (registerMovements)
			this.setMovement(keysJustPressed);

		if (this.movingDirection.x != 0 || this.movingDirection.y != 0)
		{
			// move the player until it hits an obstacle
			while(!this.hasWin && !maps.OBSTACLES.includes(mapData.getCell(this.position.x + this.movingDirection.x, this.position.y + this.movingDirection.y))) {
					this.position.x += this.movingDirection.x;
					this.position.y += this.movingDirection.y;
					this.checkVictory(mapData);
					this.activatePowerup(powerups)
			}
			this.movingDirection.x = 0;
			this.movingDirection.y = 0;
		}
		this.canMove = this.moveMeshToPosition(dt);
		if (this.canMove)
			this.meshCurrentMovingVelocity = this.meshStartMovingVelocity;
	}

	moveMeshToPosition(dt) {
		var movingDirection = new THREE.Vector2(this.position.x - this.mesh.position.x, this.position.y - this.mesh.position.y).normalize();
		if (this.position.x != this.mesh.position.x || this.position.y != this.mesh.position.y) {
			this.mesh.position.x += Math.sign(this.position.x - this.mesh.position.x) * this.meshCurrentMovingVelocity * dt;
			this.mesh.position.y += Math.sign(this.position.y - this.mesh.position.y) * this.meshCurrentMovingVelocity * dt;
			this.meshCurrentMovingVelocity += this.meshMovingAcceleration * dt*10;

			// check if the mesh has reached (or is behind) the position
			var newMovingDirection = new THREE.Vector2(this.position.x - this.mesh.position.x, this.position.y - this.mesh.position.y).normalize();
			if (Math.sign(movingDirection.x) != Math.sign(newMovingDirection.x) || Math.sign(movingDirection.y) != Math.sign(newMovingDirection.y))
				this.mesh.position.copy(new THREE.Vector3(this.position.x, this.position.y, 0));
			return false;
		}
		return true;
	}

	checkVictory(mapData) {
		if (mapData.isOutOfBounds(this.position.x, this.position.y)) {
			this.hasWin = true;
		}
	}

	updatePowerups(dt) {
		// slow effect
		if (this.slowDuration > 0)
		{
			// particles
			if (this.particlesSystem.triggerPulse(dt, this.canMove ? 4 : 22 ))
				this.particlesSystem.addParticle(this.mesh.position.x, this.mesh.position.y, this.mesh.position.z+1.5, particles.SnowParticle);
			if (this.meshCurrentMovingVelocity >= 0)
				this.meshCurrentMovingVelocity = this.slowedMeshMovingVelocity;
			this.slowDuration -= dt;
		}
		// lights down effect
		if (this.spotLightOffDuration > 0)
		{
			this.spotLight.intensity = 5;
			this.spotLightOffDuration -= dt;
			if (this.spotLightOffDuration <= 0) {
				this.spotLight.intensity = this.spotLightIntensity;
			// activate the big lights
			LightsDownPowerup.activateSceneLights(this.scene);
			this.spotLightOffDuration = -1;
			}
		}
		// daze effect
		if (this.dazedDuration > 0)
		{
			if (this.particlesSystem.triggerPulse(dt, this.canMove ? 4 : 10))
				this.particlesSystem.addParticle(this.mesh.position.x, this.mesh.position.y, this.mesh.position.z+1, particles.DazedParticle);
			this.keys = this.dazedKeys;
			this.dazedDuration -= dt;
			if (this.dazedDuration <= 0) {
				this.keys = this.defaultKeys;
			}
		}
	}

	winAnimation(dt) {
		// jumps
		if (!this.winTimer)
				this.winTimer = 0;
			this.winTimer += dt;
		this.mesh.position.z = Math.abs(Math.sin(this.winTimer*3))*1.5;
		// conffetti
		if (this.particlesSystem.triggerPulse(dt, this.canMove ? 20 : 200))
			this.particlesSystem.addParticle(this.mesh.position.x, this.mesh.position.y, 10, particles.ConfettiParticle);
		LightsDownPowerup.activateSceneLights(this.scene);

	}

	do360(dt, speed=1, minHeight=1) {
		if (this.mesh.position.z >= minHeight)
			this.mesh.rotation.z += speed*dt * Math.PI*2;
	}

	deceptionAnimation(dt, speed=.2) {
		if (!this.deceptionTimer)
			this.deceptionTimer = Math.random() * Math.PI * 2;
		this.deceptionTimer += dt;

		this.mesh.rotation.z = Math.sin(this.deceptionTimer*speed*Math.PI*2)/4;
	}

	tpToPosition(x, y) {
		this.position.set(x, y);
		this.mesh.position.set(x, y, this.mesh.position.z);
	}

	update(dt, keysJustPressed, mapData, powerups, canMove=true) {
		this.updateMovement(dt, mapData, keysJustPressed, powerups, canMove);
		this.updatePowerups(dt);
		if (this.hasWin) {
			this.winAnimation(dt)
		}
	}

}
