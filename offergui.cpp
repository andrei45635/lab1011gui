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
	leftLayout->addWidget(btnSearch);
	leftLayout->addWidget(btnSortDen);
	leftLayout->addWidget(btnSortDest);
	leftLayout->addWidget(btnSortTypePrice);
	hLay->addWidget(windLeft);
	QWidget* wind_det = new QWidget();
	wind_det->setLayout(formLayout);
	formLayout->addRow(new QLabel("Denumire"), denumire_txt);
	formLayout->addRow(new QLabel("Destination"), destinatie_txt);
	formLayout->addRow(new QLabel("Type"), type_txt);
	formLayout->addRow(new QLabel("Price"), price_txt);
	formLayout->addRow(new QLabel("Destination to filter"), filter_dest);
	formLayout->addRow(new QLabel("Price to filter"), filter_price);
	formLayout->addRow(new QLabel("Position to find"), position_of_offer);
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

void OfferGUI::updateWish(QListWidget* wishlst) {
	wishlist->clear();
	for (const auto& wsh : serv.get_all_from_wish()) {
		QString string = QString::fromStdString(wsh.toString());
		QListWidgetItem* item = new QListWidgetItem(string, wishlst);
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

void OfferGUI::searchOfferGUI() {
	QDialog* dlg = new QDialog();
	QVBoxLayout* vdlg = new QVBoxLayout();
	QLabel* lblOffer = new QLabel();
	dlg->setModal(true);
	vdlg->addWidget(lblOffer);
	dlg->setLayout(vdlg);
	auto offer = serv.findOfferService(position_of_offer->text().toInt());
	lblOffer->setText(QString::fromStdString(offer.toString()));
	dlg->exec();
	updateList(offer_list);
}

void OfferGUI::modifyOfferGUI() {
	QDialog* dlg = new QDialog();
	QVBoxLayout* vdlg = new QVBoxLayout();
	QVBoxLayout* vdlg1 = new QVBoxLayout();
	QFormLayout* formDlg = new QFormLayout();
	QPushButton* modOffer = new QPushButton("Modify!");
	dlg->setModal(true);
	vdlg1->addWidget(modOffer);
	formDlg->addRow(new QLabel("New name"), new_denum);
	formDlg->addRow(new QLabel("New destination"), new_dest);
	formDlg->addRow(new QLabel("New type"), new_type);
	formDlg->addRow(new QLabel("New price"), new_price);
	vdlg1->addLayout(vdlg);
	vdlg->addLayout(formDlg);
	dlg->setLayout(vdlg1);
	try {
		QObject::connect(modOffer, &QPushButton::clicked, this, &OfferGUI::modGUI);
		updateList(offer_list);
	}
	catch (ValidException& msg) {
		QMessageBox::critical(this, "Eroare la validare!", QString::fromStdString(msg.get_msg()));
	}
	dlg->exec();
}

void OfferGUI::modGUI() {
	Offer old_ofr{ denumire_txt->text().toStdString(), destinatie_txt->text().toStdString(), type_txt->text().toStdString(), price_txt->text().toDouble() };
	Offer new_ofr{ new_denum->text().toStdString(), new_dest->text().toStdString(), new_type->text().toStdString(), new_price->text().toDouble() };
	serv.modifyServiceForUndo(old_ofr, new_ofr);
}

void OfferGUI::sortDenumGUI() {
	const auto& sorted = serv.sortDenumire();
	offer_list->clear();
	for (const auto& srt : sorted) {
		QString string = QString::fromStdString(srt.toString());
		QListWidgetItem* item = new QListWidgetItem(string, offer_list);
	}
}

void OfferGUI::sortDestGUI() {
	const auto& sorted = serv.sortDest();
	offer_list->clear();
	for (const auto& srt : sorted) {
		QString string = QString::fromStdString(srt.toString());
		QListWidgetItem* item = new QListWidgetItem(string, offer_list);
	}
}

void OfferGUI::sortTypePriceGUI() {
	//const auto& sorted = serv.sortFinal();
	const auto& sorted = serv.sorted();
	offer_list->clear();
	for (const auto& srt : sorted) {
		QString string = QString::fromStdString(srt.toString());
		QListWidgetItem* item = new QListWidgetItem(string, offer_list);
	}
}

void OfferGUI::createWishlistGUI() {
	wish->setLayout(vLayWish);
	vLayWish->addWidget(wishlist);
	vLayWish->addLayout(formLayoutWish);
	formLayoutWish->addRow(new QLabel("Destination"), wish_dest);
	formLayoutWish->addRow(new QLabel("Random generator"), randomNumber);
	formLayoutWish->addRow(new QLabel("File name (add .html)"), fileName);
	vLayWish->addWidget(btnAddWishlist);
	vLayWish->addWidget(btnDelWishlist);
	vLayWish->addWidget(btnRandomWishlist);
	vLayWish->addWidget(btnExportHTML);
	wish->show();
}

void OfferGUI::addWishlistGUI() {
	try {
		serv.add_to_wishlist(wish_dest->text().toStdString());
		updateWish(wishlist);
		updateList(offer_list);
	}
	catch (WishExcept& msg) {
		QMessageBox::critical(this, "Eroare!", QString::fromStdString(msg.getMessage()));
	}
}

void OfferGUI::delWishlistGUI() {
	wishlist->clear();
}

void OfferGUI::randomWishlistGUI() {
	try {
		serv.generate_random_offers(randomNumber->text().toInt());
		updateWish(wishlist);
		updateList(offer_list);
	}
	catch (WishExcept& msg) {
		QMessageBox::critical(this, "Eroare!", QString::fromStdString(msg.getMessage()));
	}
	catch (ValidException& msg) {
		QMessageBox::critical(this, "Eroare critica!", QString::fromStdString(msg.get_msg()));
	}
	catch (RepoException& msg) {
		QMessageBox::critical(this, "Eroare critica!", QString::fromStdString(msg.getMessage()));
	}
}

void OfferGUI::exportHTMLGUI() {
	try {
		serv.exporta_cos_HTML(fileName->text().toStdString());
	}
	catch (RepoException& msg) {
		QMessageBox::critical(this, "Eroare critica!", QString::fromStdString(msg.getMessage()));
	}
	QMessageBox::information(wish, "Success!", QString::fromStdString("Successfully exported!"));
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

void OfferGUI::on_click_search() {
	QObject::connect(btnSearch, &QPushButton::clicked, this, &OfferGUI::searchOfferGUI);
}

void OfferGUI::on_click_modify() {
	QObject::connect(btnModify, &QPushButton::clicked, this, &OfferGUI::modifyOfferGUI);
}

void OfferGUI::on_click_sort_denum() {
	QObject::connect(btnSortDen, &QPushButton::clicked, this, &OfferGUI::sortDenumGUI);
}

void OfferGUI::on_click_sort_dest() {
	QObject::connect(btnSortDest, &QPushButton::clicked, this, &OfferGUI::sortDestGUI);
}

void OfferGUI::on_click_sort_type_price() {
	QObject::connect(btnSortDest, &QPushButton::clicked, this, &OfferGUI::sortTypePriceGUI);
}

void OfferGUI::on_click_add_wishlist() {
	QObject::connect(btnAddWishlist, &QPushButton::clicked, this, &OfferGUI::addWishlistGUI);
}

void OfferGUI::on_click_del_wishlist() {
	QObject::connect(btnDelWishlist, &QPushButton::clicked, this, &OfferGUI::delWishlistGUI);
}

void OfferGUI::on_click_random_wishlist() {
	QObject::connect(btnRandomWishlist, &QPushButton::clicked, this, &OfferGUI::randomWishlistGUI);
}

void OfferGUI::on_click_export_HTML() {
	QObject::connect(btnExportHTML, &QPushButton::clicked, this, &OfferGUI::exportHTMLGUI);
}