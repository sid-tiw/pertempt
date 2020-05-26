var canv = document.getElementById("progress");
var canvCtx = canv.getContext('2d');
var height = canv.offsetHeight;
var width = canv.offsetWidth;
var number_of_nodes = 8;
var colors = new Array();

var period = 1000;  // in milli-seconds
var startTime = null;

var randNums = new Array();
for (let i = 0; i < number_of_nodes; i++) {
    let tempX = Math.floor(Math.random() * (width - 10)) + 5, tempY = Math.floor(Math.random() * (height - 10)) + 5;
    let coords = {
        'X': tempX,
        'Y': tempY
    };
    randNums.push(coords);
}

for (let i = 0; i < number_of_nodes; i++) {
    let tempR = Math.floor(Math.random() * 256), tempG = Math.floor(Math.random() * 256), tempB = Math.floor(Math.random() * 256);
    colors.push("rgb(" + tempR.toString() + ", " + tempG.toString() + ", " + tempB.toString() + ")");
}

function setRandoms() {
    randNums.splice(0, number_of_nodes);
    colors.splice(0, number_of_nodes);
    for (let i = 0; i < number_of_nodes; i++) {
        let tempX = Math.floor(Math.random() * (width - 10)) + 5, tempY = Math.floor(Math.random() * (height - 10)) + 5;
        let coords = {
            'X': tempX,
            'Y': tempY
        };
        randNums.push(coords);
    }
    for (let i = 0; i < number_of_nodes; i++) {
        let tempR = Math.floor(Math.random() * 256), tempG = Math.floor(Math.random() * 256), tempB = Math.floor(Math.random() * 256);
        colors.push("rgb(" + tempR.toString() + ", " + tempG.toString() + ", " + tempB.toString() + ")");
    }
}

function animate(time) {
    if (!startTime)
        startTime = time;
    if ((time - startTime) % period < 10)
        setRandoms();
    canvCtx.clearRect(0, 0, 300, 300);
    canvCtx.beginPath();
    var currentTime = new Date();
    for (let i = 0; i < number_of_nodes; i++) {
        console.log(randNums[i].X, randNums[i].Y);
        canvCtx.fillStyle = colors[i];
        canvCtx.strokeStyle = "rgb(255, 255, 255)";
        canvCtx.beginPath();
        let radius = Math.abs(4 * Math.sin((2 * Math.PI * (time - startTime)) / period));
        canvCtx.arc(randNums[i].X, randNums[i].Y, radius, 0, 2 * Math.PI);
        canvCtx.stroke();
        canvCtx.fill();
    }
    window.requestAnimationFrame(animate);
}

window.requestAnimationFrame(animate);