#include "oferta.h"
#include <cassert>
#include <string>
#include <cmath>
#include <iostream>

string Offer::getDenumire() const {
	return denum;
}

string Offer::getDestinatie() const {
	return dest;
}

string Offer::getType() const {
	return type;
}

double Offer::getPrice() const {
	return price;
}

string Offer::toString() const {
	return "Denumirea ofertei: " + denum + ", destinatia: " + dest + ", tipul: " + type + ", pretul: " + std::to_string(price);
}

void testCreateOffer() {
	string denum = "Familie";
	string dest = "Kiev";
	string type = "Roadtrip";
	double price = 69;
	Offer ofr{ denum, dest, type, price };
	assert(ofr.getDenumire() == denum);
	assert(ofr.getDestinatie() == dest);
	assert(ofr.getType() == type);
	assert(fabs(ofr.getPrice() - price) < 0.00001);
}