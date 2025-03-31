import * as THREE from 'three';
import { TextGeometry } from 'three/addons/geometries/TextGeometry.js';

export default function createText({font, message, size=4, depth=0.5, curveSegments=12, bevelEnabled=false, castShadow=true,
		bevelThickness=1, bevelSize=0.5, bevelOffset=0, bevelSegments=1, frontColor="#ffffff", sideColor="#000000"}) {
	const props = {
		font,
		size,
		depth,
		curveSegments,
		bevelEnabled,
		bevelThickness,
		bevelSize,
		bevelOffset,
		bevelSegments
	};
	const textGroup = new THREE.Object3D();
	const textGeo = new TextGeometry(message, props);
	textGeo.computeBoundingBox();
	let mat = [
		new THREE.MeshBasicMaterial({ color: frontColor}), // front
		new THREE.MeshBasicMaterial({ color: sideColor}) // side
	];
	let mesh = new THREE.Mesh(textGeo, mat);

	// center the text
	const centerOffsetX = - 0.5 * (textGeo.boundingBox.max.x - textGeo.boundingBox.min.x);
	const centerOffsetY = - 0.5 * (textGeo.boundingBox.max.y - textGeo.boundingBox.min.y);
	mesh.position.x = centerOffsetX;
	mesh.position.y = centerOffsetY;
	mesh.castShadow = castShadow;

	textGroup.add(mesh);
	return textGroup;

}
