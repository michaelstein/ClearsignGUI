#ifndef _VIDEOSTREAMING_MAINWINDOW_HEADER_
#define _VIDEOSTREAMING_MAINWINDOW_HEADER_

#include "QtCore/QObject"
#include "QtCore/QString"
#include "QtCore/QSharedPointer"

#include "QtGui/QMainWindow"

class MainWindow : public QMainWindow
{
	Q_OBJECT
public:
	MainWindow(const QStringList &arguments, QWidget *parent, Qt::WindowFlags f = 0);
	~MainWindow();

public slots:
	void on_updateButton_pressed();
	void on_clearsignButton_pressed();
	void on_verifyButton_pressed();

protected:

private slots:

private:
	class Private;
	Private *d;
};

#endif
