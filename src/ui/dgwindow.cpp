#include "dgwindow.h"
#include "dgcentralwidget.hpp"

#include <QDesktopServices>
#include <QUrl>
#include <QMenuBar>

DGWindow::DGWindow(DGController* dgc, QWidget *parent) :
	QMainWindow(parent)
{
	this->setWindowTitle("DevGarden");
	this->resize(1080,640);
	this->setMinimumSize(640,360);
	ctrl = dgc;

	QMenuBar* bar = new QMenuBar(nullptr);
	this->setMenuBar(bar);

	createMenuActions();

	centralWidget = new DGCentralWidget(this);
	setCentralWidget(centralWidget);
}

void DGWindow::createMenuActions() {
	//TODO: Locale system. This is rather critical, actually.
	menuFile = menuBar()->addMenu(tr("&File"));
    menuFile->addAction(tr("New File/Project..."), this, SLOT(nullSlot()), QKeySequence::New);
    menuFile->addAction(tr("Open Folder/Project..."), ctrl, SLOT(openFolder()), QKeySequence::Open);
    menuFile->addAction(tr("Open Files..."), ctrl, SLOT(openFiles()), QKeySequence(tr("Ctrl+Shift+O")));
	menuFile->addSeparator();
    menuFile->addAction(tr("Save"), this, SLOT(nullSlot()), QKeySequence::Save);
    menuFile->addAction(tr("Save As..."), this, SLOT(nullSlot()), QKeySequence::SaveAs);
    menuFile->addAction(tr("Save All"));
    menuFile->addAction(tr("Reload"), this, SLOT(nullSlot()), QKeySequence::Refresh);
	menuFile->addSeparator();
    menuFile->addAction(tr("Close"), this, SLOT(nullSlot()), QKeySequence::Close);
    menuFile->addAction(tr("Close Project"));
	menuFile->addSeparator();
    menuFile->addAction(tr("Import..."));
    menuFile->addAction(tr("Export..."));
	menuFile->addSeparator();
    menuFile->addAction(tr("Quit"), this, SLOT(quit()), QKeySequence::Quit);

	menuEdit = menuBar()->addMenu(tr("&Edit"));
    menuEdit->addAction(tr("Undo"), this, SLOT(nullSlot()), QKeySequence::Undo);
    menuEdit->addAction(tr("Redo"), this, SLOT(nullSlot()), QKeySequence::Redo);
	menuEdit->addSeparator();
    menuEdit->addAction(tr("Cut"), this, SLOT(nullSlot()), QKeySequence::Cut);
    menuEdit->addAction(tr("Copy"), this, SLOT(nullSlot()), QKeySequence::Copy);
    menuEdit->addAction(tr("Paste"), this, SLOT(nullSlot()), QKeySequence::Paste);
    menuEdit->addAction(tr("Paste from Clipboard History"));
	menuEdit->addSeparator();
    menuEdit->addAction(tr("Select All"), this, SLOT(nullSlot()), QKeySequence::SelectAll);
    menuEdit->addAction(tr("Find/Replace"), this, SLOT(nullSlot()), QKeySequence::Find);
    menuEdit->addAction(tr("Advanced Find/Replace"), this, SLOT(nullSlot()), QKeySequence(tr("Ctrl+Shift+F")));
	menuEdit->addSeparator();
    menuEdit->addAction(tr("Format Selection"));
    menuEdit->addAction(tr("Comment Selection"));

	menuBuild = menuBar()->addMenu(tr("&Build"));
    menuBuild->addAction(tr("Cancel Build"));
    menuBuild->addAction(tr("Regen Build Scripts"));
    menuBuild->addAction(tr("Build Settings..."));
	menuBuild->addSeparator();
    menuBuildBuild = menuBuild->addMenu(tr("Build"));
    menuBuildBuild->addAction(tr("Last Target"));
    menuBuildBuild->addAction(tr("Debug"));
    menuBuildBuild->addAction(tr("Release"));
    menuBuildBuild->addAction(tr("Custom..."));
    menuBuild->addAction(tr("Rebuild"));
    menuBuild->addAction(tr("Clean"));
    menuBuild->addAction(tr("Deploy"));
	menuBuild->addSeparator();
    menuBuildBuildAll = menuBuild->addMenu(tr("Build All"));
    menuBuildBuildAll->addAction(tr("Last Target"));
    menuBuildBuildAll->addAction(tr("Debug"));
    menuBuildBuildAll->addAction(tr("Release"));
    menuBuildBuildAll->addAction(tr("Custom..."));
    menuBuild->addAction(tr("Rebuild All"));
    menuBuild->addAction(tr("Clean All"));
    menuBuild->addAction(tr("Deploy All"));

	menuDebug = menuBar()->addMenu(tr("&Run/Debug"));
    menuDebug->addAction(tr("Run"));
    menuDebug->addAction(tr("Run Settings..."));
	menuDebug->addSeparator();
    menuDebug->addAction(tr("Debug"));
    menuDebug->addAction(tr("Debug External Application..."));
    menuDebug->addAction(tr("Load Core File..."));
    menuDebug->addAction(tr("Show Debug Window"));
    menuDebug->addAction(tr("Debugger Settings..."));
	menuDebug->addSeparator();
    menuDebug->addAction(tr("Interrupt"));
    menuDebug->addAction(tr("Continue"));
    menuDebug->addAction(tr("Toggle Breakpoint"));
    menuDebug->addAction(tr("Step Over"));
    menuDebug->addAction(tr("Step Into"));
	menuDebug->addSeparator();
    menuDebugAnalyze = menuDebug->addMenu(tr("Analyze"));
    menuDebugAnalyze->addAction(tr("Memory Checker"));
    menuDebugAnalyze->addAction(tr("Thread Checker"));
    menuDebugAnalyze->addAction(tr("Call Graph"));
    menuDebugAnalyze->addAction(tr("Cache Profiler"));
    menuDebugAnalyze->addAction(tr("Heap Profiler"));
    menuDebug->addAction(tr("Analyze External Application..."));
    menuDebug->addAction(tr("Analysis Settings..."));
	menuDebug->addSeparator();
    menuDebug->addAction(tr("Test"));
    menuDebug->addAction(tr("Test Settings..."));

	menuWindow = menuBar()->addMenu(tr("&Window"));
    menuWindow->addAction(tr("Minimize"), this, SLOT(showMinimized()));
    menuWindow->addAction(tr("Expand"), this, SLOT(showMaximized()));
    menuWindow->addAction(tr("Toggle Full Screen"), this, SLOT(toggleFullscreen()), QKeySequence::FullScreen);
	menuWindow->addSeparator();
    menuWindow->addAction(tr("Toggle Lower Bar"));
    menuWindow->addAction(tr("Toggle Split View Bar"));
    menuWindow->addAction(tr("Toggle Sidebar"));
	menuWindow->addSeparator();
    menuWindow->addAction(tr("Increase Font Size"), this, SLOT(zoomIn()), QKeySequence::ZoomIn);
    menuWindow->addAction(tr("Decrease Font Size"), this, SLOT(zoomOut()), QKeySequence::ZoomOut);
    menuWindow->addAction(tr("Reset Font Size"));
	menuWindow->addSeparator();
    menuWindow->addAction(tr("Toggle Light/Dark Theme"));
    menuWindow->addAction(tr("Run Command Prompt..."), this, SLOT(nullSlot()), QKeySequence(tr("Alt+Space")));
    menuWindow->addAction(tr("Settings..."), this, SLOT(nullSlot()), QKeySequence::Preferences);

	menuHelp = menuBar()->addMenu(tr("&Help"));
    menuHelp->addAction(tr("Manual"), this, SLOT(nullSlot()), QKeySequence::HelpContents);
    menuHelp->addAction(tr("Command Reference"));
    menuHelp->addAction(tr("Hacking DevGarden"));
	menuHelp->addSeparator();
    menuHelp->addAction(tr("Project Page"), this, SLOT(openProjectPage()));
    menuHelp->addAction(tr("Report Bug..."), this, SLOT(openBugReportPage()));
}

void DGWindow::openProjectPage() {
	QDesktopServices::openUrl(QUrl("https://github.com/TheRabbitologist/DevGarden"));
}

void DGWindow::openBugReportPage() {
	QDesktopServices::openUrl(QUrl("https://github.com/TheRabbitologist/DevGarden/issues?q=is%3Aopen+is%3Aissue"));
}

void DGWindow::quit() {
	this->close();
}

void DGWindow::toggleFullscreen() {
	this->isFullScreen()?this->showNormal():this->showFullScreen();
}

void DGWindow::zoomOut() {}
void DGWindow::zoomIn() {}

void DGWindow::nullSlot() {}

DGWindow::~DGWindow() {
}