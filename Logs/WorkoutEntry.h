#ifndef WORKOUTENTRY_H
#define WORKOUTENTRY_H

#include "LogEntry.h"

class WorkoutEntry : public LogEntry {
private:
    std::string exerciseType;
    int durationMin;
    int caloriesBurned;

public:
    WorkoutEntry(const std::string& d, const std::string& n, const std::string& eType, int dur, int cal)
        : LogEntry(d, n), exerciseType(eType), durationMin(dur), caloriesBurned(cal) {}

    std::string getExerciseType() const { return exerciseType; }
    int getDurationMin() const { return durationMin; }

    int getCalories() const override { return -caloriesBurned; } // Burned calories are negative in sum
    void displayDetails() const override;
    std::string serialize() const override;
};

#endif // WORKOUTENTRY_H
