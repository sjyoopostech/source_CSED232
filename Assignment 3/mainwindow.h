#ifndef MAINWINDOW_H
#define MAINWINDOW_H

// included header & libraries
#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
	//constructor & destructor
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
	
private slots:
	// button click functions
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
	
private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
