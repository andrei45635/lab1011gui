#include "lab1011gui.h"
#include "stdafx.h"
#include "offergui.h"
//#include "UI.h"
#include "offer_service.h"
#include <iostream>
#include <QtWidgets/QApplication>

void runAllTests() {
	std::cout << "beginning testing..." << std::endl;
	testCreateOffer();
	test_create_repo();
	test_delete_repo();
	test_modify_repo();
	test_find_repo();
	testCreateService();
	testDeleteOfferService();
	testModifyOfferService();
	testFindOfferService();
	testFilters();
	testSorts();
	testAddCart();
	testDeleteFromCart();
	testGenerateRandom();
	testAddToWish();
	testDeleteWish();
	testGenerateWish();
	testUndo();
	std::cout << "finished testing..." << std::endl;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    lab1011gui w;
	runAllTests();
	OfferValidator valid;
	RepoOffer repo;
	//FileRepoOffer file_repo("oferte.txt");
	Wishlist wish;
	ServiceOffer serv(repo, valid);
	//UI ui(serv);
	//ui.startUI();
	auto gui = OfferGUI(serv);
	gui.move(200, 10);
	gui.show();
	auto gui2 = OfferGUI(serv);
	gui2.move(300, 10);
	gui2.show();
	auto gui3 = OfferGUI(serv);
	gui3.move(400, 10);
	gui3.show();
    return a.exec();
}
