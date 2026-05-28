#ifndef LOGENTRY_H
#define LOGENTRY_H

#include <string>

class LogEntry {
protected:
    std::string date;
    std::string notes;

public:
    LogEntry(const std::string& d, const std::string& n)
        : date(d), notes(n) {}
    
    virtual ~LogEntry() = default;

    std::string getDate() const { return date; }
    std::string getNotes() const { return notes; }

    virtual int getCalories() const = 0;
    virtual void displayDetails() const = 0;
    virtual std::string serialize() const = 0;
};

#endif // LOGENTRY_H
