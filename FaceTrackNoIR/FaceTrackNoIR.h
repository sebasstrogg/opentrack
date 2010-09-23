/********************************************************************************
* FaceTrackNoIR		This program is a private project of the some enthusiastic	*
*					gamers from Holland, who don't like to pay for				*
*					head-tracking.												*
*																				*
* Copyright (C) 2010	Wim Vriend (Developing)									*
*						Ron Hendriks (Researching and Testing)					*
*																				*
* Homepage																		*
*																				*
* This program is free software; you can redistribute it and/or modify it		*
* under the terms of the GNU General Public License as published by the			*
* Free Software Foundation; either version 3 of the License, or (at your		*
* option) any later version.													*
*																				*
* This program is distributed in the hope that it will be useful, but			*
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY	*
* or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for	*
* more details.																	*
*																				*
* You should have received a copy of the GNU General Public License along		*
* with this program; if not, see <http://www.gnu.org/licenses/>.				*
*********************************************************************************/

#ifndef FaceTrackNoIR_H
#define FaceTrackNoIR_H

#include <tchar.h>
#include <QtGui/QMainWindow>
#include <QApplication>
#include <QFileDialog>
#include <QListView>
#include <QPainter>
#include <QWidget>
#include <QDialog>

#include "ui_FaceTrackNoIR.h"
#include "ui_FTNoIR_KeyboardShortcuts.h"
#include "ui_FTNoIR_Preferences.h"
#include <sm_api_qt.h>
#include <Dshow.h>

using namespace sm::faceapi;
using namespace sm::faceapi::qt;

class Tracker;				// pre-define class to avoid circular includes

class FaceTrackNoIR : public QMainWindow
{
	Q_OBJECT

public:
	FaceTrackNoIR(QWidget *parent = 0, Qt::WFlags flags = 0);
	~FaceTrackNoIR();

	void getGameProgramName();					// Get the ProgramName from the game and display it.

private:
	Ui::FaceTrackNoIRClass ui;
	Tracker *tracker;
	QTimer *timMinimizeFTN;

	/** face api variables **/
	VideoDisplayWidget *_display;
	QVBoxLayout *l;
	QWidget *_engine_controls;
	QWidget *_server_controls;
	QWidget *_preferences;
	QWidget *_keyboard_shortcuts;

	/** QT objects **/
	QDialog aboutDialog;	
	QDesktopWidget desktop;

    QAction *minimizeAction;
    QAction *restoreAction;
    QAction *quitAction;

    QSystemTrayIcon *trayIcon;
    QMenu *trayIconMenu;

	void createIconGroupBox();
//	void createMessageGroupBox();
	void createActions();
	void createTrayIcon();

	/** helper **/
	bool cameraDetected;
	bool settingsDirty;

	void GetCameraNameDX();
	void loadSettings();
	void setupFaceTrackNoIR();

	private slots:
		//file
		void open();
		void save();
		void saveAs();
		void exit();

		void setIcon(int index);
		void iconActivated(QSystemTrayIcon::ActivationReason reason);
		void trackingSourceSelected(int index);

		void showVideoWidget();
		void showHeadPoseWidget();
		void showEngineControls();
		void showServerControls();
		void showPreferences();
		void showKeyboardShortcuts();

		// sensibility sliders
		void setSensYaw( int sens );
		void setSensPitch( int sens );
		void setSensRoll( int sens );
		void setSensX( int sens );
		void setSensY( int sens );
		void setSensZ( int sens );

		// invert checkboxes
		void setInvertYaw( int invert );
		void setInvertPitch( int invert );
		void setInvertRoll( int invert );
		void setInvertX( int invert );
		void setInvertY( int invert );
		void setInvertZ( int invert );

		void setUseFilter( int set );

		// reduction factor sliders
		void setRedYaw( int redh );
		void setRedPitch( int redh );
		void setRedRoll( int redh );
		void setRedX( int redh );
		void setRedY( int redh );
		void setRedZ( int redh );

		void setNeutralZone( int angle );

		//smoothing slider
		void setSmoothing( int smooth );

		void startTracker();
		void stopTracker();
		void about();
};

// Widget that has controls for FaceTrackNoIR Preferences.
class PreferencesDialog: public QWidget, public Ui::UICPreferencesDialog
{
    Q_OBJECT
public:

	explicit PreferencesDialog( QWidget *parent=0, Qt::WindowFlags f=0 );
    virtual ~PreferencesDialog();
	void showEvent ( QShowEvent * event );

private:
	Ui::UICPreferencesDialog ui;
	void loadSettings();
	void save();

	/** helper **/
	bool settingsDirty;

private slots:
	void doOK();
	void doCancel();
	void keyChanged( int index ) { settingsDirty = true; };
};

// Widget that has controls for Keyboard shortcuts.
class KeyboardShortcutDialog: public QWidget, public Ui::UICKeyboardShortcutDialog
{
    Q_OBJECT
public:

	explicit KeyboardShortcutDialog( QWidget *parent=0, Qt::WindowFlags f=0 );
    virtual ~KeyboardShortcutDialog();
	void showEvent ( QShowEvent * event );

private:
	Ui::UICKeyboardShortcutDialog ui;
	void loadSettings();
	void save();

	/** helper **/
	bool settingsDirty;
	QList<QString> stringList;			// List of strings, that describe the keyboard-keys
	QList<BYTE> keyList; 				// List of keys, with the values of the keyboard-keys

private slots:
	void doOK();
	void doCancel();
	void keyChanged( int index ) { settingsDirty = true; };
};


#endif // FaceTrackNoIR_H
