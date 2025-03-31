import * as THREE from 'three';


export default class Cube {
	constructor({scene, x=0, y=0, z=0, width=1, depth=1, color='#ffffff'}) {
		this.mesh = this.createMesh(x, y, z, width, depth, color);
		this.scene = scene;
		scene.add(this.mesh);
	}

	createMesh(x, y, z, width, depth, color) {
		const geometry = new THREE.BoxGeometry(width, width, depth);
		const material = new THREE.MeshStandardMaterial({color: color});
		const mesh = new THREE.Mesh(geometry, material);
		mesh.position.set(x, y, z);
		mesh.castShadow = true;
		mesh.receiveShadow = true;
		return mesh;
	}

	delete() {
		this.scene.remove(this.mesh);
		this.mesh.geometry.dispose();
		this.mesh.material.dispose()
	}

}
