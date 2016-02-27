


void main (string[] args) {
  Gtk.init (ref args);
  var window = new Gtk.Window ();
  var image_view = new Gtk.ImageView ();
  var file_chooser = new Gtk.FileChooserButton ("Open Image", Gtk.FileChooserAction.OPEN);
  var box = new Gtk.Box (Gtk.Orientation.VERTICAL, 12);

  image_view.fit_allocation = true;
  image_view.transitions_enabled = true;
  image_view.vexpand = true;



  file_chooser.file_set.connect (() => {
    var file = GLib.File.new_for_uri (file_chooser.get_uri ());
    message ("uri: %s", file_chooser.get_uri ());
    image_view.load_from_file_async.begin (file, 0);
  });


  box.add (image_view);
  box.add (file_chooser);


  window.add (box);

  window.show_all ();
  Gtk.main ();
}
