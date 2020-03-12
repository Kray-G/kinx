#ifndef WEBVIEW_H
#define WEBVIEW_H

// Headers
#include <functional>
#include <string>
#if defined(WEBVIEW_WIN)
#define WEBVIEW_MAIN int __stdcall WinMain(HINSTANCE, HINSTANCE, LPSTR, int)
#define UNICODE
#define _UNICODE
#define Str(s) L##s
#define WIN32_LEAN_AND_MEAN
#pragma comment(lib, "gdi32.lib")
#pragma comment(lib, "windowsapp")

#include <objbase.h>
#include <windows.h>
#include <winrt/Windows.Foundation.Collections.h>
#include <winrt/Windows.Web.UI.Interop.h>
#elif defined(WEBVIEW_MAC) // WEBVIEW_WIN
#define WEBVIEW_MAIN int main(int argc, char **argv)
#define Str(s) s
#import <Cocoa/Cocoa.h>
#import <Webkit/Webkit.h>
#include <objc/objc-runtime.h>

// ObjC declarations may only appear in global scope
@interface WindowDelegate : NSObject <NSWindowDelegate, WKScriptMessageHandler>
@end

@implementation WindowDelegate
- (void)userContentController:(WKUserContentController *)userContentController
      didReceiveScriptMessage:(WKScriptMessage *)scriptMessage {
}
@end
#elif defined(WEBVIEW_GTK) // WEBVIEW_MAC
#define WEBVIEW_MAIN int main(int argc, char **argv)
#define Str(s) s
#include <JavaScriptCore/JavaScript.h>
#include <gtk/gtk.h>
#include <webkit2/webkit2.h>
#else // WEBVIEW_GTK
#error "Define one of WEBVIEW_WIN, WEBVIEW_MAC, or WEBVIEW_GTK"
#endif

constexpr auto DEFAULT_URL = Str(
    "data:text/"
    "html,%3C%21DOCTYPE%20html%3E%0A%3Chtml%20lang=%22en%22%3E%0A%3Chead%3E%"
    "3Cmeta%20charset=%22utf-8%22%3E%3Cmeta%20http-equiv=%22X-UA-Compatible%22%"
    "20content=%22IE=edge%22%3E%3C%2Fhead%3E%0A%3Cbody%3E%3Cdiv%20id=%22app%22%"
    "3E%3C%2Fdiv%3E%3Cscript%20type=%22text%2Fjavascript%22%3E%3C%2Fscript%3E%"
    "3C%2Fbody%3E%0A%3C%2Fhtml%3E");

/*
<!DOCTYPE html>
<html lang="en">
<head><meta charset="utf-8"><meta http-equiv="X-UA-Compatible"
content="IE=edge"></head> <body><div id="app"></div><script
type="text/javascript"></script></body>
</html>
*/

namespace wv {
#if defined(WEBVIEW_WIN)
using String = std::wstring;
using namespace winrt::impl;
using namespace winrt::Windows::Foundation;
using namespace winrt::Windows::Foundation::Collections;
using namespace winrt::Windows::Web::UI::Interop;
#elif defined(WEBVIEW_MAC)
using String = std::string;
#elif defined(WEBVIEW_GTK)
using String = std::string;
#endif

class WebView {
  using jscb = std::function<void(WebView &, std::string &)>;

public:
  WebView(int width, int height, bool resizable, bool debug, String title,
          String url = DEFAULT_URL)
      : width(width), height(height), resizable(resizable), debug(debug),
        title(title), url(url) {}
  int init();                      // Initialize webview
  void setCallback(jscb callback); // JS callback
  void setTitle(String t);         // Set title of window
  void setFullscreen(bool fs);     // Set fullscreen
  void setBgColor(uint8_t r, uint8_t g, uint8_t b,
                  uint8_t a); // Set background color
  bool run();                 // Main loop
  void navigate(String u);    // Navigate to URL
  void preEval(String js);    // Eval JS before page loads
  void eval(String js);       // Eval JS
  void css(String css);       // Inject CSS
  void exit();                // Stop loop

private:
  // Properties for init
  int width;
  int height;
  bool resizable;
  bool fullscreen = false;
  bool debug;
  String title;
  String url;

