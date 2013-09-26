#include "mainwindow.h"
#include "ui_mainwindowform.h"

#include <QtCore/QProcess>


///////////////////////////////////////////////////////////////////////////////
// MainWindow (Client-side)
///////////////////////////////////////////////////////////////////////////////

class MainWindow::Private
{
public:
	Private(MainWindow *o)
		: owner(o),
		  form(nullptr)
	{
		
	}

	MainWindow *owner;
	Ui_MainWindowForm *form;
	QStringList arguments;
};

MainWindow::MainWindow( const QStringList &arguments, QWidget *parent, Qt::WindowFlags f )
	: QMainWindow( parent, f ), d( new Private( this ) )
{
	d->arguments = arguments;
	d->form = new Ui_MainWindowForm();
	d->form->setupUi(this);

	QFont font = QFont ("Courier");
	font.setStyleHint (QFont::Monospace);
	font.setPointSize (8);
	font.setFixedPitch (true);
	d->form->inputText->setFont (font);
	d->form->outputText->setFont (font);

	on_updateButton_pressed();
}

MainWindow::~MainWindow()
{
	if (d->form)
		delete d->form;
	delete d;
}

void MainWindow::on_updateButton_pressed()
{
	// Clear list.
	d->form->keyBox->clear();
	QStringList keys;

	/* Retrieve key list. */
	// Create GPG process.
	QProcess gpg;

	// Create parameters.
	QStringList params;
	params << "--list-secret-keys";

	// Start process.
	gpg.start( "gpg", params );
	if( !gpg.waitForStarted() )
		return;

	if( !gpg.waitForFinished() )
		return;

	QByteArray result = gpg.readLine();
	QRegExp regex( "uid\\s+([a-zA-Z_\\ ]+)<(\\w+\\@[a-zA-Z\\_\\-\\.]+)>" );
	while( !result.isNull() && !result.isEmpty() ) {
		QString str( result );

		int pos = regex.indexIn( str );
		if (pos > -1) {
			QString uid = regex.cap(2);  // EMail address.
			keys << uid;
		}

		result = gpg.readLine();
	}

	d->form->keyBox->addItems( keys );
	d->form->keyBox->setCurrentIndex( 0 );
}

void MainWindow::on_clearsignButton_pressed()
{
	if( d->form->keyBox->count() <= 0 ) {
		d->form->statusbar->showMessage( tr( "Error: No key selected." ) );
		return;
	}

	// Create GPG process.
	QProcess gpg;

	// Create parameters.
	QStringList params;
	params << "--armor";
	params << "--clearsign";
	params << "--local-user";
	params << d->form->keyBox->currentText();

	// Start process.
	gpg.start( "gpg", params );
	if( !gpg.waitForStarted() )
		return;

	// Write input.
	QByteArray input = d->form->inputText->toPlainText().toUtf8();
	gpg.write( input );
	gpg.closeWriteChannel();

	if( !gpg.waitForFinished() )
		return;

	// Read output.
	QByteArray output = gpg.readAll();
	QString clearsigned( output );
	d->form->outputText->setPlainText( clearsigned );
}

void MainWindow::on_verifyButton_pressed()
{
	// Create GPG process.
	QProcess gpg;

	// Create parameters.
	QStringList params;
	params << "--verify";

	// Start process.
	gpg.start( "gpg", params );
	if( !gpg.waitForStarted() )
		return;

	// Write input.
	QByteArray input = d->form->inputText->toPlainText().toUtf8();
	gpg.write( input );
	gpg.closeWriteChannel();

	if( !gpg.waitForFinished() )
		return;

	// Read output.
	QByteArray output = gpg.readAll();
	QString verfied( output );
	d->form->outputText->setPlainText( verfied );
}
