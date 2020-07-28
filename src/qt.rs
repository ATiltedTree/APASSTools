use cpp_core::{Ptr, Ref, StaticUpcast};
use qt_core::{qs, slot, ContextMenuPolicy, QBox, QObject, QPoint, SlotNoArgs};
use qt_widgets::{
    QAction, QApplication, QLineEdit, QMenu, QMessageBox, QPushButton, QTableWidget,
    QTableWidgetItem, QVBoxLayout, QWidget, SlotOfQPoint, SlotOfQTableWidgetItemQTableWidgetItem,
};

use std::rc::Rc;

fn main() {
    QApplication::init(|_| unsafe {
        let _form = APASSTools::new();
        QApplication::exec()
    })
}

struct APASSTools {
    widget: QBox<QWidget>,
    line_edit: QBox<QLineEdit>,
}

impl StaticUpcast<QObject> for APASSTools {
    unsafe fn static_upcast(ptr: Ptr<Self>) -> Ptr<QObject> {
        ptr.widget.as_ptr().static_upcast()
    }
}

impl APASSTools {
    fn new() -> Rc<Self> {
        unsafe {
            let widget = QWidget::new_0a();
            let layout = QVBoxLayout::new_1a(&widget);
            let line_edit = QLineEdit::new();
            layout.add_widget(&line_edit);

            widget.show();

            let this = Rc::new(Self { widget, line_edit });
            this
        }
    }
}
