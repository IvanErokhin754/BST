
#include <SFML/Graphics.hpp>
#include "BinaryTree.hpp"

#include <optional>
#include <string>
#include <exception>

void DrawNode(sf::RenderWindow& window, float x, float y, float radius, bool highlighted = false) {
    sf::CircleShape circle(radius);

    circle.setOrigin({radius, radius});
    circle.setPosition({x, y});

    circle.setFillColor(
        highlighted ? sf::Color::Green : sf::Color::White
    );

    circle.setOutlineColor(sf::Color::Black);
    circle.setOutlineThickness(3.f);

    window.draw(circle);
}

void DrawEdge(sf::RenderWindow& window, float x1, float y1, float x2, float y2) {
    sf::VertexArray line(sf::PrimitiveType::Lines, 2);

    line[0].position = {x1, y1};
    line[1].position = {x2, y2};

    line[0].color = sf::Color::Black;
    line[1].color = sf::Color::Black;

    window.draw(line);
}

void DrawText(sf::RenderWindow& window, const sf::Font& font, float x, float y, const char* txt) {
    sf::Text text(font, txt, 24);

    auto bounds = text.getLocalBounds();

    text.setFillColor(sf::Color::Black);

    text.setOrigin({
        bounds.position.x + bounds.size.x / 2.f,
        bounds.position.y + bounds.size.y / 2.f
    });

    text.setPosition({x, y});

    window.draw(text);
}

template<typename NodePtr>
void DrawTree(sf::RenderWindow& window, const sf::Font& font, NodePtr node, float x, float y, float offset, const std::optional<int>& highlighted) {
    if (node == nullptr)
        return;

    const float levelHeight = 100.f;
    const float radius = 30.f;

    if (node->left != nullptr) {
        float childX = x - offset;
        float childY = y + levelHeight;

        DrawEdge(window, x, y, childX, childY);

        DrawTree(window, font, node->left, childX, childY, offset / 2.f, highlighted);
    }

    if (node->right != nullptr) {
        float childX = x + offset;
        float childY = y + levelHeight;

        DrawEdge(window, x, y, childX, childY);

        DrawTree(window, font, node->right, childX, childY, offset / 2.f, highlighted);
    }

    bool isHighlighted = highlighted.has_value() && node->value == highlighted.value();

    DrawNode(window, x, y, radius, isHighlighted);

    std::string value = std::to_string(node->value);
    DrawText(window, font, x, y, value.c_str());
}

int main() {
    BinaryTree<int> tree;

    for (int value : {50, 30, 70, 20, 40, 60, 80}) {
        tree.Insert(value);
    }

    sf::RenderWindow window(
        sf::VideoMode({800, 600}),
        "AVL Tree Visualizer"
    );

    sf::Font font;

    if (!font.openFromFile("font.ttf"))
        return 1;

    window.setKeyRepeatEnabled(false);

    auto it = tree.GetEnumerator();
    std::optional<int> highlighted;

    enum class Mode {
        None,
        Insert,
        Remove
    };

    Mode mode = Mode::None;

    std::string input;
    std::string message = "I: Insert | D: Remove | Space: Next";

    while (window.isOpen()) {
        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
                window.close();
            }

            if (const auto* key = event->getIf<sf::Event::KeyPressed>()) {

                if (key->code == sf::Keyboard::Key::I && mode == Mode::None) {
                    mode = Mode::Insert;
                    input.clear();
                }

                else if (key->code == sf::Keyboard::Key::D && mode == Mode::None) {
                    mode = Mode::Remove;
                    input.clear();
                }

                else if (key->code == sf::Keyboard::Key::Escape) {
                    mode = Mode::None;
                    input.clear();
                }

                else if (key->code == sf::Keyboard::Key::Backspace && mode != Mode::None && !input.empty()) {
                    input.pop_back();
                }

                else if (key->code == sf::Keyboard::Key::Space && mode == Mode::None && it->HasNext()) {
                    highlighted = it->Next();
                }

                else if (key->code == sf::Keyboard::Key::Enter && mode != Mode::None) {
                    try {
                        if (input.empty() || input == "-") {
                            throw std::invalid_argument("Empty input");
                        }

                        int value = std::stoi(input);

                        if (mode == Mode::Insert) {
                            tree.Insert(value);

                            message = "Inserted: " + std::to_string(value);
                        }

                        else {
                            tree.Remove(value);

                            message = "Removed: " + std::to_string(value);
                        }

                        it = tree.GetEnumerator();
                        highlighted.reset();
                    }

                    catch (const std::exception&) {
                        message = "Operation failed";
                    }

                    mode = Mode::None;
                    input.clear();
                }
            }

            if (const auto* text = event->getIf<sf::Event::TextEntered>()) {

                if (mode != Mode::None) {
                    char32_t ch = text->unicode;

                    if (ch >= '0' && ch <= '9') {
                        input += static_cast<char>(ch);
                    }
                    else if (ch == '-' && input.empty()) {
                        input += '-';
                    }
                }
            }
        }

        window.clear(sf::Color::White);

        DrawTree(window, font, tree.GetRoot(),
                 400.f, 100.f, 180.f, highlighted);

        std::string status = message;

        if (mode == Mode::Insert) {
            status = "Insert: " + input;
        }
        else if (mode == Mode::Remove) {
            status = "Remove: " + input;
        }

        DrawText(window, font, 400.f, 550.f,
                 status.c_str());

        window.display();
    }

    return 0;
}
