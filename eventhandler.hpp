#pragma once
#ifndef EVENT_HANDLER_HPP
#define EVENT_HANDLER_HPP
#include <map>
#include <string>
#include <functional>

struct Entity;


using Callable = std::function<void(Entity*, Entity*)>;
using Condition = std::function<bool(Entity*, Entity*)>;



struct Event {
    Event(Condition cond, Callable call) { 
        condition = cond;
        callback = call;
    }
    
    Callable callback;
    Condition condition;
};

class EventHandler {
public:
    void trigger(const std::string& _trigName, Entity * _target);    
    void attach(const std::string& _trigName, Condition cond, Callable call ); 
private:
    Entity * source;
    std::map<std::string, Event> events;
};











#endif /* EVENT_HANDLER_HPP */