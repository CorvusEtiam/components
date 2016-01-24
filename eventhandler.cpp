#include "eventhandler.hpp"

void EventHandler::trigger(const std::string& _trigName, Entity* _target)
{
    auto it =  events.find(_trigName);
    if ( it != events.end() ) {
        if ( it->second.condition(source, _target) ) {
            it->second.callback(source, _target);
        }
    }
}

void EventHandler::attach(const std::string& _trigName, Condition cond, Callable call ) {
    events.insert({_trigName, Event(cond, call)});
}

   
