var static = require('node-static');
var http = require('http');
var port = 1729;
var hostname = '127.0.0.1';
var file = new static.Server('../CLIENT/');

var server = http.createServer((request, response) => {
	if (request.method == "POST") {
		var body = "";
        request.on('data', (chunk) => {
            body += chunk;
		});
		console.log(body);
	}
	request.addListener('end', function () {
		file.serve(request, response);
	}).resume();
});

server.listen(port, hostname, () => {
	var time = new Date();
	console.log("server started at ", time.toUTCString());
});