  jscb js_callback;
  bool init_done = false; // Finished running init
  uint8_t bgR = 255, bgG = 255, bgB = 255, bgA = 255;

#if defined(WEBVIEW_WIN)
  String inject =
      Str("window.external.invoke=arg=>window.external.notify(arg);");
  HINSTANCE hInt = nullptr;
  HWND hwnd = nullptr;
  WebViewControl webview{nullptr};
  MSG msg; // Message from main loop

  void resize();
  static LRESULT CALLBACK WndProcedure(HWND hwnd, UINT msg, WPARAM wparam,
                                       LPARAM lparam);
#elif defined(WEBVIEW_MAC) // WEBVIEW_WIN
  String inject = Str("window.external={invoke:arg=>window.webkit."
                      "messageHandlers.webview.postMessage(arg)};");
  bool should_exit = false; // Close window
  NSAutoreleasePool *pool;
  NSWindow *window;
  WKWebView *webview;
#elif defined(WEBVIEW_GTK) // WEBVIEW_MAC
  String inject = Str("window.external={invoke:arg=>window.webkit."
                      "messageHandlers.external.postMessage(arg)};");
  bool ready = false;       // Done loading page
  bool js_busy = false;     // Currently in JS eval
  bool should_exit = false; // Close window
  GtkWidget *window;
  GtkWidget *webview;

  static void external_message_received_cb(WebKitUserContentManager *m,
                                           WebKitJavascriptResult *r,
                                           gpointer arg);
  static void webview_eval_finished(GObject *object, GAsyncResult *result,
                                    gpointer arg);
  static void webview_load_changed_cb(WebKitWebView *webview,
                                      WebKitLoadEvent event, gpointer arg);
  static void destroyWindowCb(GtkWidget *widget, gpointer arg);
  // static gboolean closeWebViewCb(WebKitWebView *webView, GtkWidget *window);
  static gboolean webview_context_menu_cb(WebKitWebView *webview,
                                          GtkWidget *default_menu,
                                          WebKitHitTestResult *hit_test_result,
                                          gboolean triggered_with_keyboard,
                                          gpointer userdata);
#endif                     // WEBVIEW_GTK
};

#if defined(WEBVIEW_WIN)
// Await helper
template <typename T> auto block(T const &async) {
  if (async.Status() != AsyncStatus::Completed) {
    winrt::handle h(CreateEvent(nullptr, false, false, nullptr));
    async.Completed([h = h.get()](auto, auto) { SetEvent(h); });
    HANDLE hs[] = {h.get()};
    DWORD i;
    CoWaitForMultipleHandles(COWAIT_DISPATCH_WINDOW_MESSAGES |
                                 COWAIT_DISPATCH_CALLS | COWAIT_INPUTAVAILABLE,
                             INFINITE, 1, hs, &i);
  }
  return async.GetResults();
}

int WebView::init() {
  hInt = GetModuleHandle(nullptr);
  if (hInt == nullptr) {
    return -1;
  }

  // Initialize Win32 window
  WNDCLASSEX wc;
  wc.cbSize = sizeof(WNDCLASSEX);
  wc.style = 0;
  wc.lpfnWndProc = WndProcedure;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInt;
  wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
  wc.lpszMenuName = NULL;
  wc.lpszClassName = L"webview";
  wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

  RegisterClassEx(&wc);
  hwnd = CreateWindow(L"webview", title.c_str(), WS_OVERLAPPEDWINDOW,
                      CW_USEDEFAULT, CW_USEDEFAULT, 640, 480, nullptr, nullptr,
                      hInt, nullptr);

  if (hwnd == nullptr) {
    MessageBox(NULL, L"Window Registration Failed!", L"Error!",
               MB_ICONEXCLAMATION | MB_OK);
    return 0;
  }

  // Set window size
  RECT r;
  r.left = 0;
  r.top = 0;
  r.right = width;
  r.bottom = height;
  SetWindowPos(hwnd, NULL, r.left, r.top, r.right - r.left, r.bottom - r.top,
               SWP_NOZORDER | SWP_NOACTIVATE | SWP_FRAMECHANGED);

  // Used with GetWindowLongPtr
  SetWindowLongPtr(hwnd, GWLP_USERDATA, (LONG_PTR)this);

  ShowWindow(hwnd, SW_SHOWDEFAULT);
  UpdateWindow(hwnd);
  SetFocus(hwnd);

  // Initialize WinRT WebView
  init_apartment(winrt::apartment_type::single_threaded);

  // Allow intranet access (and localhost)
  WebViewControlProcessOptions options;
  options.PrivateNetworkClientServerCapability(
      WebViewControlProcessCapabilityState::Enabled);

  WebViewControlProcess proc(options);
  webview = block(
      proc.CreateWebViewControlAsync(reinterpret_cast<int64_t>(hwnd), Rect()));
  webview.Settings().IsScriptNotifyAllowed(true);
  webview.ScriptNotify([=](auto const &sender, auto const &args) {
    if (js_callback) {
      std::string s = winrt::to_string(args.Value());
      js_callback(*this, s);
    }
  });
  webview.NavigationStarting(
      [=](auto &&, auto &&) { webview.AddInitializeScript(inject); });

  // Set webview bounds
  resize();

  webview.IsVisible(true);

  // Done initialization, set properties
  init_done = true;

  setTitle(title);
  if (fullscreen) {
    setFullscreen(true);
  }
  setBgColor(bgR, bgG, bgB, bgA);
  navigate(url);

  return 0;
}

void WebView::setCallback(jscb callback) { js_callback = callback; }

void WebView::setTitle(std::wstring t) {
  if (!init_done) {
    title = t;
  } else {
    SetWindowText(hwnd, t.c_str());
  }
}

void WebView::setFullscreen(bool fs) {
  // TODO: implement
}

void WebView::setBgColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  if (!init_done) {
    bgR = r;
    bgG = g;
    bgB = b;
    bgA = a;
  } else {
    webview.DefaultBackgroundColor({a, r, g, b});
  }
}

