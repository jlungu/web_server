# jserve - A simple, multithreaded web-server for Linux/OSX.

## Basic Info
Written in C++, this application runs an HTTP web server, servicing HTTP Requests/Responses for provided build files. Supports Linux, OSX.
Utilizes multithreading to service multiple clients quickly and efficiantly.
## Starting the Web Server
- Navigate to the web_server directory in terminal.
- Run the 'jserve' executable by typing './jserve'
- App will prompt you for which IP address you would like to run the server on; One being 127.0.0.1 (the default) and the rest belonging to your network cards the app detected. Make a selection.
- App will prompt you for the PORT you want to listen for connections to. Enter a PORT number, 8080 is default.
- Web server is now running! Navigate to the printed web address!
## Support
Web Server supports basic HTML/JS applications, as well as build files from some JS frameworks (i.e. React).
## How does it work, really?
After user inputted address/port information, the program binds to the socket created and enters an infinite loop, awaiting connections. On incoming connection, the program hands off the client info to a newly created, detached thread, running the "response" function. This thread will parse the request, find the requested file in the "web" directory, where 
you should put your build files. If it finds the file, it parses it line by line, and puts it in the HTTP response. If the program cant find the file, a 404 error page is
returned. If the program finds the file, it searches for the "Content-Type" to return in the HTTP respnse from some pre-established content-type arrays, utilizing its file extension. If it cant find
the proper content tyle, the HTTP response simply returns a "text/plain" type.
