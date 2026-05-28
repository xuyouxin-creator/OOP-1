#ifndef RENTALRECORD_H
#define RENTALRECORD_H

#include <string>

class RentalRecord {
public:
    std::string rentalId;
    std::string username;
    std::string itemId;
    std::string rentDate;
    std::string dueDate;
    bool isReturned;

    RentalRecord(const std::string& rId, const std::string& uName, const std::string& iId, 
                 const std::string& rDate, const std::string& dDate, bool ret)
        : rentalId(rId), username(uName), itemId(iId), rentDate(rDate), dueDate(dDate), isReturned(ret) {}

    std::string serialize() const;
};

#endif // RENTALRECORD_H
