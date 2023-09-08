

#include "../Nodes/Node.h"

class Frame{
    uint8_t pin_count{};
    bool dirty{};
    Node page;

    public:
    // Node* set_page(Node*);
    Node* free_page();
    void add_pin(){pin_count++;};
    void down_pin(){pin_count--;};
    void set_dirty(bool state){dirty = state;};
    bool is_dirty(){return dirty;};
    uint8_t pin(){return pin_count;};
    uint16_t id(){return page.page_id();};
    Node* get_page(){return &page;};


};