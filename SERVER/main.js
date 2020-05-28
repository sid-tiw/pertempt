var { exec } = require('child_process');
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
		request.on('end', () => {
			console.log(body);
			String.prototype.char;
			var parse = (body) => {
				body += "&";
				let result = {};
				let temp1 = "", temp2 = "";
				for (let i = 0; i <= body.length; i++) {
					console.log(body.charAt(i));
					if (body.charAt(i) != "=" && body.charAt(i) != "&") {
						if (body.charAt(i) == "+")
							temp2 += " ";
						else
							temp2 += body.charAt(i);
					}
					else {
						console.log(temp1, temp2);
						if (body.charAt(i) == "&") {
							result[temp1] = temp2;
							temp1 = "";
							temp2 = "";
						}
						else {
							temp1 = temp2;
							temp2 = "";
						}
					}
				}
				return result;
			};
			var parsedData = parse(body);
			var userName = parsedData['uname'];
			var name = parsedData['name'];
			var rawString = "main.exe";
			rawString += " \"" + userName + "\"";
			rawString += " \"" + name + "\"";
			exec(rawString, (err, output, stError) => {
				console.log("Siddhartha");
				if (err) {
					console.error(err);
					return;
				  }
				  console.log(output);
			});
		});
	}
	request.addListener('end', function () {
		file.serve(request, response);
	}).resume();
});

server.listen(port, hostname, () => {
	var time = new Date();
	console.log("server started at ", time.toUTCString());
});