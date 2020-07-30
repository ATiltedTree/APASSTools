use gio::prelude::*;
use gtk::prelude::*;

use gtk::{ApplicationWindow, WindowPosition};

use std::env::args;

fn main() {
    let application = gtk::Application::new(Some("de.atiltedtree.apasstools"), Default::default())
        .expect("FAILED!");

    application.connect_activate(|application| {
        let window = ApplicationWindow::new(application);

        window.set_title("APASSTools");
        window.set_position(WindowPosition::Center);

        window.show_all();
    });

    application.run(&args().collect::<Vec<_>>());
}
