import { GLTFLoader } from 'three/examples/jsm/loaders/GLTFLoader.js';


export const NAME = 'Find The Exit ';

export var DEBUG; // need to be changed in games.js...
export function setDegub(debug) {
	DEBUG = debug;
}

export const gltflLoader = new GLTFLoader();

// lights
export const ambientLightIntensity = 0.46;
export const directionalLightIntensity = 0.5;
// fov
export const fov = 90;