bool WebView::run() {
  bool loop = GetMessage(&msg, NULL, 0, 0) > 0;
  if (loop) {
    TranslateMessage(&msg);
    DispatchMessage(&msg);
  }
  return !loop;
}

void WebView::navigate(std::wstring u) {
  if (!init_done) {
    url = u;
  } else {
    Uri uri{u};
    webview.Navigate(uri);
  }
}

void WebView::preEval(std::wstring js) { inject += L"(()=>{" + js + L"})()"; }

void WebView::eval(std::wstring js) {
  auto result = block(webview.InvokeScriptAsync(
      L"eval", std::vector<winrt::hstring>({winrt::hstring(js)})));

  // if (debug) {
  // std::cout << winrt::to_string(result) << std::endl;
  //}
}

void WebView::css(std::wstring css) {
  eval(LR"js(
  (
    function (css) {
      if (document.styleSheets.length === 0) {
        var s = document.createElement('style');
        s.type = 'text/css';
        document.head.appendChild(s);
      }
      document.styleSheets[0].insertRule(css);
    }
  )(')js" +
       css + L"')");
}

void WebView::exit() { PostQuitMessage(WM_QUIT); }

void WebView::resize() {
  RECT rc;
  GetClientRect(hwnd, &rc);
  Rect bounds((float)rc.left, (float)rc.top, (float)(rc.right - rc.left),
              (float)(rc.bottom - rc.top));
  webview.Bounds(bounds);
}

LRESULT CALLBACK WebView::WndProcedure(HWND hwnd, UINT msg, WPARAM wparam,
                                       LPARAM lparam) {
  WebView *w =
      reinterpret_cast<WebView *>(GetWindowLongPtr(hwnd, GWLP_USERDATA));

  switch (msg) {
  case WM_SIZE:
    // WM_SIZE will first fire before the webview finishes loading
    // init() calls resize(), so this call is only for size changes
    // after fully loading.
    if (w != nullptr && w->init_done) {
      w->resize();
    }
    return DefWindowProc(hwnd, msg, wparam, lparam);
  case WM_CLOSE:
    DestroyWindow(hwnd);
    break;
  case WM_DESTROY:
    w->exit();
    break;
  default:
    return DefWindowProc(hwnd, msg, wparam, lparam);
  }
  return 0;
}
#elif defined(WEBVIEW_MAC) // WEBVIEW_WIN
int WebView::init() {
  // Initialize autorelease pool
  pool = [NSAutoreleasePool new];

  // Window style: titled, closable, minimizable
  uint style = NSWindowStyleMaskTitled | NSWindowStyleMaskClosable |
               NSWindowStyleMaskMiniaturizable;

  // Set window to be resizable
  if (resizable) {
    style |= NSWindowStyleMaskResizable;
  }

  // Initialize Cocoa window
  window = [[NSWindow alloc]
      // Initial window size
      initWithContentRect:NSMakeRect(0, 0, width, height)
                // Window style
                styleMask:style
                  backing:NSBackingStoreBuffered
                    defer:NO];

  // Minimum window size
  [window setContentMinSize:NSMakeSize(width, height)];

  // Position window in center of screen
  [window center];

  // Initialize WKWebView
  WKWebViewConfiguration *config = [WKWebViewConfiguration new];
  WKPreferences *prefs = [config preferences];
  [prefs setJavaScriptCanOpenWindowsAutomatically:NO];
  [prefs setValue:@YES forKey:@"developerExtrasEnabled"];

  WKUserContentController *controller = [config userContentController];
  // Add inject script
  WKUserScript *userScript = [WKUserScript alloc];
  [userScript initWithSource:[NSString stringWithUTF8String:inject.c_str()]
               injectionTime:WKUserScriptInjectionTimeAtDocumentStart
            forMainFrameOnly:NO];
  [controller addUserScript:userScript];

  webview = [[WKWebView alloc] initWithFrame:NSZeroRect configuration:config];

  // Add delegate methods manually in order to capture "this"
  class_replaceMethod(
      [WindowDelegate class], @selector(windowWillClose:),
      imp_implementationWithBlock(
          [=](id self, SEL cmd, id notification) { this->exit(); }),
      "v@:@");

  class_replaceMethod(
      [WindowDelegate class],
      @selector(userContentController:didReceiveScriptMessage:),
      imp_implementationWithBlock(
          [=](id self, SEL cmd, WKScriptMessage *scriptMessage) {
            if (this->js_callback) {
              id body = [scriptMessage body];
              if (![body isKindOfClass:[NSString class]]) {
                return;
              }

              std::string msg = [body UTF8String];
              this->js_callback(*this, msg);
            }
          }),
      "v@:@");

  WindowDelegate *delegate = [WindowDelegate alloc];
  [controller addScriptMessageHandler:delegate name:@"webview"];
  // Set delegate to window
  [window setDelegate:delegate];

  // Initialize application
  [NSApplication sharedApplication];
  [NSApp setActivationPolicy:NSApplicationActivationPolicyRegular];

  // Sets the app as the active app
  [NSApp activateIgnoringOtherApps:YES];

  // Add webview to window
  [window setContentView:webview];

  // Display window
  [window makeKeyAndOrderFront:nil];

  // Done initialization, set properties
  init_done = true;

  setTitle(title);
  if (fullscreen) {
    setFullscreen(true);
  }
  setBgColor(bgR, bgG, bgB, bgA);
  navigate(url);

  return 0;
}

void WebView::setCallback(jscb callback) { js_callback = callback; }

void WebView::setTitle(std::string t) {
  if (!init_done) {
    title = t;
  } else {
    [window setTitle:[NSString stringWithUTF8String:t.c_str()]];
  }
}

void WebView::setFullscreen(bool fs) {
  if (!init_done) {
    fullscreen = fs;
  } else if (fs) {
    // TODO: replace toggle with set
    [window toggleFullScreen:nil];
  } else {
    [window toggleFullScreen:nil];
  }
}

void WebView::setBgColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  if (!init_done) {
    bgR = r;
    bgG = g;
    bgB = b;
    bgA = a;
  } else {
    [window setBackgroundColor:[NSColor colorWithCalibratedRed:r / 255.0
                                                         green:g / 255.0
                                                          blue:b / 255.0
                                                         alpha:a / 255.0]];
  }
}

