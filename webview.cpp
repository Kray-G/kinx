/*
  For Windows
    $ cl /O2 /std:c++17 /EHac webview.cpp /D WEBVIEW_WIN=1 user32.lib ole32.lib
*/
#include "webview.hpp"

int main(int argc, char **argv) {
  wv::WebView w{
      800, 600, true, true, Str("WebView"), Str("http://www.google.com")};

  if (w.init() == -1) {
    return 1;
  }

  int i = 0;
  while (w.run() == 0)
    printf("%d\n", ++i);

  return 0;
}
