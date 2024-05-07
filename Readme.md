Structure::

InMemoryPubSub is the main Application.
It accepts addition of topic, subscriberGroup(topic), subscriber(subscriber group).

Anyone can call publish method on it with void* data and topic name. After adding to the queue, the publisher thread will release the semaphore for all the subcriber group to that topic.

Subscriber object will be returned when a new subscriber comes to register. Subscriber will call get Data on subscriber object which will try to acquire lock on the subGroup. SubGroup is ponted by each subscriber object.

After getting the token froms semaphore, it will call topic.getData.

Locking for consuming and pubslishing is not implemented yet. It should be implemented in the queue.
For publishing a publisher lock can be used.
For subscriber a subscriber lock for each subscriber group index can be used.









g++ Lib/DoublyLinkedList/Source/Node.cpp Lib/DoublyLinkedList/Source/DoublyLinkedList.cpp Lib/Topic/Source/Topic.cpp Lib/SubscriberGroup/Source/SubscriberGroup.cpp Lib/Subscriber/Source/Subscriber.cpp Lib/InMemoryPubSub/Source/InMemoryPubSub.cpp     Test/test.cpp 