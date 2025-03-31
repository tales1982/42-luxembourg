import * as THREE from 'three';
import * as CANNON from 'cannon-es';
import { LineMaterial } from 'three/examples/jsm/lines/LineMaterial.js';

import createLine from './createLine.js';


export default class Paddle {
	// Mesh materials
	// Basic : no shading
	// Lambert : matte material (emissive color)
	// Phong : shiny material (specular color, shininess)
	// Standard : combination of Lambert and Phong (metalness, roughness)

	static wallSkin = {'line': new LineMaterial({color: '#3CD6EB', linewidth: 0.002}), 'material': new THREE.MeshStandardMaterial({color: "#3CD6EB"})};

	static aiSkin = {'line': new LineMaterial({color: '#ff0000', linewidth: 0.007}), 'material': new THREE.MeshStandardMaterial({color: "#2c3e50"})};

	static skins = [
		// red
		{
			'line': new LineMaterial({color: '#ffaaaa', linewidth: 0.009}),
			'material': new THREE.MeshStandardMaterial(
				{
					color: "#c0392b",
				}
			),
		},
		// yellow
		{
			'line': new LineMaterial({color: '#C2F988', linewidth: 0.009}),
			'material': new THREE.MeshStandardMaterial(
				{
					color: "#F9F871",
					emissive: "#ff0f00",
					emissiveIntensity: .1,

				}
			),
		},
		// green
		{
			'line': new LineMaterial({color: '#beff5f', linewidth: 0.009}),
			'material': new THREE.MeshStandardMaterial(
				{
					color: "#57C05A",
				}
			),
		},
		// blue
		{
			'line': new LineMaterial({color: '#9BDEAC', linewidth: 0.009}),
			'material': new THREE.MeshStandardMaterial(
				{
					color: "#2980b9",
				}
			),
		},

		// purple
		{
			'line': new LineMaterial({color: '#FFA4B8', linewidth: 0.009}),
			'material': new THREE.MeshStandardMaterial(
				{
					color: "#857BCE",
					// emissive: "#ff0f00",
					// emissiveIntensity: .7,
				}
			),
		},
		// pink
		{
			'line': new LineMaterial({color: '#FFE3EF', linewidth: 0.008}),
			'material': new THREE.MeshStandardMaterial(
				{
					color: "#FF84A8",
					// emissive: "#ff0f00",
					// emissiveIntensity: .7,
				}
			),
		},
		// ---- Specials ----
		// dazzle
		{
			'line': new LineMaterial({color: '#00f0f0', linewidth: 0.028}),
			'material': new THREE.MeshBasicMaterial(
				{
					color: "#ffffff",
				}
			),
		},
		// gray
		// {
		// 	'line': new LineMaterial({color: '#dddddd', linewidth: 0.019}),
		// 	'material': new THREE.MeshStandardMaterial(
		// 		{
		// 			color: "#95B0B5",
		// 			emissive: "#ff0f00",
		// 			emissiveIntensity: .01,
		// 			roughness: 0.1,
		// 			metalness: .4,
		// 		}
		// 	),
		// },
		// transparent purple
		{
			'line': new LineMaterial({color: '#eeeeee', linewidth: 0.004}),
			'material': new THREE.MeshPhysicalMaterial(
				{
					color: "#9b59b6",
					transmission: .8,
					roughness: 0.3,
					ior: 1.7,
					thickness: .5,
					specularIntensity: 1,
				}
			),
		},
		// transparent
		{
			'line': new LineMaterial({color: '#aaaaaa', linewidth: 0.0002}),
			'material': new THREE.MeshPhysicalMaterial(
				{
					color: "#ffffff",
					transmission: 1,
					roughness: 0.2,
					ior: 1.7,
					thickness: .5,
					specularIntensity: 1,
				}
			),
		},
	];


