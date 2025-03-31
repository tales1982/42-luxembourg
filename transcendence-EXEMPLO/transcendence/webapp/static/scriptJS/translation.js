// This file is used to handle the translation of the website

async function	fetchLanguageData(lang)
{
	const response = await fetch(`/static/languages/${lang}.json`);
	return response.json();
}

// Set the language preference in the local storage

function	setLanguagePreference(lang)
{
	localStorage.setItem('language', lang);
}

// Update the content of the website with the new language data

function	updateContent(langData)
{
	document.querySelectorAll('[data-i18n]').forEach(element => {
		const key = element.getAttribute('data-i18n');
		element.textContent = langData[key];
	});
}

// Change the language of the website

async function	changeLanguage(lang)
{
	await setLanguagePreference(lang);
	const langData = await fetchLanguageData(lang);
	updateContent(langData);
}

// Event listener to change the language of the website when DOM is loaded

document.addEventListener('DOMContentLoaded', async () => {
	const userPreferredLanguage = localStorage.getItem('language') || 'en';
	const langData = await fetchLanguageData(userPreferredLanguage);
	updateContent(langData);
	document.querySelector('.form-select.custom-select').value = userPreferredLanguage;
});

// Update the Error modal message with the correct language

async function	updateModalMessage(errorKey)
{
	const lang = localStorage.getItem('language') || 'en';
	const langData = await fetchLanguageData(lang);
	document.getElementById('errorMessage').textContent = langData[errorKey];
	let alertModal = new bootstrap.Modal(document.getElementById('errorModal'));
	alertModal.show();
}

// Update the Tournament modal message with the correct language

async function	updateModalTournament()
{
	const	lang = localStorage.getItem('language') || 'en';
	const	langData = await fetchLanguageData(lang);
	const	player = langData['player'];
	return (player);
}

// Activates or deactivates the drop-down menu

function	disableDropdown()
{
	const	dropdown = document.getElementById('dropdownLang');
	if (dropdown)
		dropdown.disabled = true;
}

function	enableDropdown()
{
	const	dropdown = document.getElementById('dropdownLang');
	if (dropdown)
		dropdown.disabled = false;
}

function	languageRestriction()
{
	const	menuToCheck = document.querySelectorAll('#pongVersusIG, #pongTournamentIG, #findExitSoloIG, #findExitVersusIG');
	let		acceptChange = true;
	menuToCheck.forEach(function(element)
	{
		if (!element.classList.contains('d-none'))
			acceptChange = false;
	});
	return (acceptChange);
}

function	changeLanguageDropdown()
{
	if (languageRestriction())
		enableDropdown();
	else
		disableDropdown();
}
