let username = localStorage.getItem('userAlias');
let usernameFormSubmitted = false;

function getCookie(name) {
	const cookieValue = document.cookie.match('(^|;)\\s*' + name + '\\s*=\\s*([^;]+)');
	return cookieValue ? cookieValue.pop() : '';
}
// Redirection to the main page to register a username
function	registerUsernameModal()
{

	const usernameModal = new bootstrap.Modal(document.getElementById('usernameModal'),
	{
		backdrop: 'static',
		keyboard: false
	});
	history.pushState(null, "", '/');
	menuButtons.classList.remove('d-none');
	usernameModal.show();

	const usernameForm = document.getElementById('usernameForm');

	function handleFormSubmit(event){
		event.preventDefault();

		const username = document.getElementById('userAlias').value;
		const language = localStorage.getItem('language') || 'en';

		const errorMsg = validateUsername(username, language);
		if (errorMsg !== null) {
			alert(errorMsg);
			console.log("errorMsg: ", errorMsg);
			return;
		}

		const csrfToken = getCookie('csrftoken');

		fetch('/registerUsername', {
			method: 'POST',
			headers: {
				'Content-Type': 'application/json',
				'X-CSRFToken': csrfToken
			},
			body: JSON.stringify({ username: username })
		})
		.then(response => {
			if (response.ok) {
				localStorage.setItem('userAlias', username);
				console.log('Username registered:', username);
				usernameModal.hide();
				usernameForm.removeEventListener('submit',handleFormSubmit);
			} else {
				return response.json().then(data => {
					alert('Error registering username: ' + data.error);
				});
			}
		})
		.catch(error => console.error('Error sending data:', error));
	}

	function validateUsername(username, language)
	{
		let errMsg;
		switch (language) {
			case 'fr':
				errMsg = {
					empty: "Veuillez saisir un nom d'utilisateur.",
					invalidCharacters: "Le nom d'utilisateur ne peut contenir que des lettres et des chiffres.",
					length: "Le nom d'utilisateur doit contenir entre 2 et 20 caractères."
				};
				break;
			case 'de':
				errMsg = {
					empty: "Bitte geben Sie einen Benutzernamen ein.",
					invalidCharacters: "Benutzername darf nur Buchstaben und Zahlen enthalten.",
					length: "Benutzername muss zwischen 2 und 20 Zeichen lang sein."
				};
				break;
			default:
				errMsg = {
					empty: "Please enter a username.",
					invalidCharacters: "Username can only contain letters and numbers.",
					length: "Username must be between 2 and 20 characters."
				};
		}
		console.log("username: ", username);

		if (!username.trim()) {
			return errMsg.empty;
		} else if (!/^[a-zA-Z0-9]+$/.test(username)) {
			return errMsg.invalidCharacters;
		} else if (username.length < 2 || username.length > 20) {
			return errMsg.length;
		}

		return null;
	}

	usernameForm.addEventListener('submit', handleFormSubmit);
}

// Disconnect the user and redirect to the main page
function	disconnectUser()
{
	if (!forceStopGame)
	{
		forceStopGame = true;
		console.log("The game has been stopped");
	}
	localStorage.removeItem('userAlias');
	username = '';
	route();
	changeLanguageDropdown()
}
