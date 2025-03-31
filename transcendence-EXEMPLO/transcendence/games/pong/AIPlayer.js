import * as THREE from 'three';

import Player from './Player';
import Paddle from './Paddle';

export default class AIPlayer extends Player {
	constructor(scene, physicsWorld, playerNb, startPos, endPos, fieldEdgeDiameter, ball, fieldVertices, playersNb) {
		super (scene, physicsWorld, playerNb, startPos, endPos, fieldEdgeDiameter, playersNb);
		// set the ai paddle skin
		this.paddle.setSkin(Paddle.aiSkin);
		this.physicsWorld = physicsWorld;
		this.ball = ball;
		this.targetPosition = this.goalHitboxBody.position;
		this.paddlePosition = this.paddle.body.position;
		this.startPos = startPos;
		this.endPos = endPos;
		this.scene = scene

		// Wall
		this.goalLength = startPos.distanceTo(endPos);
		let dX = endPos.x - startPos.x;
		let dY = endPos.y - startPos.y;
		this.centerPos = new THREE.Vector3(startPos.x + dX/2, startPos.y + dY/2, 0);
		this.centerPos.x += fieldEdgeDiameter/2*Math.cos(this.axeAngle);
		this.centerPos.y += fieldEdgeDiameter/2*Math.sin(this.axeAngle);

		this.goal = this.createWall(this.startPos, this.endPos);
		this.wallArray = [];
		// create arrayWall of all walls except goal
		for (let nbWalls = 1; nbWalls < this.playersNb; nbWalls++)
		{
			if (fieldVertices[nbWalls] == this.startPos)
				continue;
			else
			{
				this.wallArray.push(this.createWall(fieldVertices[nbWalls], fieldVertices[nbWalls+1]));
			}
		}
		this.goalPos = this.wallArray.length;
		// this.wallArray.push(this.goal);
	}


	// ---------- Preparing the walls and goal ----------


	// create the wall object based on the startPos, and endPos
	createWall(startPos, endPos)
	{
		return {
			startPos: new THREE.Vector3(startPos.x, startPos.y, startPos.z),
			endPos: new THREE.Vector3(endPos.x, endPos.y, endPos.z),
			slope: this.calculateSlope(startPos, endPos),
			normal: this.calculateNormal(startPos, endPos)
		};
	}

	calculateNormal(startPos, endPos)
	{
		// Calculate the direction vector of the wall
		const directionVector = [endPos.x - startPos.x, endPos.y - startPos.y];

		// Calculate the perpendicular vector (normal vector) by rotating the direction vector by 90 degrees counterclockwise
		const normalVector = [-directionVector[1], directionVector[0]];

		// Normalize the normal vector
		const normalLength = Math.sqrt(normalVector[0] * normalVector[0] + normalVector[1] * normalVector[1]);
		const normalizedNormal = new THREE.Vector3(0, 0, 0);
		normalizedNormal.x = normalVector[0] / normalLength;
		normalizedNormal.y = normalVector[1] / normalLength;

		return normalizedNormal;
	}

	calculateSlope(startPos, endPos)
	{
		return ((endPos.y - startPos.y) / (endPos.x - startPos.x));
	}


	// ---------- Predicting ball position ----------

	normalizeV3(vector)
	{
		const magnitude = Math.sqrt(Math.pow(vector.x, 2) + Math.pow(vector.y, 2) + Math.pow(vector.z, 2));
		const normalizeV3 = new THREE.Vector3(vector.x / magnitude, vector.y / magnitude, vector.z / magnitude);
		return normalizeV3;
	}

	isPointOnSegment(point, startPos, endPos) {
		const tolerance = 0.000001; // Tolerance for floating point comparisons

		// Calculate the distance between two points
		function distanceSquared(p1, p2) {
			const dx = p2.x - p1.x;
			const dy = p2.y - p1.y;
			const dz = p2.z - p1.z;
			return dx * dx + dy * dy + dz * dz;
		}

		// Calculate the squared distance between the start and end points
		const segmentLengthSquared = distanceSquared(startPos, endPos);

		return (
			distanceSquared(startPos, point) + distanceSquared(point, endPos) - segmentLengthSquared
		) < tolerance;
	}

	getBallInterWithray()
	{
		let pointOnRay = new THREE.Vector3();
		let pointOnSegment = new THREE.Vector3();
		const normalizedVelocity = new THREE.Vector3(this.ball.body.velocity.x, this.ball.body.velocity.y, this.ball.body.velocity.z);
		normalizedVelocity.normalize();
		const ray = new THREE.Ray(this.ball.body.position, normalizedVelocity);
		ray.distanceSqToSegment(this.startPos, this.endPos, pointOnRay, pointOnSegment);
		if (!this.isPointOnSegment(pointOnRay, this.startPos, this.endPos))
		{
			for (const wall of this.wallArray)
			{
				if (!this.isPointOnSegment(pointOnRay, wall.startPos, wall.endPos))
				{
					const normDir = ray.direction.clone().normalize();
					const incidentVector = normDir.clone().sub(wall.normal.clone().multiplyScalar(2 * wall.normal.dot(normDir)));
					const reflectedRayDir = incidentVector.normalize();
					const reflectedRay = new THREE.Ray(pointOnRay, reflectedRayDir);
					reflectedRay.distanceSqToSegment(this.startPos, this.endPos, pointOnRay, pointOnSegment);
				}
				else
					break;
			}
		}
		return pointOnRay;
	}

	// ---------- Working DO NOT TOUCH ----------

	updateBall(ball)
	{
		this.ball = ball;
		this.targetPosition = this.getBallInterWithray();
		// this.drawSphere(this.targetPosition);
	}

	movePaddle(dt) {
		if (!this.targetPosition) {
			return;
		}
		const threshold = 1;
		const	startToTarget = this.startPos.distanceTo(this.targetPosition);
		const	startToPaddle = this.startPos.distanceTo(this.paddle.body.position);
		const	endToTarget = this.endPos.distanceTo(this.targetPosition);
		const	endToPaddle = this.endPos.distanceTo(this.paddle.body.position);

		if (startToTarget < startToPaddle - threshold)
			this.paddle.moveDown(dt);
		else if (endToTarget < endToPaddle - threshold)
			this.paddle.moveUp(dt);
	}

	drawSphere(newPosition) {
		// Remove existing sphere (if any)
		if (this.currentSphereMesh) {
			this.paddle.mesh.remove(this.currentSphereMesh);
			this.currentSphereMesh = null; // Reset the reference
		}
		var colors = ['#ff0000', '#00ff00', '#0000ff', '#ffffff','#f000f0', '#00bff']
		var color=colors[this.playerNb];
		// Create a new sphere
		const geometry = new THREE.SphereGeometry(4, 5, 5);
		const material = new THREE.MeshBasicMaterial({ color: color});
		this.currentSphereMesh = new THREE.Mesh(geometry, material);
		this.currentSphereMesh.position.copy(newPosition);

		// Add to the scene
		this.scene.add(this.currentSphereMesh);
	}
}
