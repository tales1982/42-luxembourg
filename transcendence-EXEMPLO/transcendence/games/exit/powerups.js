import * as THREE from 'three';

import * as particles from './particles.js';
import Cube from './Cube.js';
import * as constants from './constants.js';

class Powerup extends Cube {
	constructor({scene, x, y, color}) {
		super({scene: scene, x: x, y: y, z: 0, width: 0.4, depth: 0.4, color: color});
		this.scene = scene;
		this.position = new THREE.Vector2(x, y);
		this.hasBeenActivated = false;
		// to make them fall
		this.mesh.position.z = 10;
		this.fallSpeed = 20;
		this.rotateSpeed = 1;
	}

	fall(dt) {
		if (this.mesh.position.z > 0) {
			this.mesh.position.z = Math.max(0, this.mesh.position.z - this.fallSpeed * dt);
		}
	}

	update(dt) {
		this.mesh.rotation.x += dt * this.rotateSpeed;
		this.mesh.rotation.y += dt * this.rotateSpeed;
		this.fall(dt);

	}

	activateByPlayer(player) {
		throw new Error('Not implemented');
	}

	delete() {
		this.scene.remove(this.mesh);
		this.mesh.geometry.dispose();
		this.mesh.material.dispose();
	}
}

export class SlowPowerup extends Powerup {
	constructor({scene, x, y, players, particlesSystem}) {
		super({scene: scene, x: x, y: y, color: 0x55aaff});
		this.players = players;
		this.particlesSystem = particlesSystem;
	}

	activateByPlayer(player) {
		this.hasBeenActivated = true;
		for (let p of this.players) {
			if (p == player)
				continue;
			p.slowDuration = 10;
		}
	}

	update(dt) {
		if (this.particlesSystem.triggerPulse(dt, 3))
			this.particlesSystem.addParticle(this.position.x, this.position.y, 1.5, particles.SnowParticle);
		super.update(dt);
	}
}

export class LightsDownPowerup extends Powerup {
	constructor({scene, x, y, players, particlesSystem}) {
		super({scene: scene, x: x, y: y, color: 0x000000});
		this.players = players;
		this.particlesSystem = particlesSystem;
	}

	static desactivateSceneLights(scene, minDirectionalLightIntensity, minAmbientLightIntensity) {
		for (let object of scene.children) {
			if (object.type == 'DirectionalLight') {
				object.intensity = minDirectionalLightIntensity;
			} else if (object.type == 'AmbientLight') {
				object.intensity = minAmbientLightIntensity;
			}
		}
	}

	static activateSceneLights(scene) {
		for (let object of scene.children) {
			if (object.type == 'DirectionalLight') {
				object.intensity = constants.directionalLightIntensity;
			} else if (object.type == 'AmbientLight') {
				object.intensity = constants.ambientLightIntensity;
			}
		}
	}

	activateByPlayer(player) {
		this.hasBeenActivated = true;
		for (let p of this.players) {
			if (p == player)
				continue;
			p.spotLightOffDuration = 8;

		}
		LightsDownPowerup.desactivateSceneLights(this.scene, 0, 0.003);
	}

	update(dt) {
		if (this.particlesSystem.triggerPulse(dt, 3))
			this.particlesSystem.addParticle(this.position.x, this.position.y, 0.5, particles.LightAbsorbedParticle);
		super.update(dt);
	}
}

export class DazedPowerup extends Powerup {
	constructor({scene, x, y, players, particlesSystem}) {
		super({scene: scene, x: x, y: y, color: 0xffb000});
		this.players = players;
		this.particlesSystem = particlesSystem;
	}

	activateByPlayer(player) {
		this.hasBeenActivated = true;
		for (let p of this.players) {
			if (p == player)
				continue;
			p.dazedDuration = 10;
		}
	}

	update(dt) {
		if (this.particlesSystem.triggerPulse(dt, 4))
			this.particlesSystem.addParticle(this.position.x, this.position.y, 1, particles.DazedParticle);
		super.update(dt);
	}
}
