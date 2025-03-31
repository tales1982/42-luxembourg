let	isSwitchOn = true;

// Start Find the Exit (solo) after checking that the conditions are OK
function	launchExitSolo()
{
	let	levels = document.getElementById("exitSoloLevel");
	let	NumberLevels = parseInt(levels.value);

	if (isNaN(NumberLevels))
	{
		updateModalMessage('exit_solo_modal');
		return;
	}

	findExitMenu.classList.add('d-none');
	findExitSoloIG.classList.remove('d-none');
	changeLanguageDropdown()

	if (window.exitGame) {  // Check if function exists (avoid errors)
		const language = localStorage.getItem('language') || 'en';
		console.log("Starting SOLO game with " + NumberLevels + " levels in " + language + " language.");
		window.exitGame(1, NumberLevels, false, 'solo', language, '#webglExitSolo', false, (game) => {
		if (game.isOver) {
			console.log('Solo game is over, time :', game.time);
			let Result = {
				username: localStorage.getItem('userAlias'),
				game_id: 'ES',
				position: [game.time, NumberLevels]
			}
			sendGameData(Result);
			backToMain();
		}
			});
	} else {
		console.error('exitGame function not available.');
	}
}

// Start Find the Exit (Versus) after checking that the conditions are OK

function launchExitVersus()
{
	let	playerSelect = document.getElementById("exitVersusPlayers");
	let	levels = document.getElementById("exitVersusLevel");

	let	FirstTo = parseInt(levels.value);
	let	selectedPlayers = parseInt(playerSelect.value);

	// 1 if the players won, 0 if he lost
	function isFirst(scores, FirstTo)
	{
		if (scores[0] === FirstTo)
			return 1;
		return 0;
	}

	if (isNaN(FirstTo) || isNaN(selectedPlayers))
	{
		updateModalMessage('exit_versus_modal');
		return;
	}
	if (window.exitGame) {  // Check if function exists (avoid errors)
		const language = localStorage.getItem('language') || 'en';
		const powerUps = isSwitchOn;
		console.log("Starting Versus game with ", selectedPlayers, " players and ", FirstTo, " levels with powerups " + powerUps + " in ", language, " language.");
 		window.exitGame(selectedPlayers, FirstTo, powerUps, 'tournament', language, '#webglExitVersus', false, (tournament) => {
			if (tournament.isOver) {
			let Result = {
					username: localStorage.getItem('userAlias'),
					game_id: 'EV',
					position: [isFirst(tournament.scores, FirstTo), selectedPlayers],
					bo_type: FirstTo
				}
				sendGameData(Result);
			}
			backToMain();
			});
		findExitMenu.classList.add('d-none');
		findExitVersusIG.classList.remove('d-none');
		changeLanguageDropdown()
	} else {
		console.error('exitGame function not available.');
	}

}

// Caught the switch button state

document.addEventListener('DOMContentLoaded', function()
{
	let switchInput = document.getElementById('switchBonus');

	switchInput.addEventListener('change', function()
	{
		isSwitchOn = this.checked;
		console.log('Switch is now', isSwitchOn);
	});
});
