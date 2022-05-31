#ifndef CONTROLSYSTEM_HPP_
#define CONTROLSYSTEM_HPP_

#include <eeros/control/TimeDomain.hpp>
#include <eeros/core/Executor.hpp>
#include <eeros/control/Constant.hpp>
#include <eeros/control/Gain.hpp>
#include <eeros/control/I.hpp>
#include <eeros/control/PeripheralInput.hpp>
#include <eeros/control/PeripheralOutput.hpp>
#include <eeros/control/Saturation.hpp>

using namespace eeros::control;

class ControlSystem
{
public:
    ControlSystem(double dt);

    // Define Blocks
    Constant<> myConstant;
    Gain<> myGain1;
    Gain<> myGain2;
    Gain<> myGain3;

    Saturation<double> limit;

    PeripheralOutput<double> myMotor1;
    PeripheralInput<double> myEncoder1;

    PeripheralOutput<double> myMotor2;
    PeripheralInput<double> myEncoder2;

    TimeDomain timedomain;
};

#endif // CONTROLSYSTEM_HPP