bool WebView::run() {
  NSEvent *event = [NSApp nextEventMatchingMask:NSEventMaskAny
                                      untilDate:[NSDate distantFuture]
                                         inMode:NSDefaultRunLoopMode
                                        dequeue:true];
  if (event) {
    [NSApp sendEvent:event];
  }

  return should_exit;
}

void WebView::navigate(std::string u) {
  if (!init_done) {
    url = u;
  } else {
    [webview
        loadRequest:[NSURLRequest
                        requestWithURL:
                            [NSURL URLWithString:[NSString stringWithUTF8String:
                                                               u.c_str()]]]];
  }
}

void WebView::preEval(std::string js) { inject += "(()=>{" + js + "})()"; }

void WebView::eval(std::string js) {
  [webview evaluateJavaScript:[NSString stringWithUTF8String:js.c_str()]
            completionHandler:nil];
}

void WebView::css(std::string css) {
  eval(R"js(
    (
      function (css) {
        if (document.styleSheets.length === 0) {
          var s = document.createElement('style');
          s.type = 'text/css';
          document.head.appendChild(s);
        }
        document.styleSheets[0].insertRule(css);
      }
    )(')js" +
       css + "')");
}

void WebView::exit() {
  // Distinguish window closing with app exiting
  should_exit = true;
  [NSApp terminate:nil];
}

#elif defined(WEBVIEW_GTK) // WEBVIEW_MAC
int WebView::init() {
  if (gtk_init_check(0, NULL) == FALSE) {
    return -1;
  }

  // Initialize GTK window
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

  if (resizable) {
    gtk_window_set_default_size(GTK_WINDOW(window), width, height);
  } else {
    gtk_widget_set_size_request(window, width, height);
  }

  gtk_window_set_resizable(GTK_WINDOW(window), resizable);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

  // Add scrolling container
  GtkWidget *scroller = gtk_scrolled_window_new(nullptr, nullptr);
  gtk_container_add(GTK_CONTAINER(window), scroller);

  // Content manager
  WebKitUserContentManager *cm = webkit_user_content_manager_new();
  webkit_user_content_manager_register_script_message_handler(cm, "external");
  g_signal_connect(cm, "script-message-received::external",
                   G_CALLBACK(external_message_received_cb), this);

  // WebView
  webview = webkit_web_view_new_with_user_content_manager(cm);
  g_signal_connect(G_OBJECT(webview), "load-changed",
                   G_CALLBACK(webview_load_changed_cb), this);
  gtk_container_add(GTK_CONTAINER(scroller), webview);

  g_signal_connect(window, "destroy", G_CALLBACK(destroyWindowCb), this);
  // g_signal_connect(webview, "close", G_CALLBACK(closeWebViewCb), window);

  // Dev Tools if debug
  if (debug) {
    WebKitSettings *settings =
        webkit_web_view_get_settings(WEBKIT_WEB_VIEW(webview));
    webkit_settings_set_enable_write_console_messages_to_stdout(settings, true);
    webkit_settings_set_enable_developer_extras(settings, true);
  } else {
    g_signal_connect(G_OBJECT(webview), "context-menu",
                     G_CALLBACK(webview_context_menu_cb), nullptr);
  }

  webkit_web_view_run_javascript(WEBKIT_WEB_VIEW(webview), inject.c_str(), NULL,
                                 NULL, NULL);

  // Done initialization, set properties
  init_done = true;

  setTitle(title);
  if (fullscreen) {
    setFullscreen(true);
  }
  setBgColor(bgR, bgG, bgB, bgA);
  navigate(url);

  // Finish
  gtk_widget_grab_focus(GTK_WIDGET(webview));
  gtk_widget_show_all(window);

  return 0;
}

void WebView::setCallback(jscb callback) { js_callback = callback; }

void WebView::setTitle(std::string t) {
  if (!init_done) {
    title = t;
  } else {
    gtk_window_set_title(GTK_WINDOW(window), t.c_str());
  }
}

void WebView::setFullscreen(bool fs) {
  if (!init_done) {
    fullscreen = fs;
  } else if (fs) {
    gtk_window_fullscreen(GTK_WINDOW(window));
  } else {
    gtk_window_unfullscreen(GTK_WINDOW(window));
  }
}

void WebView::setBgColor(uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
  if (!init_done) {
    bgR = r;
    bgG = g;
    bgB = b;
    bgA = a;
  } else {
    GdkRGBA color = {r / 255.0, g / 255.0, b / 255.0, a / 255.0};
    webkit_web_view_set_background_color(WEBKIT_WEB_VIEW(webview), &color);
  }
}

bool WebView::run() {
  gtk_main_iteration_do(true);
  return should_exit;
}

void WebView::navigate(std::string u) {
  if (!init_done) {
    url = u;
  } else {
    webkit_web_view_load_uri(WEBKIT_WEB_VIEW(webview), u.c_str());
  }
}

void WebView::preEval(std::string js) { inject += "(()=>{" + js + "})()"; }

void WebView::eval(std::string js) {
  while (!ready) {
    g_main_context_iteration(NULL, TRUE);
  }
  js_busy = true;
  webkit_web_view_run_javascript(WEBKIT_WEB_VIEW(webview), js.c_str(), NULL,
                                 webview_eval_finished, this);
  while (js_busy) {
    g_main_context_iteration(NULL, TRUE);
  }
}

void WebView::css(std::string css) {
  eval(R"js(
    (
      function (css) {
        if (document.styleSheets.length === 0) {
          var s = document.createElement('style');
          s.type = 'text/css';
          document.head.appendChild(s);
        }
        document.styleSheets[0].insertRule(css);
      }
    )(')js" +
       css + "')");
}

void WebView::exit() { should_exit = true; }

void WebView::external_message_received_cb(WebKitUserContentManager *m,
                                           WebKitJavascriptResult *r,
                                           gpointer arg) {
  WebView *w = static_cast<WebView *>(arg);
  if (w->js_callback) {
    JSCValue *value = webkit_javascript_result_get_js_value(r);
    std::string str = std::string(jsc_value_to_string(value));
    w->js_callback(*w, str);
  }
}

void WebView::webview_eval_finished(GObject *object, GAsyncResult *result,
                                    gpointer arg) {
  static_cast<WebView *>(arg)->js_busy = false;
}

void WebView::webview_load_changed_cb(WebKitWebView *webview,
                                      WebKitLoadEvent event, gpointer arg) {
  if (event == WEBKIT_LOAD_FINISHED) {
    static_cast<WebView *>(arg)->ready = true;
  }
}

void WebView::destroyWindowCb(GtkWidget *widget, gpointer arg) {
  static_cast<WebView *>(arg)->exit();
}

// gboolean WebView::closeWebViewCb(WebKitWebView *webView, GtkWidget *window) {
//   gtk_widget_destroy(window);
//   return TRUE;
// }

gboolean WebView::webview_context_menu_cb(WebKitWebView *webview,
                                          GtkWidget *default_menu,
                                          WebKitHitTestResult *hit_test_result,
                                          gboolean triggered_with_keyboard,
                                          gpointer userdata) {
  // Always hide context menu if not debug
  return TRUE;
}
#endif                     // WEBVIEW_GTK

} // namespace wv

#endif // WEBVIEW_H
