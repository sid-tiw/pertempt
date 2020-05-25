let uname = document.getElementById("uname");
let name = document.getElementById("name");
let sbmt = document.getElementById("sbmt");

sbmt.addEventListener('mouseenter', ()=>{
	sbmt.className = "sbmtAnim";
});

sbmt.addEventListener('mouseleave', ()=>{
	sbmt.className = "sbmt";
});

name.addEventListener('focusin', () => {
	name.className = 'midn';
	if(name.value == "search for")
		name.value = "";
});

uname.addEventListener('focusin', () => {
	uname.className = 'midu';
	if(uname.value == "your Username")
		uname.value = "";
});

uname.addEventListener('focusout', () => {
	uname.className = "inpt up";
	if(uname.value.length == 0)
		uname.value = "your Username";
});

name.addEventListener('focusout', () => {
	name.className = "inpt down";
	if(name.value.length == 0)
		name.value = "search for";
});

