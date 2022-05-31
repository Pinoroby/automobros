#include "ControlSystem.hpp"

ControlSystem::ControlSystem(double dt)
    : myConstant(1.0), myGain1(2.0), myGain2(2.0), limit(0, 1)
    myEncoder1("enc1"),
    myEncoder2("enc2"),
    myMotor1("motor1"),
    myMotor1("motor2"),
    timedomain("Main time domain", dt, true)
{

    // Generate some Variables
    double lowLimit = 0;
    double upLimit = 700;
    double i = 33.086538461;
    double ohm = 8;
    double km = 8.44/1000;
    double maxSpeed = 21.2;

    // Name all blocks
    myEncoder1.setName("My Encoder 1");
    myEncoder2.setName("My Encoder 2");
    myMotor1.setName("My Motor 1");
    myMotor2.setName("My Motor 2");
    myGain1.setName("My Gain 1");
    myGain2.setName("My Gain 2");
    myGain2.setName("My Gain 3");

    // Name all signals
    //myIMS.getOut().getSignal().setName("Angle in Rad");
    myEncoder1.getOut().getSignal().setName("Angle in rad");
    myEncoder2.getOut().getSignal().setName("Angle in rad")

    myGain1.setGain(maxSpeed/2/M_PI);
    limit.setLimit(lowLimit, upLimit);
    myGain2.setGain(i);
    myGain3.setGain(km);

    //Make some Calculations

    // Connect signals

    myGain1.getIn().connect(myEncoder1.getOut());
    limit.getIn().connect(myGain1.getOut());
    myGain2.getIn().connect(limit.getOut());
    myGain3.getIn().connect(myGain2.getOut());
    myMotor2.getIn().connect(myGain3.getOut());

    // Add blocks to timedomain
    timedomain.addBlock(myGain1);
    timedomain.addBlock(limit);
    timedomain.addBlock(myGain2);
    timedomain.addBlock(myGain3);
    timedomain.addBlock(myMotor2);

    // Add timedomain to executor
    eeros::Executor::instance().add(timedomain);
}