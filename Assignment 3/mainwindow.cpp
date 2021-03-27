#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "bio.h"
#include "cell.h"
#include "enemy.h"
#include "virus.h"
#include "feed.h"

using namespace Qt;

// constructor
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

// destructor
MainWindow::~MainWindow()
{
    delete ui;
}

// when start button clicked
void MainWindow::on_pushButton_clicked()
{
	// hide mainWindow
    this->hide();
	
    // scene
    QGraphicsScene* scene = new QGraphicsScene();
    scene->setSceneRect(0, 0, 800, 800);

	// get rgb from horizontal sliders
    int r = 255 - (ui->horizontalSlider->value())*2.55;
    int g = 255 - (ui->horizontalSlider_2->value())*2.55;
    int b = 255 - (ui->horizontalSlider_3->value())*2.55;

    // view
    QGraphicsView* view = new QGraphicsView(scene);
    view->setHorizontalScrollBarPolicy(ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(ScrollBarAlwaysOff);
    view->setFixedSize(800, 800);
    view->setBackgroundBrush(QBrush(QColor(r, g, b), Qt::SolidPattern));
    view->show();

	// make player
    Bio* player = new Cell();
    scene->addItem(player);

	// make objects
    Bio* object[30];
    for (int i = 0; i < 30; i++) {
        int r = rand() % 100;
        if (r < 70) {
            object[i] = new Feed();
        }
        else if (r < 85) {
            object[i] = new Virus();
        }
        else {
            object[i] = new Enemy();
        }
        scene->addItem(object[i]);
    }
}

// when quit button clicked
void MainWindow::on_pushButton_2_clicked()
{
    exit(0);
}
