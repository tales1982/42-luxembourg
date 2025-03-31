import * as THREE from 'three';
import { LineGeometry } from 'three/examples/jsm/lines/LineGeometry.js';
import { LineMaterial } from 'three/examples/jsm/lines/LineMaterial.js';
import { Line2 } from 'three/examples/jsm/lines/Line2.js';

export default function createLine({points, color='#FFFFFF', lineWidth=0.002, zOffset=0}) {
	const geometry = new LineGeometry();
	geometry.setPositions(points);
	geometry.translate(0, 0, zOffset);
	const material = new LineMaterial({
		color: color,
		linewidth: lineWidth, // in pixels
	});
	const line = new Line2(geometry, material);
	return line;
}
