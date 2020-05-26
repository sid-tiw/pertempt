const http = require('http');

const hname = "127.0.0.1";

const port = 3000;

const server = http.createServer((request, response) => {
	let urlData = request.url;
	let indUname = urlData.indexOf("uname=");
	let indName = urlData.indexOf("&name=");
	let file = "home.html";
	console.log(indUname, indName);
	response.statusCode = 200;
	if (indUname != -1)
		file = "info.html";
	var flst = require('fs'),
		path = require('path'),
		filePath = path.join(__dirname, file);
	flst.readFile(filePath, {
		encoding: 'utf-8'
	}, (err, data) => {
		if (!err) {
			response.writeHead(200, {
				"content-Type": "text/html"
			});
			response.write(data);
			response.end();
		} else {
			console.log(err);
		}
	});
});

server.listen(port, hname, () => {
	console.log("start");
});