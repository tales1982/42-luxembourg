// Selecting the number of players for Pong versus
function	updatePongPlayersVersus()
{
	let	playerSelect = document.getElementById("pongVersusPlayer");
	let	aiSelect = document.getElementById("pongVersusAI");
	let	totalParticipants = 5;

	let	selectedPlayers = parseInt(playerSelect.value);
	let	selectedAI = parseInt(aiSelect.value);

	if (isNaN(selectedPlayers))
		selectedPlayers = 0;
	if (isNaN(selectedAI))
		selectedAI = 0;

	for (let i = 1; i < playerSelect.options.length; i++)
	{
		let playerOptionValue = parseInt(playerSelect.options[i].value);
		if (playerOptionValue + selectedAI > totalParticipants)
			playerSelect.options[i].disabled = true;
		else
			playerSelect.options[i].disabled = false;
	}

	for (let i = 1; i < aiSelect.options.length; i++)
	{
		let aiOptionValue = parseInt(aiSelect.options[i].value);
		if (aiOptionValue + selectedPlayers > totalParticipants)
			aiSelect.options[i].disabled = true;
		else
			aiSelect.options[i].disabled = false;
	}
}

document.addEventListener('DOMContentLoaded', updatePongPlayersVersus);

// Start Pong Versus after checking that the conditions are OK
function	launchPongVersus()
{
	let	playerSelect = document.getElementById("pongVersusPlayer");
	let	aiSelect = document.getElementById("pongVersusAI");
	let	selectedPlayers = parseInt(playerSelect.value);
	let	selectedAI = parseInt(aiSelect.value);

	if (isNaN(selectedPlayers))
		selectedPlayers = 0;
	if (isNaN(selectedAI))
		selectedAI = 0;

	let	totalParticipants = selectedPlayers + selectedAI;

	function hasWon(username, winnerName) {
		if (username === winnerName)
			return 1;
		return 0;
	}

	if (totalParticipants < 2 || selectedPlayers < 1)
	{
		updateModalMessage('pong_versus_modal');
		return;
	}
	if (window.pongGame) {  // Check if function exists
		language = localStorage.getItem('language') || 'en';
		console.log("Starting Versus Pong game with ", selectedPlayers, " players and ", selectedAI, " AI" + " in ", language, " language.");
		const username = localStorage.getItem('userAlias');
		var humanNames = [username]; // ! TODO get the main account name
		for (let i = 1; i < selectedPlayers; i++)
		{
			let playerName = "Guest " + i;
			humanNames.push(playerName);
		}
		window.pongGame(humanNames, selectedAI, 'versus', language, '#webglPongVesus', false, (game) => {
			if (game.isOver) {
				let Result = {
					username: username,
					game_id: 'PV',
					position: [hasWon(username, game.winnerName), selectedPlayers + selectedAI]
				}
				sendGameData(Result);
			}
			backToMain();
		});
	} else {
		console.error('pongGame function not available.');
	}

	pongMenu.classList.add('d-none');
	pongVersusIG.classList.remove('d-none');
	changeLanguageDropdown()
}

// Start Pong Tournament after checking that the conditions are OK
function	launchPongTournament()
{
	let	playerSelect = document.getElementById("pongTournamentPlayer");
	let	selectedPlayers = parseInt(playerSelect.value);

	if (isNaN(selectedPlayers))
	{
		updateModalMessage('pong_tournament_modal');
		return;
	}
	selectPlayersNames(selectedPlayers);
}

