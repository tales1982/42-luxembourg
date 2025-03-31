import * as maps from './maps/maps.js';


export default class MapData {
	constructor(mapArray) {
		this._mapArray = mapArray;
		this._height = mapArray.length;
		this._width = mapArray[0].length;
	}

	isOutOfBounds(x, y) {
		return x < 0 || x >= this.getWidth() || y < 0 || y >= this.getHeight();
	}

	getCell(x, y) {
		if (this.isOutOfBounds(x, y)) {
			return null; // out of bounds
		}
		return this._mapArray[this._height-y-1][x];
	}

	getRandomEmptyCell(maxTries=100) {
		let x = Math.floor(Math.random() * this.getWidth());
		let y = Math.floor(Math.random() * this.getHeight());

		while (this.getCell(x, y) !== maps.EMPTY && maxTries > 0) {
			x = Math.floor(Math.random() * this.getWidth());
			y = Math.floor(Math.random() * this.getHeight());
			maxTries--;
		}
		if (maxTries === 0) {
			console.error('Could not find an empty cell for powerup');
			return null;
		}
		return {x, y};
	}

	getHeight() {
		return this._height;
	}

	getWidth() {
		return this._width;
	}

}
