#include "ControlSystem.hpp"

ControlSystem::ControlSystem(double dt)
    : myConstant(1.0), myGain(2.0),
    myIMS("quat1"),
    myServo("servo1"),
    timedomain("Main time domain", dt, true)
{
    // Name all blocks
    myGain.setName("My gain");
    myIMS.setName("My IMS Input");
    myServo.setName("My Servo Output");

    // Name all signals
    //myIMS.getOut().getSignal().setName("Angle in Rad");
    myServo.getOut().getSignal().setName("Angle in Rad");
    myGain.getOut().getSignal().setName("Gain");

    myGain.setGain(1);

    // Connect signals
    myIMS.getIn().connect(myGain.getOut());
    myGain.getIn().connect(myServo.getOut());

    // Add blocks to timedomain
    timedomain.addBlock(myGain);
    timedomain.addBlock(myIMS);
    timedomain.addBlock(myServo);

    // Add timedomain to executor
    eeros::Executor::instance().add(timedomain);
}