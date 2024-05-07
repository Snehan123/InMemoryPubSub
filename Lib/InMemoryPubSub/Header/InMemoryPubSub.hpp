#pragma once
#include"./../../Topic/Header/Topic.h"
#include"./../../SubscriberGroup/Header/SubscriberGroup.hpp"
#include"./../../Subscriber/Header/Subscriber.hpp"
#include<map>
#include<unordered_map>
#include<set>
#include<vector>

class InMemoryPubSub{
private:
    unordered_map<shared_ptr<Topic>,vector<shared_ptr<SubscriberGroup>>> topicToSubscriberGroupMap;
    unordered_map<shared_ptr<SubscriberGroup>,vector<shared_ptr<Subscriber>>> subscriberGroupToSubscriberMap;
    std::unordered_map<string,shared_ptr<Topic>> topicList;
    std::unordered_map<string,shared_ptr<SubscriberGroup>> subscriberGroupList;
    // std::set<string,shared_ptr<Topic>> topicList;
public:

    InMemoryPubSub();
    bool addTopic(string topicName);
    bool addSubscriberGroup(string subscriberGroupName, string topicName);
    shared_ptr<Subscriber> addSubscriber(string subscriber, string subscriberGroupName);
    bool publish(string topicName, void* data);


};