#include <nwm.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

#define DECL(n, h) {n, sizeof(n) - 1, &WindowManager::evt_##h},

static struct EventHandler {
  const char *pattern;
  int length;
  void (WindowManager::*handler)(const char *);
} handlers[] = {
  FOREACH_EVENT(DECL)
};

void WindowManager::handle_event(const char *evt) {
  if (evt[0] == '#') return;
  for (auto &h: handlers) {
    if (strncmp(evt, h.pattern, h.length) == 0) {
      (this->*h.handler)(evt + h.length);
      break;
    }
  }
}

// ---------- EVENT HANDLERS ----------

void WindowManager::evt_timer(const char *evt) {
  uint32_t now;
  sscanf(evt, "%d", &now);
  if (now > uptime) {
    uptime = now;
  }
  for (Window *w: windows) {
    if (w) {
      assert(w->write_fd);
      char buf[64]; sprintf(buf, "t %d\n", now);
      write(w->write_fd, buf, strlen(buf));
    }
  }
  for (Window *w: windows) {
    if (w) w->update();
  }
  render();
}

static int ctrl = 0, alt = 0, shift = 0;

void WindowManager::evt_keydown(const char *evt) {
  char key[20];
  sscanf(evt, "%s", key);
  if (strcmp(key, "LALT") == 0) { alt = 1; return; }
  if (strcmp(key, "LCTRL") == 0) { ctrl = 1; return; }
  if (strcmp(key, "LSHIFT") == 0 || strcmp(key, "RSHIFT") == 0) { shift ^= 1; return; }

  if (ctrl || alt) {
    char event[20];
    sprintf(event, "%s%s%s", ctrl ? "C-" : "", alt ? "A-" : "", key);
    handle_event(event);
  } else {
    if (display_appfinder) {
      if (strcmp(key, "LEFT") == 0) appfinder->prev();
      if (strcmp(key, "TAB") == 0) appfinder->next();
      if (strcmp(key, "RIGHT") == 0) appfinder->next();
      if (strcmp(key, "RETURN") == 0) {
        spawn(appfinder->getcmd());
        display_appfinder = false;
        appfinder->draw();
      }
      if (strcmp(key, "ESCAPE") == 0) {
        display_appfinder = false;
        appfinder->draw();
      }
    } else if (focus) {
      assert(focus->write_fd);
      char buf[64]; sprintf(buf, "kd %s\n", key);
      write(focus->write_fd, buf, strlen(buf));
    }
  }
}

void WindowManager::evt_keyup(const char *evt) {
  char key[20];
  sscanf(evt, "%s", key);

  if (strcmp(key, "LALT") == 0) {
    alt = 0;
    if (display_switcher) {
      switcher->draw();
    }
    display_switcher = false;
    return;
  }
  if (strcmp(key, "LCTRL") == 0) {
    ctrl = 0;
    return;
  }
  if (strcmp(key, "LSHIFT") == 0 || strcmp(key, "RSHIFT") == 0) {
    shift ^= 1;
    return;
  }

  if (focus && !display_appfinder) {
    assert(focus->write_fd);
    char buf[64]; sprintf(buf, "ku %s\n", key);
    write(focus->write_fd, buf, strlen(buf));
  }
}

void WindowManager::evt_switch_window(const char *evt) {
  int i = 0;
  if (!focus) return;
  display_switcher = true;
  if (display_appfinder) {
    display_appfinder = false;
    appfinder->draw();
  }
  while (windows[i] != focus) i ++;
  while (1) {
    i ++;
    if (i >= 16) i = 0;
    if (windows[i]) break;
  }
  set_focus(windows[i]);
}

void WindowManager::evt_moveup_window(const char *evt) {
  if (focus && focus != appfinder) {
    focus->move(focus->x, focus->y - 10);
  }
}

void WindowManager::evt_movedown_window(const char *evt) {
  if (focus && focus != appfinder) {
    focus->move(focus->x, focus->y + 10);
  }
}

void WindowManager::evt_moveleft_window(const char *evt) {
  if (focus && focus != appfinder) {
    focus->move(focus->x - 10, focus->y);
  }
}

void WindowManager::evt_moveright_window(const char *evt) {
  if (focus && focus != appfinder) {
    focus->move(focus->x + 10, focus->y);
  }
}

void WindowManager::evt_appfinder(const char *evt) {
  if (!display_switcher) {
    display_appfinder = true;
    appfinder->draw();
  }
}

