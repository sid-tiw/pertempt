let uname = document.getElementById("uname");
let name = document.getElementById("name");

name.addEventListener('focusin', () => {
	name.className = 'mid';
});

uname.addEventListener('focusin', () => {
	uname.className = 'mid';
});

uname.addEventListener('focusout', () => {
	uname.className = "inpt";
});

name.addEventListener('focusout', () => {
	name.className = "inpt";
});