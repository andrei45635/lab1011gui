#include "offergui.h"

void OfferGUI::initGUIfields() {
	setLayout(hLay);
	setLayout(vLay);
	QWidget* windLeft = new QWidget();
	QVBoxLayout* leftLayout = new QVBoxLayout();
	windLeft->setLayout(leftLayout);
	leftLayout->addWidget(offer_list);
	leftLayout->addWidget(btnFiltDest);
	leftLayout->addWidget(btnFiltPrice);
	hLay->addWidget(windLeft);
	QWidget* wind_det = new QWidget();
	wind_det->setLayout(formLayout);
	formLayout->addRow(new QLabel("Denumire"), denumire_txt);
	formLayout->addRow(new QLabel("Destination"), destinatie_txt);
	formLayout->addRow(new QLabel("Type"), type_txt);
	formLayout->addRow(new QLabel("Price"), price_txt);
	formLayout->addRow(new QLabel("Destination to filter"), filter_dest);
	formLayout->addRow(new QLabel("Price to filter"), filter_price);
	hLay->addLayout(vLay);
	vLay->addWidget(wind_det);
	vLay->addWidget(btnAdd);
	vLay->addWidget(btnDel);
	vLay->addWidget(btnModify);
}

void OfferGUI::updateList(QListWidget* lst) {
	offer_list->clear();
	for (const auto& ofr : serv.getAllService()) {
		QString string = QString::fromStdString(ofr.toString());
		QListWidgetItem* item = new QListWidgetItem(string, lst);
	}
}

void OfferGUI::addOfferGUI() {
	try {
		serv.addServiceOffer(denumire_txt->text().toStdString(), destinatie_txt->text().toStdString(), type_txt->text().toStdString(), price_txt->text().toDouble());
		updateList(offer_list);
	}
	catch (RepoException& msg) {
		QMessageBox::critical(this, "Eroare critica!", QString::fromStdString(msg.getMessage()));
	}
	catch (ValidException& msg) {
		QMessageBox::critical(this, "Eroare critica!", QString::fromStdString(msg.get_msg()));
	}
}

void OfferGUI::delOfferGUI() {
	try {
		Offer ofr{ denumire_txt->text().toStdString(), destinatie_txt->text().toStdString(), type_txt->text().toStdString(), price_txt->text().toDouble() };
		serv.deleteServiceForUndo(ofr);
		updateList(offer_list);
	}
	catch (RepoException& msg) {
		QMessageBox::critical(this, "Eroare critica!", QString::fromStdString(msg.getMessage()));
	}
}

void OfferGUI::filtDestGUI() {
	QDialog* dlg = new QDialog();
	QListWidget* dlgList = new QListWidget();
	QHBoxLayout* hDlg = new QHBoxLayout();
	dlg->setModal(true);
	hDlg->addWidget(dlgList);
	dlg->setLayout(hDlg);
	dlgList->clear();
	try {
		const auto& filtered = serv.filtrare_dest(filter_dest->text().toStdString());
		for (const auto& ofr : filtered) {
			QString string = QString::fromStdString(ofr.toString());
			QListWidgetItem* item = new QListWidgetItem(string, dlgList);
		}
	}
	catch (ValidException& msg) {
		QMessageBox::critical(this, "Eroare critica!", QString::fromStdString(msg.get_msg()));
	}
	catch (RepoException& msg) {
		QMessageBox::critical(this, "Eroare critica!", QString::fromStdString(msg.getMessage()));
	}
	dlg->exec();
	updateList(dlgList);
	updateList(offer_list);
}

void OfferGUI::filtPriceGUI() {
	QDialog* dlg = new QDialog();
	QListWidget* dlgList = new QListWidget();
	QHBoxLayout* hDlg = new QHBoxLayout();
	dlg->setModal(true);
	hDlg->addWidget(dlgList);
	dlg->setLayout(hDlg);
	dlgList->clear();
	try {
		const auto& filtered = serv.filtrare_pret(filter_price->text().toInt());
		for (const auto& ofr : filtered) {
			QString string = QString::fromStdString(ofr.toString());
			QListWidgetItem* item = new QListWidgetItem(string, dlgList);
		}
	}
	catch (ValidException& msg) {
		QMessageBox::critical(this, "Eroare critica!", QString::fromStdString(msg.get_msg()));
	}
	catch (RepoException& msg) {
		QMessageBox::critical(this, "Eroare critica!", QString::fromStdString(msg.getMessage()));
	}
	dlg->exec();
	updateList(dlgList);
	updateList(offer_list);
}

void OfferGUI::on_click_add() {
	QObject::connect(btnAdd, &QPushButton::clicked, this, &OfferGUI::addOfferGUI);
}

void OfferGUI::on_click_del() {
	QObject::connect(btnDel, &QPushButton::clicked, this, &OfferGUI::delOfferGUI);
}

void OfferGUI::on_click_filter_dest() {
	QObject::connect(btnFiltDest, &QPushButton::clicked, this, &OfferGUI::filtDestGUI);
}

void OfferGUI::on_click_filter_price() {
	QObject::connect(btnFiltPrice, &QPushButton::clicked, this, &OfferGUI::filtPriceGUI);
}