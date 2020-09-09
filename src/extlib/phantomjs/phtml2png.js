var page = require('webpage').create();
var system = require('system');

if (system.args.length !== 4) {
  console.log('Usage: ' + system.args[0] + ' html_file png_file width');
  phantom.exit(1);
}

var htmlFile = system.args[1];
var pngFile = system.args[2];
var width = system.args[3];

function endsWith(str, suffix) {
  return str.indexOf(suffix, str.length - suffix.length) !== -1;
}

page.open(htmlFile, function(status) {
  if (status === 'fail') {
    console.log('Error! failed to open ' + htmlFile);
    phantom.exit(1);
  }

  page.zoomFactor = 4.00;
  page.viewportSize = { width: width * page.zoomFactor, height: 600 };
  var clipRect = page.evaluate(function(){
    var all = document.querySelector('#katex-node').getBoundingClientRect();
    var clip = document.querySelector('.katex-html').getBoundingClientRect();
    return {
      top: all.top,
      left: clip.left,
      width:  clip.width,
      height: all.height
    };
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

  if (endsWith(pngFile, ".jpg") || endsWith(pngFile, ".jpeg")) {
    page.render(pngFile, {format: 'jpeg', quality: '100'});
  } else {
    page.render(pngFile);
  }
  phantom.exit();
});
