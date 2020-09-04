var page = require('webpage').create();
var system = require('system');

if (system.args.length !== 3) {
  console.log('Usage: ' + system.args[0] + ' html_file png_file');
  phantom.exit(1);
}

var htmlFile = system.args[1];
var pngFile = system.args[2];

page.open(htmlFile, function(status) {
  if (status === 'fail') {
    console.log('Error! failed to open ' + htmlFile);
    phantom.exit(1);
  }

  page.viewportSize = { width: 600, height: 600 };
  page.zoomFactor = 4.00;
  var clipRect = page.evaluate(function(){
    return document.querySelector('.katex-html').getBoundingClientRect();
  });

  page.evaluate(function() {
    document.body.bgColor = 'white';
  });

  page.clipRect = {
    top:    clipRect.top * page.zoomFactor - clipRect.top,
    left:   clipRect.left * page.zoomFactor - clipRect.left,
    width:  clipRect.width * page.zoomFactor + clipRect.left * 2,
    height: clipRect.height * page.zoomFactor + clipRect.top * 2
  };
  // console.log(page.clipRect.top);
  // console.log(page.clipRect.left);
  // console.log(page.clipRect.width);
  // console.log(page.clipRect.height);

  page.render(pngFile);
  phantom.exit();
});
