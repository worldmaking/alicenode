#!/usr/bin/env node

const { exec, spawn, fork } = require('child_process');

const nodemon = require('nodemon');
const app = "index.js";


/*
var fn = process.stdout.write;
process.stdout.write = function write() {
  fn.apply(process.stdout, arguments);
  fn.apply(process.stdout, arguments);
}

let server = spawn("node", ["index.js"]);
server.stdout.on('data', (data) => {
	console.log(`stdout: ${data}`);
});
server.stderr.on('data', (data) => {
	console.log(`stderr: ${data}`);
});
server.on('close', (code) => {
	console.log(`child process exited with code ${code}`);
});
*/


nodemon({ script: app });
nodemon.on('start', function () {
	console.log(app + ' has started');
}).on('quit', function () {
	console.log(app + ' has quit');
	process.exit();
}).on('restart', function (files) {
	console.log("----------------------------------------------------------------------");
	console.log(app + ' restarted due to: ', files);
}).on('crash', function() {
	nodemon.restart();
	nodemon({
		script: app
	});
});