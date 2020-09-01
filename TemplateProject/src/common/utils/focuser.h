#ifndef FOCUSER_H
#define FOCUSER_H
#include <QtWidgets/qwidget.h>

class Focuser {
  QWidget *widget;

public:
  Focuser(QWidget *w)
  {
      widget = w;
  }

public:
  void show()
  {
      widget->show();
      focus();
  }

  void focus()
  {
      widget->activateWindow();
      widget->raise();
  }
};

#endif // FOCUSER_H
