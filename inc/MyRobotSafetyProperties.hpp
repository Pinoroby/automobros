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

    eeros::safety::SafetyEvent doInitialising;
    eeros::safety::SafetyEvent doReleaseError;
    eeros::safety::SafetyEvent doInitToMotorOff;
    eeros::safety::SafetyEvent doMotorOn;
    eeros::safety::SafetyEvent doMove;
    eeros::safety::SafetyEvent doGrasping;
    eeros::safety::SafetyEvent doEmergency;
    eeros::safety::SafetyEvent doRobotStop;
    eeros::safety::SafetyEvent doGraspingStop;
    eeros::safety::SafetyEvent doShutDown;
    eeros::safety::SafetyEvent doDebug;

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
