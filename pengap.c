#include <string.h>

#include <webkit/webkit.h>
#include <libnotify/notify.h>

#include "pengap.h"
#include "pengap.js.h"

static GtkWidget* window_main;
static GtkWidget* webkit_view;

void load_status_update(GtkWidget*, gpointer);
gboolean message_recieved(WebKitWebView*, gchar*, gint, gchar*, gpointer);

void pengap_init(gint* argc, gchar*** argv) {

  gtk_init(argc, argv);
  notify_init("pengap");

  // Create main window
  window_main = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  g_signal_connect(window_main, "destroy", G_CALLBACK(gtk_main_quit), NULL);

  // Set default title
  gtk_window_set_title(GTK_WINDOW(window_main), "pengap");

  // Set settings on view
  webkit_view = webkit_web_view_new();
  WebKitWebSettings* settings = webkit_web_view_get_settings(WEBKIT_WEB_VIEW(webkit_view));
  g_object_set(G_OBJECT(settings), "enable-scripts", TRUE, NULL);
  g_object_set(G_OBJECT(settings), "enable-html5-database", TRUE, NULL);
  g_object_set(G_OBJECT(settings), "enable-html5-local-storage", TRUE, NULL);
  g_object_set(G_OBJECT(settings), "enable-offline-web-application-cache", TRUE, NULL);
  g_object_set(G_OBJECT(settings), "enable-plugins", TRUE, NULL);
  g_object_set(G_OBJECT(settings), "enable-spell-checking", TRUE, NULL);

  // Add the view to the window
  GtkWidget* scrollbars = gtk_scrolled_window_new(NULL, NULL);
  gtk_container_add(GTK_CONTAINER(scrollbars), webkit_view);

  gtk_container_add(GTK_CONTAINER(window_main), scrollbars);

  g_signal_connect(webkit_view, "notify::load-status", G_CALLBACK(load_status_update), NULL);
  g_signal_connect(webkit_view, "console-message", G_CALLBACK(message_recieved), NULL);


}

gint pengap_main() {

  gtk_widget_show_all(window_main);

  gtk_main();

  return 0;
}

void pengap_default_size(gint width, gint height) {

  gtk_window_set_default_size(GTK_WINDOW(window_main), width, height);
}

void pengap_load(const gchar* uri) {

  webkit_web_view_load_uri(WEBKIT_WEB_VIEW(webkit_view), uri);
}

void load_status_update(GtkWidget* view, gpointer data) {

  WebKitLoadStatus status = webkit_web_view_get_load_status(WEBKIT_WEB_VIEW(view));

  switch (status) {

    // page load began
    case WEBKIT_LOAD_COMMITTED:
      // load the api
      webkit_web_view_execute_script(WEBKIT_WEB_VIEW(webkit_view), pengap_js); 
    break;

    // page load complete
    case WEBKIT_LOAD_FINISHED:
      gtk_window_set_title(GTK_WINDOW(window_main), webkit_web_view_get_title(WEBKIT_WEB_VIEW(view)));
    break;
  }
}

gboolean message_recieved(WebKitWebView* view, gchar* message, gint line,
                          gchar* source_id, gpointer user_data) {

  // Messages have a major (class) minor (function) format
  PengapClass class;
  PengapFunction function;

  sscanf(message, "%*s %i %i", (gint*) &class, (gint*) &function);

  switch (class) {

    case PENGAP_APP:
      switch (function) {

        case PENGAP_TERMINATE:
          gtk_main_quit();
          return TRUE;
        break;

        case PENGAP_ACTIVATE:
          gtk_window_present(GTK_WINDOW(window_main));
          return TRUE;
        break;

        case PENGAP_HIDE:
          gtk_window_iconify(GTK_WINDOW(window_main));
          return TRUE;
        break;

        case PENGAP_UNHIDE:
          gtk_window_deiconify(GTK_WINDOW(window_main));
          return TRUE;
        break;

        case PENGAP_BEEP:
          gdk_display_beep(gdk_display_get_default());
          return TRUE;
        break;

        default: return FALSE; break;
      }
    break;

    case PENGAP_WINDOW:

      switch (function) {

        case PENGAP_RESIZE: {

          char* data = strstr(message, "[");

          GKeyFile* object = g_key_file_new();
          g_key_file_load_from_data(object, data, -1, G_KEY_FILE_NONE, NULL);

          gint width = g_key_file_get_integer(object, "resize", "width", NULL);
          gint height = g_key_file_get_integer(object, "resize", "height", NULL);

          gtk_window_resize(GTK_WINDOW(window_main), width, height);

          g_key_file_free(object);
          return TRUE;

        }
        break;

        default: return FALSE; break;
      }

    break;

    case PENGAP_NOTICE:
      switch (function) {

        case PENGAP_NOTIFY: {

          char* data = strstr(message, "[");

          GKeyFile* object = g_key_file_new();
          g_key_file_load_from_data(object, data, -1, G_KEY_FILE_NONE, NULL);

          gchar* title = g_key_file_get_string(object, "notify", "title", NULL);
          gchar* content = g_key_file_get_string(object, "notify", "content", NULL);

          NotifyNotification* notice = notify_notification_new(title, content, NULL);
          notify_notification_show(notice, NULL);

          g_free(title);
          g_free(content);
          g_key_file_free(object);
          return TRUE;
        }
        break;

        default: return FALSE; break;
      }
    break;

    default: return FALSE; break;
  }

  // eat the message
  return FALSE;
}

