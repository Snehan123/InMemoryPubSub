#include"./../Header/InMemoryPubSub.hpp"
#include"./../../globals.h"
InMemoryPubSub::InMemoryPubSub(){
    if(debug){
        cout<<"["<<__FUNCTION__<<" "<<__LINE__<<"] "<<"Initialising InmemoryPubSub\n"<<endl;
    }
    topicToSubscriberGroupMap.clear();
    subscriberGroupToSubscriberMap.clear();
}

bool InMemoryPubSub::addTopic(string topicName){
    if(debug){
        cout<<"["<<__FUNCTION__<<" "<<__LINE__<<"] "<<"Entering Add Topic\n"<<endl;
    }
    if(topicList.count(topicName)>0){
        return 0;
    }

    if(debug){
        cout<<"["<<__FUNCTION__<<" "<<__LINE__<<"] "<<"Topic does not exist.\n"<<endl;
    }

    std::shared_ptr<Topic> currTopic = std::make_shared<Topic>(topicName);
    if(debug){
        cout<<"["<<__FUNCTION__<<" "<<__LINE__<<"] "<<"Made SharedPtr.\n"<<endl;
    }
    topicList[topicName] = currTopic;
    if(debug){
        cout<<"["<<__FUNCTION__<<" "<<__LINE__<<"] "<<"Entering Add Topic\n"<<endl;
    }
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
    if(topicList.count(topicName)==0){
        return 0;
    }
    if(debug){
        cout<<"["<<__FUNCTION__<<" "<<__LINE__<<"] "<<"Publishing to matching topic\n"<<endl;
    }
    
    shared_ptr<Topic> currTopic = topicList[topicName];

    if(debug){
        cout<<"["<<__FUNCTION__<<" "<<__LINE__<<"] "<<"Got The topic Ptr. Publishing data.\n"<<endl;
    }

    if(currTopic->publish(data)==0)return 0;

    for(auto subGrp: topicToSubscriberGroupMap[currTopic]){
        if(debug){
            cout<<"["<<__FUNCTION__<<" "<<__LINE__<<"] "<<"Notifying subscriber grp\n"<<endl;
        }
        subGrp->notify();
    }
    return true;
}