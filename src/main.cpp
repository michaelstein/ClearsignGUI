#ifdef _WIN32
#include <windows.h>
#endif

#include "QtCore/QSettings"
#include "QtCore/QFileInfo"
#include "QtCore/QDateTime"
#include "QtCore/QString"
#include "QtCore/QVariant"
#include "QtCore/QTimer"

#include "QtGui/QApplication"

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


#ifdef _WIN32
// \see http://stackoverflow.com/questions/9555375/qt-cmake-vc-produce-a-command-prompt
int CALLBACK WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	return main(nCmdShow, &lpCmdLine);
}
#endif
