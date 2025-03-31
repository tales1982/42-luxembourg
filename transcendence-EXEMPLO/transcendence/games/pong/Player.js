import * as THREE from 'three';
import * as CANNON from 'cannon-es';
import Paddle from './Paddle.js';
import { GLTFLoader } from 'three/examples/jsm/loaders/GLTFLoader.js';


export default class Player {
	constructor(scene, physicsWorld, playerNb, startPos, endPos, fieldEdgeDiameter, playersNb) {
		this.scene = scene;
		this.physicsWorld = physicsWorld;
		this.playerNb = playerNb;
		this.startPos = startPos;
		this.endPos = endPos;

		this.axeAngle = 2*Math.PI/(playersNb*2) +  2*Math.PI/playersNb*(playerNb);

		this.paddle = new Paddle(scene, physicsWorld, startPos, endPos, this.axeAngle, fieldEdgeDiameter);

		this.isBallInGoal = {a: false}; // ! TODO find a better way to do this (pass by reference)
		this.createGoalHitBox(scene, physicsWorld, startPos, endPos, fieldEdgeDiameter, this.isBallInGoal);

		this.health = 3;
		this.createHealthMeshes();
	}

	delete() {
		this.physicsWorld.removeBody(this.goalHitboxBody);
		if (this.closedGoalBody)
			this.physicsWorld.removeBody(this.closedGoalBody);
		this.paddle.delete();
	}

	createHealthMeshes() {
		this.healthMeshes = [];
		const loader = new GLTFLoader();
		// TODO make the heart a static variable
		loader.load("pong/assets/models/Heart.glb", (gltf) => {
			const model = gltf.scene;
			// get the paddle size
			const paddleSize = this.paddle.mesh.geometry.parameters.height;
			model.scale.set(3.8, 3.8, 3.8);
			model.rotation.set(0, 0, -Math.PI/2);
			// make the model more bright
			model.traverse((child) => {
				if (child.isMesh) {
					child.material.color.setHex(0xff5511);
				}
			});
			// create the health meshes
			for (var i = 0; i < this.health; i++) {
				var modelInstance = model.clone();
				modelInstance.position.set(0.4, -paddleSize/2+paddleSize/(this.health+1)*(i+1), 1.5);
				this.healthMeshes.push(modelInstance);
				this.paddle.mesh.add(modelInstance);
			}
		});
	}

	createClosedGoalBody() {
		var goalLength = this.startPos.distanceTo(this.endPos);
		var dX = this.endPos.x - this.startPos.x;
		var dY = this.endPos.y - this.startPos.y;
		var width = this.paddle.mesh.geometry.parameters.width
		var depth = this.paddle.mesh.geometry.parameters.depth;
		var centerPos = new THREE.Vector3(this.startPos.x + dX/2, this.startPos.y + dY/2, depth/2);

		this.closedGoalBody = new CANNON.Body({ // Todo rename to make it more explicit ?
			mass: 0,
			shape: new CANNON.Box(new CANNON.Vec3(width/2, goalLength/2, depth/2)),
			position: centerPos,
			material: new CANNON.Material({ friction: 0, restitution: 1 }),
		});
		this.closedGoalBody.quaternion.setFromAxisAngle(new CANNON.Vec3(0, 0, 1), this.axeAngle);
		this.closedGoalBody.collisionResponse = true;
		// this.closedGoalHitboxBody.isTrigger = true;
		this.physicsWorld.addBody(this.closedGoalBody);
	}

	closeGoal(dt, instant=false) {
		if (!this.closedGoalBody)
			this.createClosedGoalBody();
		// move the paddle to the center
		this.paddle.mesh.position.copy(this.paddle.centerPos);
		// increase the size of the paddle
		if (instant) {
			this.paddle.mesh.scale.set(1, 1 / this.paddle.percentLengthSize, 1);
		} else if (this.paddle.mesh.scale.y < 1 / this.paddle.percentLengthSize) {
			this.paddle.scale(4*dt)
		}
	}

	createGoalHitBox(scene, physicsWorld, startPos, endPos, fieldEdgeDiameter, isBallInGoal) {
		var goalLength = startPos.distanceTo(endPos);
		var dX = endPos.x - startPos.x;
		var dY = endPos.y - startPos.y;
		var centerPos = new THREE.Vector3(startPos.x + dX/2, startPos.y + dY/2, 0);
		// make the centerPos a bit back
		centerPos.x += fieldEdgeDiameter/2*Math.cos(this.axeAngle);
		centerPos.y += fieldEdgeDiameter/2*Math.sin(this.axeAngle);

		this.goalHitboxBody = new CANNON.Body({
			mass: 0,
			shape: new CANNON.Box(new CANNON.Vec3(.2, goalLength/2, 5)),
			position: centerPos,
			material: new CANNON.Material({ friction: 0, restitution: 1 }),
		});
		this.goalHitboxBody.quaternion.setFromAxisAngle(new CANNON.Vec3(0, 0, 1), this.axeAngle);
		this.goalHitboxBody.collisionResponse = false;
		this.goalHitboxBody.isTrigger = true;

		this.goalHitboxBody.addEventListener("collide", function(event){
			isBallInGoal.a = true;
		});
		physicsWorld.addBody(this.goalHitboxBody);
	}

	loseHealth() {
		this.health--;
		if (this.healthMeshes.length > 0)
			this.paddle.mesh.remove(this.healthMeshes.pop());
	}

	movePaddle(dt, keysdown) {
		// to be implemented in the subclasses
		throw new Error('You have to implement the method movePaddle in a Subclass!');
	}

	update(dt, keysdown) {
		if (this.health <= 0) {
			return;
		}
		this.movePaddle(dt, keysdown)
		this.paddle.update();
		if (this.isBallInGoal.a)
			this.loseHealth();
	}
}
