#pragma once
#include "qwidget.h"
#include "qlabel.h"
#include "qpushbutton.h"
#include "offer_service.h"
#include "qlineedit.h"
#include "qlistwidget.h"
#include "qboxlayout.h"
#include "qformlayout.h"
#include "qmessagebox.h"

class OfferGUI : public QWidget {
private:
	ServiceOffer& serv;
	QWidget* window = new QWidget();
	QHBoxLayout* hLay = new QHBoxLayout(window);
	QVBoxLayout* vLay = new QVBoxLayout(window);
	QFormLayout* formLayout = new QFormLayout();
	QPushButton* btnAdd = new QPushButton("Add");
	QPushButton* btnDel = new QPushButton("Delete");
	QPushButton* btnModify = new QPushButton("Modify");
	QPushButton* btnFiltDest = new QPushButton("Destination Filter");
	QPushButton* btnFiltPrice = new QPushButton("Price Filter");
	QLineEdit* denumire_txt = new QLineEdit();
	QLineEdit* destinatie_txt = new QLineEdit();
	QLineEdit* type_txt = new QLineEdit();
	QLineEdit* price_txt = new QLineEdit();
	QLineEdit* filter_dest = new QLineEdit();
	QLineEdit* filter_price = new QLineEdit();
	QListWidget* offer_list = new QListWidget();

	void addOfferGUI();
	void delOfferGUI();
	void modifyOfferGUI();
	void filtDestGUI();
	void filtPriceGUI();
	void on_click_add();
	void on_click_del();
	void on_click_filter_dest();
	void on_click_filter_price();
	void initGUIfields();
	void updateList(QListWidget* lst);

public:
	OfferGUI(ServiceOffer& serv) : serv{ serv } {
		initGUIfields();
		on_click_add();
		on_click_del();
		on_click_filter_dest();
		on_click_filter_price();
		updateList(offer_list);
	}
};
