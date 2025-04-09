#include <InteractionListener.h>

class ConsoleListener : public InteractionListener {
public:
    ConsoleListener() = default;
    ~ConsoleListener() override = default;

    void interact(void* actor, void* data) override {
        std::cout << "Interaction occurred!" << std::endl;
        std::cout << *((std::string*) data) << std::endl; // Assuming data is a string or can be printed directly
    }

    std::shared_ptr<Vector2D> getPosition() override {
        return std::make_shared<Vector2D>(0,0); // No specific position needed for console interaction
    }

private:
    std::function<void()> func; // Function to be called on interaction
};