// Select the players names for the Pong Tournament
async function	selectPlayersNames(selectedPlayers)
{
	let	form = document.getElementById("playerNamesForm");
	let	fragment = document.createDocumentFragment();
	let	player = await updateModalTournament();
	form.innerHTML = '';

	for (let i = 1; i < selectedPlayers; i++)
	{
		let	inputGroup = document.createElement("div");
		inputGroup.classList.add("input-group", "mb-3");

		let inputLabel = document.createElement("label");
		inputLabel.textContent = player + ` ${i} : `;
		inputLabel.setAttribute("for", `playerName${i}`);
		inputLabel.classList.add("form-label", "custom-input");

		let inputField = document.createElement("input");
		inputField.type = "text";
		inputField.id = `playerName${i}`;
		inputField.name = `playerName${i}`;
		inputField.classList.add("form-control", "custom-input");

		inputGroup.appendChild(inputLabel);
		inputGroup.appendChild(inputField);
		fragment.appendChild(inputGroup);
	}
	form.appendChild(fragment);
	let playerNamesModal = new bootstrap.Modal(document.getElementById('tournamentModal'), {
		backdrop: 'static'
	});
	playerNamesModal.show();
}

// submitPlayerNames sending the players names to the server and check if the names are valid
function	submitPlayerNames()
{
	console.log('submitPlayerNames');
	let form = document.getElementById("playerNamesForm");
	let playerNames = [];
	let players = form.elements;
	let playersCount = players.length;
	let	playerSelect = document.getElementById("pongTournamentPlayer");
	let	selectedPlayers = parseInt(playerSelect.value);
	const username = localStorage.getItem('userAlias');
	const lang = localStorage.getItem('language') || 'en';
	playerNames.push(username);

	for (let i = 0; i < playersCount; i++) {
		if (players[i].nodeName === 'INPUT') {
			const errorMsg = isValidUsername(players[i].value, lang);
			if (errorMsg) {
				alert(errorMsg);
				return;
			}
			playerNames.push(players[i].value);
		}
	}
	console.log('Player Names:', playerNames);
	if (window.pongGame) {
		language = localStorage.getItem('language') || 'en';
		console.log("Starting Tournament Pong game with ", selectedPlayers, " players in ", language, " language.");
		window.pongGame(playerNames, 0, 'tournament', language, '#webglPongTournament', false, (tournament) => {
			if (tournament.winner) { // Check if the game is over
				let Result = {
					username: localStorage.getItem('userAlias'),
					game_id: 'PT',
					position: [hasWon(username, tournament.winner.name), selectedPlayers]
				}
				sendGameData(Result);
			}
		backToMain();
		});

	} else {
		console.error('pongGame function not available.');
	}

	pongMenu.classList.add('d-none');
	pongTournamentIG.classList.remove('d-none');
	changeLanguageDropdown()

	let playerNamesModal = bootstrap.Modal.getInstance(document.getElementById('tournamentModal'));
	playerNamesModal.hide();

	function hasWon(username, winnerName) {
		if (username === winnerName)
			return 1;
		return 0;
	}

	function isValidUsername(username, language) {
		let errorMsg;
		switch (language) {
			case 'fr':
				errorMsg = {
					empty: "Veuillez saisir un nom d'utilisateur.",
					invalidCharacters: "Le nom d'utilisateur ne peut contenir que des lettres et des chiffres.",
					length: "Le nom d'utilisateur doit contenir entre 2 et 20 caractères.",
					taken: "Le nom d'utilisateur est déjà choisi par un autre joueur."
				};
				break;
			case 'de':
				errorMsg = {
					empty: "Bitte geben Sie einen Benutzernamen ein.",
					invalidCharacters: "Benutzername darf nur Buchstaben und Zahlen enthalten.",
					length: "Benutzername muss zwischen 2 und 20 Zeichen lang sein.",
					taken: "Benutzername wurde bereits von einem anderen Spieler gewählt."
				};
				break;
			default:
				errorMsg = {
					empty: "Please enter a username.",
					invalidCharacters: "Username can only contain letters and numbers.",
					length: "Username must be between 2 and 20 characters.",
					taken: "Username already chosen by another player."
				};
		}

		if (!username) {
			return errorMsg.empty;
		} else if (!/^[a-zA-Z0-9]+$/.test(username)) {
			return errorMsg.invalidCharacters;
		} else if (username.length < 2 || username.length > 20) {
			return errorMsg.length;
		} else if (playerNames.includes(username)) {
			return errorMsg.taken;
		}

		return null;
	}
}
