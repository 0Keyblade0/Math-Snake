#include "snake.hxx"
#include <cmath>

// Construct the snake.
Snake::Snake()
        : head(Snake_part{9, 8}),
          fake_head(Temp_position {9, 8}),
          body(std::vector<Snake_part>{}),
          velocity(Velocity{0, 0}),
          live(false)
{ }

// Snake hits boundary if the snake is off the board.
// The board will always be 19 x 17
bool Snake::hits_boundary() const
{
    return  (head.x < 0 or head.x > 19 or
             head.y < 0 or head.y > 17);
}

// The snake hits itself if the head is in the
// same position as a part of its body
bool Snake::hits_self() const
{
    for (auto i : body) {
        if (head.x == i.x and head.y == i.y) {
            return true;
        }
    }
    return false;
}

// Snake is at food if the head has te same position as a food
bool
Snake::at_food(const std::vector<Food>& foods) const
{
    for (auto & food : foods) {
        if (head == food.pos) {
            return true;
        }
    }
    return false;
}

// Same process as at_food but returns the food
Food Snake::which_food(const std::vector<Food>& foods)
{
    for (auto & food : foods) {
        if (head == food.pos) {
            return food;
        }
    }
    return Food{Position {100,100}, 0};

}

// Add an index to the snake body. Initialize off-screen
// eventually it will show up behind the head
void Snake::longer()
{
    Snake_part tail = Snake_part{100, 100};
    body.push_back(tail);
}

// Remove index from the snake body.
void Snake::shorter()
{
    body.pop_back();
}

// The head will move in the direction of the given velocity. The first part
// of the snake body will then move to the head's previous spot. The second
// part of te snake body will then move to the first's parts previous spot.
// Repeat this process until you reach the end of the snake body.
Snake
Snake::next(double dt) const
{
    Snake result(*this);
    Snake_part temp_head = head;
    result.fake_head.x += dt * result.velocity.width;
    result.fake_head.y += dt * result.velocity.height;

    if (result.velocity.width < 0) {
        result.head.x = floor(result.fake_head.x);
    } else if (result.velocity.width > 0) {
        result.head.x = ceil(result.fake_head.x);
    }

    if (result.velocity.height < 0) {
        result.head.y = floor(result.fake_head.y);
    } else if (result.velocity.height > 0) {
        result.head.y = ceil(result.fake_head.y);
    }
    if (temp_head != result.head) {
        for (auto & i : result.body) {
            Snake_part intermediate = temp_head;
            temp_head = i;
            i = intermediate;
        }
    }
    return result;
}

bool
operator==(Snake const& a, Snake const& b)
{
    if (a.body.size() == b.body.size()) {
        for (size_t i = 0; i < a.body.size(); i++) {
            if (a.body[i] != b.body[i]) {
                return false;
            }
        }
    } else {
        return false;
    }
    return (a.head == b.head and
            a.fake_head == b.fake_head and
            a.velocity == b.velocity and
            a.live == b.live);
}

bool
operator!=(Snake const& a, Snake const& b)
{
    return !(a == b);
}

std::ostream&
operator<<(std::ostream& o, Snake const& snake) {
    // Shows the contents of the given snake
    o << "Snake{\n";
    o << "Head: X: " << snake.head.x << " Y: " << snake.head.y << "\n";
    o << "Fake Head X: " << snake.fake_head.x << " Y: " << snake.fake_head.y << "\n";
    o << "Body{\n";
    for (size_t i = 0; i < snake.body.size(); i++) {
        o << "Part " << i << ": X: " << snake.body[i].x << " Y: " << snake.body[i].y << "\n";
    }
    o << "}\n";
    o << "Velocity: X: " << snake.velocity.width << " Y: " << snake.velocity.height << "\n";
    o << "Live: " << snake.live << "\n";
    return o << "}";
}


