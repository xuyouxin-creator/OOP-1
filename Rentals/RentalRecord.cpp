#include "RentalRecord.h"
#include <sstream>

std::string RentalRecord::serialize() const {
    // Format: rentalId,username,itemId,rentDate,dueDate,isReturned
    std::stringstream ss;
    ss << rentalId << "," << username << "," << itemId << "," << rentDate << "," << dueDate << "," << (isReturned ? "true" : "false");
    return ss.str();
}
