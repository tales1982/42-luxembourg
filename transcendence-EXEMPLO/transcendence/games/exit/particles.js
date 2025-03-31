import * as THREE from 'three';


export default class ParticlesSystem {
	constructor(scene) {
		this.scene = scene;
		this._particles = [];
	}

	delete() {
		for (let particle of this._particles) {
			particle.delete();
		}
	}

	/** Returns true frequency times per seconds in average*/
	triggerPulse(dt, frequency) {
		// can not return true more than once per frame
		return Math.random() < frequency*dt;
	}

	/** Returns true frequency times per seconds in average*/
	static triggerPulse(dt, frequency) {
		return Math.random() < frequency*dt;
	}

	addParticle(x, y, z, type) {
		this._particles.push(new type({scene: this.scene, x: x, y: y, z: z}));
	}

	update(dt) {
		for (var particle of this._particles) {
			if (particle.shouldRemove()) {
				particle.delete();
				this._particles.splice(this._particles.indexOf(particle), 1);
				continue;
			}
			particle.update(dt);
		}
	}
}


class Particle {
	constructor({scene, x, y, z}) {
		this.scene = scene;
		this.position = new THREE.Vector3(x, y, z);
	}
	shouldRemove() {
		throw new Error('Not implemented');
	}

	delete() {
		this.mesh.geometry.dispose();
		this.mesh.material.dispose();
		this.scene.remove(this.mesh);
		delete this.mesh;
	}

	update(dt) {
		throw new Error('Not implemented');
	}
}


export class SnowParticle extends Particle {

	constructor({scene, x, y, z}) {
		var randomOffsetX = Math.random() - 0.5;
		var randomOffsetY = Math.random() - 0.5;
		super({scene: scene, x: x+randomOffsetX, y: y+randomOffsetY, z: z});
		this.velocity = new THREE.Vector3(0, 0, -0.3);
		var min = 0.04,
        	max = 0.1,
        	radius = Math.random() * (max - min) + min;
		this.mesh = new THREE.Mesh(new THREE.SphereGeometry(radius), new THREE.MeshBasicMaterial({color: '#ffffff'}));
		this.mesh.position.copy(this.position);
		this.mesh.castShadow = true;
		scene.add(this.mesh);
	}

	shouldRemove() {
		return this.position.z <= -0.5;
	}

	move(dt) {
		this.position.add(this.velocity.clone().multiplyScalar(dt));
		var c = this.position.clone();
		c.x += Math.sin(this.position.z*4) * 0.1;
		c.y += Math.cos(this.position.z*5) * 0.1;
		this.mesh.position.copy(c);

	}

	update(dt) {
		this.move(dt);
	}

}


export class LightAbsorbedParticle extends Particle {

	static mesh = new THREE.Mesh(new THREE.SphereGeometry(0.1, 8, 4), new THREE.MeshBasicMaterial({color: '#fff376'}));
	constructor({scene, x, y, z}) {
		var min = -0.4,
        	max = 0.4;
        x += Math.random() * (max - min) + min;
		y += Math.random() * (max - min) + min;
		z += Math.random() * (max - min) + min;

		super({scene: scene, x: x, y: y, z: z});
		this.mesh = LightAbsorbedParticle.mesh.clone();
		this.mesh.position.copy(this.position);
		scene.add(this.mesh);
		this.maxBlackDots = 40;
		this.currentBlackDots = 0;
	}

	shouldRemove() {
		return this.mesh.scale.x <= 0.1;
	}

	decreaseRadius(dt) {
		this.mesh.scale.x -= dt;
		this.mesh.scale.y -= dt;
		this.mesh.scale.z -= dt;
	}

	spawnBlackDots(dt){
		if (this.currentBlackDots >= this.maxBlackDots)
			return;
		if (ParticlesSystem.triggerPulse(dt, 20)) {
			this.currentBlackDots += 1;
			const radius = Math.random() * 0.1 + 0.01;
			var black = new THREE.Mesh(new THREE.SphereGeometry(radius, 8, 4), new THREE.MeshBasicMaterial({color: '#000000'}));
			black.position.x += Math.random() - 0.5;
			black.position.y += Math.random() - 0.5;
			black.position.z += Math.random() - 0.5;
			this.mesh.add(black);
		}

	}

