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
	QWidget* wish = new QWidget();
	QWidget* window = new QWidget();
	QHBoxLayout* hLay = new QHBoxLayout(window);
	QVBoxLayout* vLay = new QVBoxLayout(window);
	QVBoxLayout* vLayWish = new QVBoxLayout();
	QFormLayout* formLayout = new QFormLayout();
	QFormLayout* formLayoutWish = new QFormLayout();
	QPushButton* btnAdd = new QPushButton("Add");
	QPushButton* btnDel = new QPushButton("Delete");
	QPushButton* btnModify = new QPushButton("Modify");
	QPushButton* btnFiltDest = new QPushButton("Destination Filter");
	QPushButton* btnFiltPrice = new QPushButton("Price Filter");
	QPushButton* btnSearch = new QPushButton("Search for an Offer");
	QPushButton* btnSortDen = new QPushButton("Sort by name");
	QPushButton* btnSortDest = new QPushButton("Sort by destination");
	QPushButton* btnSortTypePrice = new QPushButton("Sort by type and price");
	QPushButton* btnAddWishlist = new QPushButton("Add to the wishlist");
	QPushButton* btnDelWishlist = new QPushButton("Delete from wishlist");
	QPushButton* btnRandomWishlist = new QPushButton("Generate random offers");
	QLineEdit* denumire_txt = new QLineEdit();
	QLineEdit* destinatie_txt = new QLineEdit();
	QLineEdit* type_txt = new QLineEdit();
	QLineEdit* price_txt = new QLineEdit(); 
	QLineEdit* new_denum = new QLineEdit();
	QLineEdit* new_dest = new QLineEdit();
	QLineEdit* new_type = new QLineEdit();
	QLineEdit* new_price = new QLineEdit();
	QLineEdit* wish_dest = new QLineEdit();
	QLineEdit* filter_dest = new QLineEdit();
	QLineEdit* filter_price = new QLineEdit();
	QLineEdit* position_of_offer = new QLineEdit();
	QListWidget* offer_list = new QListWidget();
	QListWidget* wishlist = new QListWidget();

	void addOfferGUI();
	void delOfferGUI();
	void modifyOfferGUI();
	void modGUI(); //TODO
	void searchOfferGUI();
	void filtDestGUI();
	void filtPriceGUI();
	void sortDenumGUI();
	void sortDestGUI();
	void sortTypePriceGUI();
	void createWishlistGUI();
	void on_click_add();
	void on_click_del();
	void on_click_filter_dest();
	void on_click_filter_price();
	void on_click_search();
	void on_click_modify();
	void on_click_sort_denum();
	void on_click_sort_dest();
	void on_click_sort_type_price();
	void initGUIfields();
	void updateList(QListWidget* lst);

public:
	OfferGUI(ServiceOffer& serv) : serv{ serv } {
		initGUIfields();
		createWishlistGUI();
		on_click_add();
		on_click_del();
		on_click_filter_dest();
		on_click_filter_price();
		on_click_search();
		on_click_modify();
		on_click_sort_denum();
		on_click_sort_dest();
		on_click_sort_type_price();
		updateList(offer_list);
	}
};
