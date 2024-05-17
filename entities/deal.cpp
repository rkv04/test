#include "deal.h"

Deal::Deal() {
    this->id = -1;
    this->id_ticket = -1;
    this->ticket = nullptr;
    this->id_client = -1;
    this->quantity = -1;
    this->discount = -1;
    this->deal_sum = -1;
    this->date = QString();
}
