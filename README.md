# Pertempt 
Hey Github Users! Search for your closest connection on Github.

![Code Quality Score](https://www.code-inspector.com/project/11040/score/svg)           ![Code Grade](https://www.code-inspector.com/project/11040/status/svg)

## Authors
- Siddhartha Tiwari
- Siddharth Mani Tiwari

## Contributors
No contributors yet.

## Contribute
### Linux
- Install the following dependencies
  - Apache Cassandra
  - DataStax C++ Driver for Cassandra
  - Curl
  - Curl C API(libcurl)
  - Node.js
- Start Cassandra by `systemctl start cassandra` if not done already.
- Clone the repository with `git clone https://github.com/sid-tiw/pertempt.git`
- run `./build` to build the project.
- run `npm install` to install the node dependencies.
- `cd` into the SERVER directory.
- start the server by typing in `node main.js`. If the <b>port 1729</b> is not free for listening on your machine, change it accordingly.
- Access the main page through the browser. Because there is no file named index.html in the CLIENT folder, you need to enter the `localhost:1729/home.html` in the URL bar.

### Windows
- Download the <b>MSVC 142</b> compiler and all its dependencies.
- You can either install Visual Studio 2019 whole or just the VS command line tools.<br>
- Install the same dependencies that are given in the Linux section.<br>
- You need to build static libraries of libcurl using the MSVC compiler according to your architecture.<br>
- Place <b>libcurl</b> in any location, preferably `C:/CURL`. Refer to [`line 27: main.cpp`](https://github.com/sid-tiw/pertempt/blob/553f4af9a19cb3855bbea2b4ab65d6441737492e/CPP/main.cpp#L27) for details.
- Compile the CPP files using `cl -IC:/CURL main.cpp operations.cpp person.cpp -o pertempt` in the <b>VS Command Line</b>.
- Place the executable in the SERVER folder.
- Follow the steps given in the linux section for starting the server.

## Instructions
- Change all the ports and addresses to default before making a pull request.
- Rather than making a single large file, divide it into multiple files.
- Try to design efficient algorithms if you want to implement something.
- Try to keep the code portable across different operating systems. Never make it Windows oriented. In any case the code should be compatible for <b>Linux</b>.
