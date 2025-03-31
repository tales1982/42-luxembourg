import * as THREE from 'three';
import * as constants from './constants.js';


function getRandomPointAnnulus(radius1, radius2) {
	const r = Math.sqrt(radius1*radius1 + (radius2*radius2 - radius1*radius1) * Math.random());
	const theta = Math.random()*Math.PI*2;
	const x = r*Math.cos(theta);
	const y = r*Math.sin(theta);
	return [x, y];
}


class OrbitMovement {
	constructor(center, radius, speedX=THREE.MathUtils.randFloat(0.001, 0.009), speedY=THREE.MathUtils.randFloat(0.001, 0.009), speedZ=THREE.MathUtils.randFloat(0.0001, 0.001)) {
		this.center = center;
		this.radius = radius;
		this.speedX = speedX;
		this.speedY = speedY;
		this.speedZ = speedZ;
		this.angleX = Math.random() * Math.PI * 2; // random start angle
		this.angleY = Math.random() * Math.PI * 2; // random start angle
		this.angleZ = Math.random() * Math.PI * 2; // random start angle
	}

	getUpdatedPos() {
		this.angleX += this.speedX;
		this.angleY += this.speedY;
		this.angleZ += this.speedZ;

		const x = this.center.x + this.radius * Math.cos(this.angleX);
		const y = this.center.y + this.radius * Math.sin(this.angleY);
		const z = this.center.z //+ this.radius * Math.sin(this.angleZ);

		return new THREE.Vector3(x, y, z);
	}
}

class MovingSphere extends OrbitMovement {
	constructor(x, y, z) {
		super(new THREE.Vector3(x, y, z), 10);
		this.mesh = this.createSphereMesh(x, y, z);
		// this.growSpeed = THREE.MathUtils.randFloat(0.001, 0.01);
	}

	createSphereMesh(x, y, z) {
		const sphereRadius = THREE.MathUtils.randFloat(0.1, 1.2)
		const geometry = new THREE.SphereGeometry(sphereRadius, 12, 12);
		// const geometry = new THREE.TorusGeometry(sphereRadius, 1, 3);
		const material = new THREE.MeshBasicMaterial({ color: '#FFFFFF' });
		const mesh = new THREE.Mesh(geometry, material);
		mesh.position.set(x, y, z);
		return mesh;
	}

	update() {
		this.mesh.position.copy(this.getUpdatedPos());
		// this.mesh.scale.x = Math.sin(this.growSpeed)*2 + 2.1;
		// this.mesh.scale.y = Math.sin(this.growSpeed)*2 + 2.1;
		// this.mesh.scale.z = Math.sin(this.growSpeed)*2 + 2.1;
		// this.growSpeed += 0.01;
	}
}

class RotatingIcosahedro extends OrbitMovement {
	constructor(x, y, z) {
		super(new THREE.Vector3(x, y, z), 4);
		this.mesh = this.createTorusMesh(x, y, z);
		this.rotateSpeed = [THREE.MathUtils.randFloat(0.001, 0.001), THREE.MathUtils.randFloat(0.001, 0.001), THREE.MathUtils.randFloat(0.001, 0.001)];
	}

	createTorusMesh(x, y, z) {
		const radius = THREE.MathUtils.randFloat(6, 33)
		// const torusTube = THREE.MathUtils.randFloat(torusRadius-2, torusRadius-1)
		// const geometry = new THREE.TorusGeometry(torusRadius, torusTube, 12, 48);
		const geometry = new THREE.IcosahedronGeometry(radius);
		const colors = ['#F9F871', '#C2F988', '#8CF5A6', '#5AEEC4', '#5AEEC4']

		const material = new THREE.MeshBasicMaterial({ color: colors[Math.floor(Math.random()*colors.length)], wireframe: false, transparent: true, opacity: .8, });
		const mesh = new THREE.Mesh(geometry, material);
		mesh.position.set(x, y, z);
		return mesh;
	}

	rotate() {
		this.mesh.rotation.x += this.rotateSpeed[0];
		this.mesh.rotation.y += this.rotateSpeed[1];
		this.mesh.rotation.z += this.rotateSpeed[2];
	}

	update() {
		this.mesh.position.copy(this.getUpdatedPos());
		this.rotate();
	}

}

