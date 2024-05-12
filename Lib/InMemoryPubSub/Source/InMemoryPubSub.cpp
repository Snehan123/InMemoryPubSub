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
    if(debug){
        cout<<"["<<__FUNCTION__<<" "<<__LINE__<<"] "<<"SubscriberGroup is NotAlready there.\n"<<endl;
    }
    if(topicList.count(topicName)==0){
        return 0;
    }
    if(debug){
        cout<<"["<<__FUNCTION__<<" "<<__LINE__<<"] "<<"We have topicName.\n"<<endl;
    }
    auto topicPtr = topicList[topicName];
    if(debug){
        cout<<"["<<__FUNCTION__<<" "<<__LINE__<<"] "<<"Got the topic ptr.\n"<<endl;
    }
    shared_ptr<SubscriberGroup> currSubGroup  = make_shared<SubscriberGroup>(subscriberGroupName,topicPtr);
    topicToSubscriberGroupMap[topicPtr].push_back(currSubGroup);
    topicPtr->registerSubscriberGroup(subscriberGroupName);
    subscriberGroupList[subscriberGroupName] = currSubGroup;
}

shared_ptr<Subscriber> InMemoryPubSub::addSubscriber(string subscriber, string subscriberGroupName){

    if(subscriberGroupList.count(subscriberGroupName)==0){
        return 0;
    }
    if(debug){
        cout<<"["<<__FUNCTION__<<" "<<__LINE__<<"] "<<"InMemoryPubSub adding new subscriber\n"<<endl;
    }
    auto subGrpPtr = subscriberGroupList[subscriberGroupName];
    if(debug){
        cout<<"["<<__FUNCTION__<<" "<<__LINE__<<"] "<<"Got the subscriberGroup PtR\n"<<endl;
    }
    shared_ptr<Subscriber> currSub = make_shared<Subscriber>(subGrpPtr,subscriber);
    if(debug){
        cout<<"["<<__FUNCTION__<<" "<<__LINE__<<"] "<<"Created a new subscriber.\n"<<endl;
    }
    subscriberGroupToSubscriberMap[subGrpPtr].push_back(currSub);
    return currSub;
}

bool InMemoryPubSub::publish(string topicName, void* data){
    if(topicList.count(topicName)==0){
        return 0;
    }
    if(debug){
        cout<<"["<<__FUNCTION__<<" "<<__LINE__<<"] "<<"Publishing to matching topic with data "<<*(int*)data<<"\n"<<endl;
    }
    
    shared_ptr<Topic> currTopic = topicList[topicName];

    if(debug){
        cout<<"["<<__FUNCTION__<<" "<<__LINE__<<"] "<<"Got The topic Ptr. Publishing data.\n"<<endl;
    }

    if(currTopic->publish(data)!=0)return 0;

    if(debug){
        cout<<"["<<__FUNCTION__<<" "<<__LINE__<<"] "<<"Iterating Subscriber Group\n"<<endl;
    }

    for(auto subGrp: topicToSubscriberGroupMap[currTopic]){
        if(debug){
            cout<<"["<<__FUNCTION__<<" "<<__LINE__<<"] "<<"Notifying subscriber grp\n"<<endl;
        }
        subGrp->notify();
    }
    return true;
}