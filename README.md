since it seemed like a neat application:

# PenGap
#### A shameless MacGap clone for gnome-based linux distros
PenGap is basically a 1 to 1 functionality clone of MacGap, but for linux.
It also uses webkit and has a similar API. PenGap is small and fast,
MacGap is bloated in comparison, as an empty PenGap project is around 7 kilobytes.
Once I finish adding all the MacGap functions I'll add some linux specific features.

## Pre-requisites
PenGap should work on any gnome-based desktop environment. (Gnome 2/3, Unity, Pantheon, Cinnamon, etc)

## API
PenGap exposes an object called `pengap` inside JavaScript. The API is so similar to MacGap, one can
really just rename the pengap object in pengap.js to macgap, and their previously made macgap app is magially cross-platform. 

App:

```javascript

// Quit application
pengap.app.terminate();

// Activate application (bring to front)
pengap.app.activate();

// Hide application
pengap.app.hide();

// Un-hide application
pengap.app.unhide();

// System bell
pengap.app.beep();
```

Window:
```javascript
// Resize window
pengap.window.resize({width: 400, height: 200});
```

Notice:
```javascript
// Send a Native User notification
pengap.notice.notify({
  title: "Notify",
  content: "New Message!"
});
```

## Offline Shizzle
The html5-based offline storage is 100% compatable with MacGap. Any offline ready
MacGap application will run fine in PenGap.