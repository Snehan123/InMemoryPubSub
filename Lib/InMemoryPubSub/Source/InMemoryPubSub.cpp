#include"./../Header/InMemoryPubSub.hpp"

InMemoryPubSub::InMemoryPubSub(){
    topicToSubscriberGroupMap.clear();
    subscriberGroupToSubscriberMap.clear();
}

bool InMemoryPubSub::addTopic(string topicName){
    if(topicList.count(topicName)>0){
        return 0;
    }

    shared_ptr<Topic> currTopic = make_shared<Topic>(topicName);
    topicList[topicName] = currTopic;
    // topicToSubscriberGroupMap[currTopic] = {};
    return 1;
}

bool InMemoryPubSub::addSubscriberGroup(string subscriberGroupName, string topicName){
    if(subscriberGroupList.count(subscriberGroupName)>0){
        return 0;
    }
    if(topicList.count(topicName)>0){
        return 0;
    }
    auto topicPtr = topicList[topicName];
    shared_ptr<SubscriberGroup> currSubGroup  = make_shared<SubscriberGroup>(subscriberGroupName,topicPtr);
    topicToSubscriberGroupMap[topicPtr].push_back(currSubGroup);
}

shared_ptr<Subscriber> InMemoryPubSub::addSubscriber(string subscriber, string subscriberGroupName){
    if(subscriberGroupList.count(subscriberGroupName)>0){
        return 0;
    }
    auto subGrpPtr = subscriberGroupList[subscriberGroupName];
    shared_ptr<Subscriber> currSub = make_shared<Subscriber>(subGrpPtr,subscriber);
    subscriberGroupToSubscriberMap[subGrpPtr].push_back(currSub);
    return currSub;
}

bool InMemoryPubSub::publish(string topicName, void* data){
    if(topicList.count(topicName)>0){
        return 0;
    }
    shared_ptr<Topic> currTopic = make_shared<Topic>(topicName);   

    if(currTopic->publish(data)==0)return 0;

    for(auto subGrp: topicToSubscriberGroupMap[currTopic]){
        subGrp->notify();
    }
    return true;
}