#ifndef MyRobotSAFETYPROPERTIES_HPP_
#define MyRobotSAFETYPROPERTIES_HPP_

#include <eeros/safety/SafetyProperties.hpp>
#include <eeros/hal/HAL.hpp>
#include "ControlSystem.hpp"

class MyRobotSafetyProperties : public eeros::safety::SafetyProperties
{
public:
    MyRobotSafetyProperties(ControlSystem &cs, double dt);

    // Defina all possible levels

    eeros::safety::SafetyLevel slPowerOff;
    eeros::safety::SafetyLevel slError;
    eeros::safety::SafetyLevel slInitialising;
    eeros::safety::SafetyLevel slMotorPowerOff;
    eeros::safety::SafetyLevel slTesting;
    eeros::safety::SafetyLevel slMotorPowerOn;
    eeros::safety::SafetyLevel slMoving;
    eeros::safety::SafetyLevel slGrasping;

    // Define all possible events

    eeros::safety::SafetyLevel doInitialising;
    eeros::safety::SafetyLevel doReleaseError;
    eeros::safety::SafetyLevel doInitToMotorOff;
    eeros::safety::SafetyLevel doMotorOn;
    eeros::safety::SafetyLevel doMove;
    eeros::safety::SafetyLevel doGrasping;
    eeros::safety::SafetyLevel doEmergency;

private:
    // Define all critical outputs
    eeros::hal::Output<bool>* greenLED;
    eeros::hal::Output<bool>* redLED;

    // Define all critical inputs
    eeros::hal::Input<bool>* emergency;
    eeros::hal::Input<bool>* debug;

    ControlSystem &cs;
};

#endif // MyRobotSAFETYPROPERTIES_HPP_
