// Cursor's Animation

const cursorDot = document.querySelector("[data-cursor-dot]");
const cursorOutline = document.querySelector("[data-cursor-outline]");
let cursorTimeout;

window.addEventListener("mousemove", function (e)
{
	const	posX = e.clientX;
	const	posY = e.clientY;

	cursorDot.style.left = `${posX}px`;
	cursorDot.style.top = `${posY}px`;

	cursorOutline.animate({
		left: `${posX}px`,
		top: `${posY}px`
	}, {duration: 200, fill: "forwards"});

	showCursor();
});

function hideCursor()
{
	cursorDot.style.display = "none";
	cursorOutline.style.display = "none";
}

function showCursor()
{
	cursorDot.style.display = "block";
	cursorOutline.style.display = "block";

	clearTimeout(cursorTimeout);

	cursorTimeout = setTimeout(hideCursor, 1000);
}

cursorTimeout = setTimeout(hideCursor, 1000);
