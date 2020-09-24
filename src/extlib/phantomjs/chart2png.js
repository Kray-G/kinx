var page, system;

var page = require('webpage').create();
var system = require('system');
var fs = require('fs');

page.onError = function(message, trace) {
  var stack;
  stack = ['PHANTOM ERROR: ' + message];
  if (trace && trace.length) {
    stack.push('TRACE:');
    trace.forEach(function(t) {
      var ref;
      return stack.push(' -> ' + (t.file || t.sourceURL) + ': ' + t.line + ((ref = t["function"]) != null ? ref : ' (in function ' + t["function"](+{
      ')': ''
      })));
    });
  }
  console.error(stack.join('\n'));
  return phantom.exit(1);
};

page.onCallback = function(data) {
  page.clipRect = data.clipRect;
  page.render(data.dest);
  return phantom.exit();
};

var chartjsFile = system.args[1];
var pngFile = system.args[2];
var width = system.args[3];
var height = system.args[4];
var dataFile = system.args[5];
var fontSize = system.args[6] || "10";

var data = fs.read(dataFile);
page.injectJs(chartjsFile);

page.viewportSize = { width: width, height: height };
page.evaluate(function() {
  document.body.bgColor = 'white';
});

page.evaluate(function(dest, width, height, data, fontSize) {
  var canvas = document.createElement('canvas');
  canvas.id = 'chart';
  canvas.width = width;
  canvas.height = height;
  canvas.style.backgroundColor = "rgba(255, 255, 255, 1)";
  document.querySelector('body').appendChild(canvas);

  var chart = document.getElementById('chart');
  var dataObj = JSON.parse(data);
  dataObj.options = dataObj.options || {};
  dataObj.options.animation = {
    duration: 0,
    onComplete: function() {
      return window.callPhantom({
        clipRect: chart.getBoundingClientRect(),
        dest: dest
      });
    }
  };

  Chart.defaults.global.defaultFontColor = '#000';
  Chart.defaults.global.defaultFontSize = parseInt(fontSize);
  new Chart(chart.getContext('2d'), dataObj);
}, pngFile, width, height, data, fontSize);
