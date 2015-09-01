#ifdef _WIN32
#include <windows.h>
#endif

#include "QtCore/QSettings"
#include "QtCore/QFileInfo"
#include "QtCore/QDateTime"
#include "QtCore/QString"
#include "QtCore/QVariant"
#include "QtCore/QTimer"

#include "QtWidgets/QApplication"

#include "gui/mainwindow.h"


int main(int argc, char *argv[])
{
	QApplication qapp(argc, argv);
	qapp.setApplicationName("ClearsignGUI");
	qapp.setOrganizationName("insaneFactory");
	qapp.setOrganizationDomain("http://www.insanefactory.com/");
	qapp.setQuitOnLastWindowClosed(true);

	// Create main window and initialize it by program parameters.
	MainWindow win(qapp.arguments(), 0, 0);
	win.show();

	return qapp.exec();
}
