import Player from './Player.js';


export default class HumanPlayer extends Player {
	constructor(scene, physicsWorld, playerNb, startPos, endPos, fieldEdgeDiameter, upKeyCode, downKeyCode, playersNb, name) {
		super(scene, physicsWorld, playerNb, startPos, endPos, fieldEdgeDiameter, playersNb);
		this.name = name;
		this.upKeyCode = upKeyCode; // 87, 83 for w, s
		this.downKeyCode = downKeyCode;
	}


	setDownKeyCode(downKeyCode)
	{
		this.downKeyCode = downKeyCode;
	}

	setUpKeyCode(upKeyCode)
	{
		this.upKeyCode = upKeyCode;
	}

	movePaddle(dt, keysdown)
	{
		if (keysdown.includes(this.upKeyCode))
			{this.paddle.moveUp(dt);
		}
		if (keysdown.includes(this.downKeyCode))
			this.paddle.moveDown(dt);
	}
}
