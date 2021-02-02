import Impl 1.0

ButtonPanel { 
    TimeModel { // this class is defined in C++ (plugin.cpp)
            id: time
        }

        hours: time.hour
        minutes: time.minute

}
