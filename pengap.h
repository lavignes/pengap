#include <gtk/gtk.h>

typedef enum {

  PENGAP_APP = 0,
  PENGAP_WINDOW = 1,
  PENGAP_PATH = 2,
  PENGAP_NOTICE = 3,
  PENGAP_EVENT = 4

} PengapClass;

typedef enum {

  PENGAP_TERMINATE = 0,
  PENGAP_ACTIVATE = 1,
  PENGAP_HIDE = 2,
  PENGAP_UNHIDE = 3,
  PENGAP_BEEP = 4,

  PENGAP_RESIZE = 0,
  PENGAP_MOVE = 1,

  PENGAP_NOTIFY = 0

} PengapFunction;

void pengap_init(gint* argc, gchar*** argv);
gint pengap_main();

void pengap_default_size(gint width, gint height);
void pengap_load(const gchar* uri);