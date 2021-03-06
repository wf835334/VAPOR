#ifndef RENDERHOLDER_H
#define RENDERHOLDER_H

#include <qobject.h>
#include "qstackedwidget.h"
#include "qpushbutton.h"
#include "qtableview.h"
#include "EventRouter.h"
#include <vapor/MyBase.h>
#include <QMessageBox>
#include "VaporTable.h"
#include "ui_LeftPanel.h"
#include "ui_NewRendererDialog.h"

QT_USE_NAMESPACE

namespace VAPoR {
	class ControlExec;
	class ParamsMgr;
}

class NewRendererDialog : public QDialog, public Ui_NewRendererDialog {

	Q_OBJECT

public:
 NewRendererDialog(QWidget *parent, VAPoR::ControlExec* ce);

 std::string getSelectedRenderer() {return _selectedRenderer;}
	QMessageBox* msgBox;
	void mouseDoubleClickEvent ( QMouseEvent * event )
	{
	    msgBox = new QMessageBox();
	    msgBox->setWindowTitle("Hello");
	    msgBox->setText("You Double Clicked Mouse Button");
	    msgBox->show();	  

	}; 

private slots:
 void barbChecked(bool state);
 void contourChecked(bool state);
 void imageChecked(bool state);
 void twoDDataChecked(bool state);

private:
 void setUpImage(std::string imageName, QLabel *label);
 void uncheckAllButtons();
 void initializeImages();
 void initializeDataSources(VAPoR::ControlExec* ce);

 static const std::string barbDescription;
 static const std::string contourDescription;
 static const std::string imageDescription;
 static const std::string twoDDataDescription;

 std::string _selectedRenderer;
};

class CBWidget : public QWidget, public QTableWidgetItem {
public:
	CBWidget(QWidget* parent, QString type);
};

//! \class RenderHolder
//! \ingroup Public_GUI
//! \brief A class that manages the display of Renderer parameters
//! \author Alan Norton
//! \version 3.0
//! \date April 2015

//! This is class manages a QTableWidget that indicates the currently 
//! available Renderers, and a
//! QStackedWidget that displays the various parameters associated 
//! with the selected renderer.
//!
class RenderHolder : public QWidget, public Ui_LeftPanel {

	Q_OBJECT

public: 

 //! Constructor:  
 //
 RenderHolder(QWidget *parent, VAPoR::ControlExec *ce);

 virtual ~RenderHolder() {}

 //! Make the tableWidget match the currently displayed RenderParams
 //!
 void Update();

 //! Specify the index of the page to be displayed of the stackedWidget.
 //! \param[in] indx page index
 void SetCurrentIndex(int indx){
	stackedWidget->setCurrentIndex(indx);
	stackedWidget->show();
 }

 //! Add a widget (EventRouter) to the QStackedWidget. 
 //! \param[in] QWidget* Widget to be added
 //! \param[in] name Name of the renderer to be displayed
 //! \param[in] tag indicating type of renderer to be displayed
 //! \return index of widget in the stackedWidget
 int AddWidget(QWidget*, const char* name, string tag);

#ifndef DOXYGEN_SKIP_THIS
private:

 RenderHolder() {}

 GUIStateParams *getStateParams() const {
	assert(_controlExec != NULL);
	return (
		(GUIStateParams *) _controlExec->
		GetParamsMgr()->GetParams(GUIStateParams::GetClassType())
	);
 }

 void updateDupCombo();
 void makeRendererTableHeaders(vector<string> &table);
 void initializeNewRendererDialog(vector<string> datasetNames);

 //Convert name to a unique name (among renderer names)
 std::string uniqueName(std::string name);

private slots:
 void showNewRendererDialog();
 void deleteRenderer();
 void itemTextChange(QTableWidgetItem*);
 void copyInstanceTo(int);
 void activeRendererChanged(int row, int col);
 void tableValueChanged(int row, int col);

signals:
 void newRendererSignal(string vizName, string renderClass, string renderInst);
 void activeChanged(string vizName, string renderClass, string renderInst);
 
private:
 VAPoR::ControlExec *_controlExec;
 NewRendererDialog *_newRendererDialog;

 VaporTable *_vaporTable;
 int _currentRow;

 void getRow(
	int row, string &renderInst, string &renderClass, 
	string &dataSetName
 ) const;

 void makeConnections();
 void clearStackedWidget();
 void initializeSplitter();
 string getActiveRendererClass();
 string getActiveRendererInst();
 void highlightActiveRow(int row);
 void changeRendererName(int row, int col);
 VAPoR::RenderParams* getRenderParamsFromCell(int row, int col);

#endif //DOXYGEN_SKIP_THIS
};

#endif //RENDERHOLDER_H 
