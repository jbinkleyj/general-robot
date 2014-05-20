#ifndef HCSR04_H
#define HCSR04_H
// Constants definition
#define MAX_DISTANCE 200

#define AVERAGE_TIMES 3

// Error codes definition
#define E_INVALID_DISTANCE -1


class HcSr04 {
    private:
        int _echoPin;
        int _triggerPin;

    public:
        HcSr04(int echoPin, int triggerPin);
        long read_distance();

};
#endif
