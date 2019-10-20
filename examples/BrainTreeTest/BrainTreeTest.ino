#include <BrainTree.h>

class Action1 : public BrainTree::Node
{
public:
    Status update() override
    {
        Serial.println("Hello from Action Node 1!");
        return Node::Status::Success;
    }
};

class Action2 : public BrainTree::Node
{
public:
    Status update() override
    {
        Serial.println("Hello from Action Node 2!");
        return Node::Status::Success;
    }
};

void manual_construction(){
    BrainTree::BehaviorTree tree;
    shared_ptr<BrainTree::Sequence> sequence(new BrainTree::Sequence);
    
    shared_ptr<Action1> act1(new Action1);
    shared_ptr<Action2> act2(new Action2);
    
    sequence->addChild(act1);
    sequence->addChild(act2);
    tree.setRoot(sequence);
    tree.update();
}

void builder_construction(){
    auto tree = BrainTree::Builder()
        .composite<BrainTree::Sequence>()
            .leaf<Action1>()
            .leaf<Action2>()
        .end()
        .build();
    tree->update();
}

void setup()
{
  Serial.begin(115200);
  manual_construction();
  builder_construction();
}

void loop(){

}