	update(dt) {
		this.decreaseRadius(dt);
		this.spawnBlackDots(dt);

	}
}


export class DazedParticle extends Particle {


	static textureLoader = new THREE.TextureLoader();
	static starMap = DazedParticle.textureLoader.load('exit/assets/star.png');
	static planetMap = DazedParticle.textureLoader.load('exit/assets/planet.png');
	static exclamationMap = DazedParticle.textureLoader.load('exit/assets/exclamation.png');
	static interogationMap = DazedParticle.textureLoader.load('exit/assets/interogation.png');
	static spriteMaps = [
		DazedParticle.starMap, DazedParticle.starMap, DazedParticle.starMap, DazedParticle.starMap,
		DazedParticle.planetMap,
		DazedParticle.exclamationMap,
		DazedParticle.interogationMap
	];

	constructor({scene, x, y, z, orbitRadius=0.7, orbitSpeed=Math.PI*2/1.5, lifeTime=2, startScale=0.5}) {
		super({scene: scene, x: x, y: y, z: z});
		this.orbitRadius = orbitRadius;
		this.orbitSpeed = orbitSpeed; // in radians per second
		this.time = 0;
		this.lifeTime = lifeTime; // in seconds
		this.startScale = startScale;
		this.angleOffset = Math.random() * Math.PI * 2;

		const map = DazedParticle.spriteMaps[Math.floor(Math.random()*DazedParticle.spriteMaps.length)];
		const material = new THREE.SpriteMaterial( { map: map } );

		this.sprite = new THREE.Sprite( material );
		this.sprite.scale.set(this.startScale, this.startScale, 0);
		this.sprite.position.z = this.position.z;
		this.move(0); // to set the position of the sprite
		scene.add( this.sprite );
		this.mesh = this.sprite;

	}

	shouldRemove() {
		return this.time >= this.lifeTime;
	}

	scaleDown() {
		var completion = this.time/this.lifeTime;
		this.sprite.scale.set(this.startScale*(1-completion)+0.1, this.startScale*(1-completion)+0.1, 0);
	}

	move(dt) {
		this.time += dt;
		this.sprite.position.x = Math.sin(this.time * this.orbitSpeed+this.angleOffset) * this.orbitRadius;
		this.sprite.position.y = Math.cos(this.time * this.orbitSpeed+this.angleOffset) * this.orbitRadius;
		this.sprite.position.x += this.position.x;
		this.sprite.position.y += this.position.y;

	}

	update(dt) {
		this.move(dt);
		this.scaleDown()
	}
}


export class ConfettiParticle extends Particle {
	constructor({scene, x, y, z}) {
		const geometry = new THREE.SphereGeometry(THREE.MathUtils.randFloat(0.07, 0.11), 8, 4)
		super({scene: scene, x: x, y: y, z: z});
		this.velocity = new THREE.Vector3(THREE.MathUtils.randFloat(-0.9, 0.9), THREE.MathUtils.randFloat(-0.9, 0.9), THREE.MathUtils.randFloat(0, 0));
		this.gravity = new THREE.Vector3(0, 0, THREE.MathUtils.randFloat(-2, -1));
		const color = THREE.MathUtils.randInt(0, 0xffffff)
		this.mesh = new THREE.Mesh(geometry, new THREE.MeshBasicMaterial({color: color}));
		this.mesh.position.copy(this.position);
		scene.add(this.mesh);

	}

	shouldRemove() {
		return this.mesh.scale.z <= 0.1;
	}

	scaleDown(dt) {
		const speed = 0.3;
		this.mesh.scale.x -= dt * speed;
		this.mesh.scale.y -= dt * speed;
		this.mesh.scale.z -= dt * speed;
	}

	move(dt) {
		this.position.add(this.velocity.clone().multiplyScalar(dt));
		this.mesh.position.copy(this.position);
		this.velocity.add(this.gravity.clone().multiplyScalar(dt));
		if (this.position.z < 0) {
			this.position.z = 0;
			this.velocity = new THREE.Vector3(0, 0, 0);
			return false;
		}
		return true;
	}

	update(dt) {
		if (!this.move(dt))
			this.scaleDown(dt)
	}
}
