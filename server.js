const http = require('http');
const fs = require('fs');
const path = require('path');
const url = require('url');
const server = http.createServer((req, res) => {
    const filePath = path.join(__dirname, 'public', parsedUrl.pathname === '/' ? 'index.html' : parsedUrl.pathname);

    fs.readFile(filePath, (err, data) => {
        if (err) {
        res.writeHead(404, { 'Content-Type': 'text/plain' });
        res.end('404 Not Found');
        return;
        }

        res.writeHead(200, { 'Content-Type': 'text/html' });
        res.end(data);
    });



}).listen(8080, () => {

    console.log('Server is running at http://localhost:8080');


})
