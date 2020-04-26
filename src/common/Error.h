#pragma once

#define SHOW_ERROR(msg)                                                                            \
  QMessageBox errorBox;                                                                            \
  errorBox.setText(#msg);                                                                          \
  errorBox.setStandardButtons(QMessageBox::Ok);                                                    \
  errorBox.exec();                                                                                 \
  return;
