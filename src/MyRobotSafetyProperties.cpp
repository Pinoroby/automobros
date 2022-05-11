#include "MyRobotSafetyProperties.hpp"

MyRobotSafetyProperties::MyRobotSafetyProperties(ControlSystem &cs, double dt)
    : cs(cs),
    
      slPowerOff("System is offline"),
      slError("System has an Error"),
      slInitialising("Initialising"),
      slMotorPowerOff("Motor are Powered off!"),
      slTesting("Debug Mode"),
      slMotorPowerOn("Motor are Powered on!"),
      slMoving("Roboter is Moving"),
      slGrasping("Motor is Grasping"),

      doInitialising("Startup the System..."),
      doReleaseError("Clearing Error...."),
      doInitToMotorOff("Init to Motor..."),
      doMotorOn("Turning ON Motors..."),
      doMove("Robot is Moving..."),
      doGrasping("Robot is Grasping..."),
      doEmergency("Emergency!!! Entering Error State..."),
      doRobotStop("Robot is stopping..."),
      doGraspingStop("Robot is not gripping..."),
      doShutDown("Robot is powering off...."),
      doDebug("Entering Debug Mode....")
{
    eeros::hal::HAL &hal = eeros::hal::HAL::instance();

    // Declare and add critical outputs
     greenLED = hal.getLogicOutput("onBoardLEDgreen");
     redLED = hal.getLogicOutput("onBoardLEDred");

    criticalOutputs = { greenLED, redLED };

    // Declare and add critical inputs
    emergency = eeros::hal::HAL::instance().getLogicInput("onBoardButtonPause");
    debug = eeros::hal::HAL::instance().getLogicInput("onBoardButtonMode");

    criticalInputs = { emergency, debug };

    // Add all safety levels to the safety system
    addLevel(slPowerOff);
    addLevel(slError);
    addLevel(slInitialising);
    addLevel(slMotorPowerOff);
    addLevel(slTesting);
    addLevel(slMotorPowerOn);
    addLevel(slMoving);
    addLevel(slGrasping);

    // Add events to individual safety levels
    
    // slSystemOff.addEvent(doSystemOn, slSystemOn, kPublicEvent);
    slPowerOff.addEvent(doInitialising, slInitialising, kPublicEvent);
    slInitialising.addEvent(doInitToMotorOff, slMotorPowerOff, kPublicEvent);
    slMotorPowerOff.addEvent(doMotorOn, slMotorPowerOn, kPublicEvent);
    slMotorPowerOn.addEvent(doMove, slMoving, kPublicEvent);
    
    slMoving.addEvent(doRobotStop, slMotorPowerOn, kPublicEvent);

    slMotorPowerOn.addEvent(doGrasping, slGrasping, kPublicEvent);

    slGrasping.addEvent(doGraspingStop, slMotorPowerOn, kPublicEvent);

    
    // Add events to multiple safety levels
    addEventToAllLevelsBetween(slInitialising, slGrasping, doEmergency, slError, kPublicEvent);
    addEventToAllLevelsBetween(slMotorPowerOff, slGrasping, doShutDown, slPowerOff, kPublicEvent);
    addEventToAllLevelsBetween(slMotorPowerOn, slGrasping, doDebug, slTesting, kPublicEvent);

    // Define input actions for all levels
    //level.setInputActions({ ... });
    slPowerOff.setInputActions({ignore(emergency), ignore(debug)});
    slError.setInputActions({ignore(emergency), ignore(debug)});
    slInitialising.setInputActions({ignore(emergency), ignore(debug)});
    slTesting.setInputActions({check(emergency, false, doEmergency), ignore(debug)});
    slMotorPowerOff.setInputActions({check(emergency, false, doEmergency), ignore(debug)});
    slMotorPowerOn.setInputActions({check(emergency, false, doEmergency), check(debug, false, doDebug)});
    slMoving.setInputActions({check(emergency, false, doEmergency), check(debug, false, doDebug)});
    slGrasping.setInputActions({check(emergency, false, doEmergency), check(debug, false, doDebug)});


    // Define output actions for all levels
    slPowerOff.setOutputActions({   set(greenLED, false), set(redLED, false)});
    slError.setOutputActions({      set(greenLED, false), set(redLED, true)});
    slInitialising.setOutputActions({set(greenLED, false), set(redLED, true)});
    slTesting.setOutputActions({    set(greenLED, true), set(redLED, true)});
    slMotorPowerOff.setOutputActions({set(greenLED, true), set(redLED, false)});
    slMotorPowerOn.setOutputActions({set(greenLED, true), set(redLED, false)});
    slMoving.setOutputActions(      {set(greenLED, true), set(redLED, false)});
    slGrasping.setOutputActions(    {set(greenLED, true), set(redLED, false)});


    // Define and add level actions
    slPowerOff.setLevelAction([&](SafetyContext *privateContext) {
        eeros::Executor::stop();
    });

    slError.setLevelAction([&](SafetyContext *privateContext) {
    
    });

    slInitialising.setLevelAction([&](SafetyContext *privateContext) {
        cs.timedomain.start();
        privateContext->triggerEvent(doInitToMotorOff);
    });


    slTesting.setLevelAction([&](SafetyContext *privateContext) {
        cs.timedomain.start();
    
    });


    slMotorPowerOff.setLevelAction([&](SafetyContext *privateContext) {
        cs.timedomain.start();
        privateContext->triggerEvent(doMotorOn);
    });

    slMotorPowerOn.setLevelAction([&](SafetyContext *privateContext) {
        cs.timedomain.start();
        privateContext->triggerEvent(doMove);
        privateContext->triggerEvent(doGrasping);
    });

    slMoving.setLevelAction([&](SafetyContext *privateContext) {
        cs.timedomain.start();
        privateContext->triggerEvent(doGrasping);
        privateContext->triggerEvent(doRobotStop);
    });    

    slGrasping.setLevelAction([&](SafetyContext *privateContext) {
        cs.timedomain.start();
        privateContext->triggerEvent(doGraspingStop);
    });

    // Define entry level
    setEntryLevel(slPowerOff);

    // Define exit function
    exitFunction = ([&](SafetyContext *privateContext) {
        privateContext->triggerEvent(doShutDown);
    });
}
