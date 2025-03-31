function	showHistory()
{
	updateTable('historyPongVersusTableContainer', 'PV');
	updateTable('historyPongTournamentTableContainer', 'PT');
	updateTable('historyExitSoloTableContainer', 'ES');
	updateTable('historyExitVersusTableContainer', 'EV');
}

document.addEventListener("DOMContentLoaded", function()
{
	const tabButtons = document.querySelectorAll(".nav-link");
	const tabContents = document.querySelectorAll(".tab-pane");

	function switchTab(event)
	{
		tabButtons.forEach(button => button.classList.remove("active"));
		tabContents.forEach(content => content.classList.remove("show", "active"));

		const clickedButton = event.target;
		clickedButton.classList.add("active");

		const targetId = clickedButton.getAttribute("data-i18n");
		const targetContent = document.getElementById(targetId);
		targetContent.classList.add("show", "active");
	}
	tabButtons.forEach(button => {
		button.addEventListener("click", switchTab);
	});
});


async function updateTable(tableContainerId, game_id) {
    console.log("updateTable: ", game_id);
    const userAlias = localStorage.getItem('userAlias');
	const lang = localStorage.getItem('language') || 'en';
    if (!userAlias) {
        console.error('No user alias found in local storage');
        return;
    }

	const langData = await fetchLanguageData(lang);
    getGameHistory(userAlias, game_id)
        .then(data => {
            const tableContainer = document.getElementById(tableContainerId);
            tableContainer.innerHTML = '';
			if (!tableContainer) {
                console.error(`No element found with id "${tableContainerId}"`);
                return;
            }

            if (!data || !data.length) {
                return;
            }

            let tableHTML = ``;
			data.forEach(game => {
                tableHTML += '<tr>';
                tableHTML += `<td>${game.user}</td>`;
				if (game.position[0] === 0 && game.game_id != 'ES')
					tableHTML += `<td>💀</td>`;
				else if (game.position[0] === 1 && game.game_id != 'ES')
					tableHTML += `<td>👑</td>`;
				else
                	tableHTML += `<td>${game.position[0]} s</td>`;
                tableHTML += `<td>${game.position[1]}</td>`;
                tableHTML += `<td>${new Date(game.date).toLocaleString()}</td>`;
                tableHTML += '</tr>';
            });
			console.log("tableHTML: ", tableHTML);
            tableHTML += '</tbody></table>';
            tableContainer.innerHTML = tableHTML;
        })
        .catch(error => console.error('Error getting game history:', error));
}

// NO TOUCH

function sendGameData(gameHistory)
{
	// Convert gameData to JSON
	const username = localStorage.getItem('userAlias')
	const csrfToken = getCookie('csrftoken')
	const jsonData = JSON.stringify({username: username, gameHistory: gameHistory});

	// Send JSON data to the backend using fetch API
	fetch('/save_game_result', {
		method: 'POST',
		headers: {
			'Content-Type': 'application/json',
			'X-CSRFToken': csrfToken // Include CSRF token in headers
		},
		body: jsonData
	})
	.then(response => {
		if (response.ok) {
			// Game data saved successfully
			console.log('Game history saved successfully');
		} else {
			// Error handling if saving failed
			console.error('Failed to save game data');
		}
	})
	.catch(error => {
		console.error('Error sending game data:', error);
	});
}

// retrieves the last 10 games of 'game_id' associated to 'username'
function getGameHistory(username, game_id)
{
	return new Promise((resolve, reject) => {
		fetch(`/get_game_history?username=${username}&game_id=${game_id}`, {
			method: 'GET'
		})
		.then(response => {
			if (response.ok) {
				return response.json();
			} else {
				throw new Error('Failed to fetch game history data.');
			}
		})
		.then(data => {
			if (data.error) {
				console.error("Error:", data.error);
				reject(data.error); // Reject the Promise if there's an error
			} else {
				console.log("Game history:", data);
				resolve(data); // Resolve the Promise with the game history data
			}
		})
		.catch(error => {
			console.error(error);
			reject(error); // Reject the Promise if there's an error
		});
	});
}

function getDatabase()
{
	fetch('/print_all_records')
	.then(response => {
		if (response.ok) {
			return response.json();
		} else {
			throw new Error('Failed to fetch data.');
		}
	})
	.then(data => {
		console.log(data);

	})
	.catch(error => {
		console.error('Error:', error);
	});

}
