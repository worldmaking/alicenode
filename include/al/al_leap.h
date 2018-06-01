#ifndef AL_LEAP_H
#define AL_LEAP_H

#include "al_console.h"

#include "leap/LeapC.h"
#include "leap/Leap.h"

//using namespace Leap;


struct LeapMotion : public Leap::Listener {

    Leap::Controller controller; 
    
    bool connect() {
       controller.addListener(*this);
       return true;
    }

    virtual void onConnect(const Leap::Controller&) {
        console.log("Leap connected!!!!!!!");
        //controller.addListener(Listener);
        controller.enableGesture(Leap::Gesture::TYPE_SWIPE);
        controller.config().setFloat("Gesture.Swipe.MinLength", 200.0);
        controller.config().save();
    }

    virtual void onDisconnect(const Leap::Controller&) {
        console.log("Leap disconnected");
    }

    virtual void onFrame(const Leap::Controller&) {
        Leap::Frame frame = controller.frame();

        //Get Hands
        Leap::HandList hands = frame.hands();
        //Leap::Hand hand = frame.hands();
        Leap::Hand hand = frame.hands().rightmost();
        Leap::Vector position = hand.palmPosition();
        Leap::Vector velocity = hand.palmVelocity();
        Leap::Vector direction = hand.direction();

        //Get Fingers
        Leap::PointableList pointables = frame.pointables();
        Leap::Pointable pointable = frame.pointables().frontmost();
        Leap::FingerList fingers = frame.fingers();
        
        Leap::ToolList tools = frame.tools();

        //Get Arm
        //Leap::Arm arm = hand.arm(); 

        if (pointable.isTool()) {
            Leap::Tool tool = Leap::Tool(pointable);
        } else {
            Leap::Finger finger = Leap::Finger(pointable);
        }

        fingers = frame.hands()[0].fingers();
        for(Leap::FingerList::const_iterator fl = fingers.begin(); fl != fingers.end(); fl++){
        Leap::Bone bone;
        Leap::Bone::Type boneType;
        
            for(int b = 0; b < 4; b++)
            {
                boneType = static_cast<Leap::Bone::Type>(b);
                bone = (*fl).bone(boneType);
                std::cout << "Finger index: " << (*fl).type() << " " << bone << std::endl;
            }
        }

    }

    virtual void onServiceConnect(const Leap::Controller& controller) {
        std::cout << "Service connected " << std::endl;
    }

    virtual void onServiceDisconnect(const Leap::Controller&) {
        std::cout << "Service disconnected " << std::endl;
    }

    virtual void onServiceChange(const Leap::Controller& controller) {
        std::cout << "Service state change " << std::endl;
    }

    /*
    int main(int argc, char** argv) {
        std::cout << "Press Enter to quit, or enter 'p' to pause or unpause the service..." << std::endl;

        bool paused = false;
        while (true) {
            char c = std::cin.get();
            if (c == 'p') {
            paused = !paused;
            controller.setPaused(paused);
            std::cin.get(); //skip the newline
            }
            else
            break;
        }
    }
    */

};


#endif