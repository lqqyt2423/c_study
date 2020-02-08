#include "quote.h"
#include <iostream>

using std::ostream;
using std::endl;

double print_total(ostream &os, const Quote &item, size_t n) {
	double ret = item.net_price(n);
	os << "ISBN: " << item.isbn()
		<< " # sold: " << n << " total due: " << ret << endl;
	return ret;
}

double Bulk_quote::net_price(size_t cnt) const {
	if (cnt >= min_qty)
		return cnt * (1 - discount) * price;
	else
		return cnt * price;
}