	constructor(scene, physicsWorld, startPos, endPos, axeAngle, fieldEdgeDiameter) {
		this.scene = scene;
		this.physicsWorld = physicsWorld;
		this.axeAngle = axeAngle;

		var goalSize = startPos.distanceTo(endPos) - fieldEdgeDiameter;

		// ---- Sizes ----
		var width = 4;
		this.percentLengthSize = 0.3; // 0.5 = 50% of the goal size
		var height = goalSize * this.percentLengthSize ; // length of the paddle...
		var depth = 4;

		// ---- Moving ----
		this.maxMovingDistance = goalSize/2 - height/2;
		var goalDeplacementTime = 1; // time to go from one side to the other [s]
		this.moveSpeed = this.maxMovingDistance * 2 / goalDeplacementTime;

		// ---- Mesh ----
		this.skin = Paddle.skins[Math.floor(Math.random() * 6)]; // select a one of the 6 first skins
		const geometry = new THREE.BoxGeometry(width, height, depth);
		geometry.attributes.uv2 = geometry.attributes.uv; // for the aoMap
		this.mesh = new THREE.Mesh(geometry, this.skin.material);
		this.mesh.castShadow = true;
		scene.add(this.mesh);

		// edge colors
		var edgePoints = [];
		// geometry.ed
		const edgesGeometry = new THREE.EdgesGeometry(geometry);
		for (var i = 0; i < edgesGeometry.attributes.position.array.length; i++) {
			if (i >= 24 && i <30)
				continue;
			edgePoints.push(edgesGeometry.attributes.position.array[i]);
			// if (i==2)
			// 	break
		}

		this.line = createLine({points: edgePoints})
		this.line.material = this.skin.line;
		this.mesh.add(this.line); // edgesGeometry.attributes.position.array

		// ---- Physics ----
		this.centerPos = new THREE.Vector3(startPos.x + (endPos.x - startPos.x)/2, startPos.y + (endPos.y - startPos.y)/2, depth/2+.7);
		this.body = new CANNON.Body({
			mass: 0,
			shape: new CANNON.Box(new CANNON.Vec3(width/2, height/2, depth/2)),
			position: this.centerPos,
			// linearDamping: 0,
			material: new CANNON.Material({ friction: 0, restitution: 1 }),

		});
		this.body.quaternion.setFromAxisAngle(new CANNON.Vec3(0, 0, 1), this.axeAngle);
		physicsWorld.addBody(this.body);

		this.updateMeshPosAndRot();
	}

	delete() {
		this.scene.remove(this.mesh);
		this.physicsWorld.removeBody(this.body);
	}

	getNextSkin() {
		var skinIndex = Paddle.skins.indexOf(this.skin);
		if (skinIndex == -1)
			skinIndex = 0;
		else
			skinIndex = (skinIndex + 1) % Paddle.skins.length;
		return Paddle.skins[skinIndex]; // ? TODO clone needed?
	}

	getPreviousSkin() {
		var skinIndex = Paddle.skins.indexOf(this.skin);
		if (skinIndex == -1)
			skinIndex = 0;
		else
		{
			skinIndex = skinIndex - 1;
			if (skinIndex < 0)
				skinIndex = Paddle.skins.length - 1;
		}
		return Paddle.skins[skinIndex];

	}

	setSkin(skin) {
		this.skin = skin;
		this.mesh.material = skin.material;
		// this.line.material.color.set(skin.line);
		this.line.material = skin.line;
	}

	changeSkin(direction) {
		if (direction > 0)
			this.skin = this.getNextSkin();
		else
			this.skin = this.getPreviousSkin();
		this.setSkin(this.skin);
	}

	move(dt, speed) {
		// make the paddle move in the direction of the angle
		var angle = this.axeAngle + Math.PI/2;
		var depX = speed * Math.cos(angle) * dt;
		var depY = speed * Math.sin(angle) * dt;
		var newPos = new THREE.Vector3(this.body.position.x + depX, this.body.position.y + depY, this.body.position.z);
		var distanceToCenter = this.centerPos.distanceTo(newPos);
		if (distanceToCenter > this.maxMovingDistance)
			return;
		this.body.position.x += depX;
		this.body.position.y += depY;
	}

	moveUp(dt) {
		this.move(dt, this.moveSpeed);
	}

	moveDown(dt) {
		this.move(dt, -this.moveSpeed);
	}

	scale(scale) {
		this.mesh.scale.y += scale;
	}

	updateMeshPosAndRot() {
		this.mesh.position.copy(this.body.position);
		this.mesh.quaternion.copy(this.body.quaternion);
	}

	update() {
		this.updateMeshPosAndRot();
	}
}
