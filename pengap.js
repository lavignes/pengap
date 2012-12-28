pengap = {}
pengap.app = {

  terminate: function() {
    console.log("pengap 0 0")
  },

  activate: function() {
    console.log("pengap 0 1")
  },

  hide: function() {
    console.log("pengap 0 2")
  },

  unhide: function() {
    console.log("pengap 0 3")
  },

  beep: function() {
    console.log("pengap 0 4")
  }
}

pengap.window = {

  resize: function(msg) {

    console.log("pengap 1 0 [resize]\nwidth=" + msg.width + "\nheight=" + msg.height);
  }

  move: function(msg) {

    console.log("pengap 1 0 [resize]\nwidth=" + msg.width + "\nheight=" + msg.height);
  }
}

pengap.notice = {

  notify: function(msg) {
    console.log("pengap 3 0 [notify]\ntitle=" + msg.title + "\ncontent=" + msg.content)
  }
}