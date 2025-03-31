
import * as constants from './constants.js';
import * as THREE from 'three';
import { TextGeometry } from 'three/addons/geometries/TextGeometry.js';


export default function createText({font, message, size=4, height=0.5, fontColor="#ffffff", sideColor="#000000",
			curveSegments=12, bevelEnabled=true, bevelThickness=1, bevelSize=0.5, bevelOffset=0, bevelSegments=1, shadow=false}) {
	const props = {
		font,
		size,
		depth: height,
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
	// let mat = new THREE.MeshMatcapMaterial({
		// 	// matcap: constants.matcapTexture,
		// 	color: 0x00f0ff
		// });
	let mat = [
		new THREE.MeshBasicMaterial({ color: fontColor}), // front
		new THREE.MeshBasicMaterial({ color: sideColor }) // side
	];
	let mesh = new THREE.Mesh(textGeo, mat);
	if (shadow) {
		mesh.castShadow = true;
		// mesh.receiveShadow = true;
	}

	// center the text
	const centerOffsetX = - 0.5 * (textGeo.boundingBox.max.x - textGeo.boundingBox.min.x);
	const centerOffsetY = - 0.5 * (textGeo.boundingBox.max.y - textGeo.boundingBox.min.y);
	mesh.position.x = centerOffsetX;
	mesh.position.y = centerOffsetY;

	textGroup.add(mesh);
	return textGroup;

}