class MovingBox extends OrbitMovement {
	constructor(x, y, z) {
		super(new THREE.Vector3(x, y, z), 10);
		this.mesh = this.createBoxMesh(x, y, z);
		this.rotateSpeed = [THREE.MathUtils.randFloat(0.0001, 0.001), THREE.MathUtils.randFloat(0.0001, 0.001), THREE.MathUtils.randFloat(0.0001, 0.001)];
	}

	createBoxMesh(x, y, z) {
		const boxSize = THREE.MathUtils.randFloat(5, 12)
		const geometry = new THREE.BoxGeometry(1, boxSize, 1);
		const blue = new THREE.Color('#80d0d9');
		const yellow = new THREE.Color('#faed3b');
		const material = new THREE.MeshBasicMaterial({ color: Math.random() > 0.5 ? blue : yellow });

		const mesh = new THREE.Mesh(geometry, material);
		mesh.position.set(x, y, z);
		mesh.rotation.x = Math.random() * Math.PI;
		mesh.rotation.y = Math.random() * Math.PI;
		mesh.rotation.z = Math.random() * Math.PI;
		return mesh;
	}

	rotate() {
		this.mesh.rotation.x += this.rotateSpeed[0];
		this.mesh.rotation.y += this.rotateSpeed[1];
		this.mesh.rotation.z += this.rotateSpeed[2];
	}

	update() {
		this.mesh.position.copy(this.getUpdatedPos());
		this.rotate();
	}
}


class FallingBox {
	constructor(x, y) {
		this.minZ = -constants.FIELD_DIAMETER * 3; // will be teleported to the top when it reaches this point
		this.respawnZ = constants.FIELD_DIAMETER*2;
		const z = THREE.MathUtils.randFloat(this.minZ, this.respawnZ);
		this.mesh = this.createBoxMesh(x, y, z);
		this.speed = THREE.MathUtils.randFloat(0.2, 0.6); // or better with all same speed?

	}

	createBoxMesh(x, y, z) {
		const boxSize = THREE.MathUtils.randFloat(14, 33); // 10, 22
		const geometry = new THREE.BoxGeometry(1, boxSize, 1);
		const blue = new THREE.Color('#80d0d9');
		const yellow = new THREE.Color('#faed3b');
		const material = new THREE.MeshBasicMaterial({ color: Math.random() > 0.5 ? blue : yellow });

		const mesh = new THREE.Mesh(geometry, material);
		mesh.position.set(x, y, z);

		mesh.rotation.x = Math.PI/2; // make them vertically
		return mesh;
	}

	update() {
		this.mesh.position.z -= this.speed;
		if (this.mesh.position.z < this.minZ) {
			this.mesh.position.z = this.respawnZ;
		}
	}
}

export default class Background {
	constructor(scene) {
		this.scene = scene;
		this.stars = []

		if (Math.random() > 0.82) { // special background !
			this.stars.push(...this.createMovingObject(MovingBox, {number: 200, maxSpawnDistance: 250, spawnUnderField: true}));
		} else if (Math.random() > 0.94) { // special background !
			this.stars.push(...this.createMovingObject(RotatingIcosahedro, {number: 200, maxSpawnDistance: 400, spawnUnderField: true, safeZoneAroundFieldBorder: 100}));
		} else { // default background
			this.stars.push(...this.createMovingObject(MovingSphere, {number: 100, maxSpawnDistance: 200, spawnUnderField: true}));
			this.stars.push(...this.createMovingObject(FallingBox, {number: 100, maxSpawnDistance: 200, spawnUnderField: false}));
		}
	}

	delete() {
		this.stars.forEach(star => this.scene.remove(star.mesh));
	}

	createMovingObject(movingObjectClass, {number=100, maxSpawnDistance=200, safeZoneAroundFieldBorder=30, spawnUnderField=false}) {
		const objects = [];
		for (let i = 0; i < number; i++) {
			var minDistance = safeZoneAroundFieldBorder + constants.FIELD_DIAMETER/2;
			const z = THREE.MathUtils.randFloatSpread(maxSpawnDistance * 2);
			if (spawnUnderField && z < -safeZoneAroundFieldBorder)
				minDistance = 0; // will be able to put stars below the field
			const [x, y] = getRandomPointAnnulus(minDistance, maxSpawnDistance);
			const object = new movingObjectClass(x, y, z);
			objects.push(object);
			this.scene.add(object.mesh);
		}
		return objects;
	}

	update() {
		this.stars.forEach(star => star.update());
	}
}

