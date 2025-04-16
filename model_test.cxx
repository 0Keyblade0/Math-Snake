#include "model.hxx"
#include <catch.hxx>

/*
 Requirements Shown:
 1. Snake can move in one direction at a time
 2. Snake dies when its head hits its body
 3. Snake dies when its  head goes past the boundary
 4. When the snake answers correctly it gets longer
 5. When the snake answers incorrectly it gets shorter
 6. If the snake answers incorrectly and does not have body, then it dies
 7. When the snake answers, a new question is asked (set is made)
 8. A set can use addition, subtraction, multiplication, and division
 9. The number of incorrect answers is being calculated (tracked)
 10. The number of correct answers is being calculated (tracked)
 11. The number of deaths is being calculated (tracked)
 */

TEST_CASE("Snake moving freely")
{
    Model m;

    // Get rid of all the bricks and make the ball move slowly upward so
    // we don't hit anything:
    m.all_food.clear();
    m.snake.velocity = {5, 0};
    m.snake.live = true;

    // Make a copy of the ball's position, which we'll use to compute
    // where we expect the ball to go.
    Temp_position expected_place = m.snake.fake_head;
    Snake_part expected_head = m.snake.head;

    CHECK(m.snake.fake_head == expected_place);
    CHECK(m.snake.head == expected_head);

    // If the model advances by 0.5 s then we expect the center to move
    // accordingly:
    m.on_frame(0.5);
    expected_place.x += 0.5 * m.snake.velocity.width;
    expected_place.y += 0.5 * m.snake.velocity.height;
    expected_head.x = ceil(expected_place.x);
    expected_head.y = ceil(expected_place.y);

    CHECK(m.snake.fake_head == expected_place);
    CHECK(m.snake.head == expected_head);

    // Again, but only 0.25 s this time.
    m.on_frame(0.25);
    expected_place.x += 0.25 * m.snake.velocity.width;
    expected_place.y += 0.25 * m.snake.velocity.height;
    expected_head.x = ceil(expected_place.x);
    expected_head.y = ceil(expected_place.y);

    CHECK(m.snake.fake_head == expected_place);
    CHECK(m.snake.head == expected_head);

    // Again, but 0.125 s this time.
    m.on_frame(0.125);
    expected_place.x += 0.125 * m.snake.velocity.width;
    expected_place.y += 0.125 * m.snake.velocity.height;
    expected_head.x = ceil(expected_place.x);
    expected_head.y = ceil(expected_place.y);

    CHECK(m.snake.fake_head == expected_place);
    CHECK(m.snake.head == expected_head);

    // Change velocity so the head moves up
    m.snake.velocity = {0, 5};

    m.on_frame(0.5);
    expected_place.x += 0.5 * m.snake.velocity.width;
    expected_place.y += 0.5 * m.snake.velocity.height;
    expected_head.x = ceil(expected_place.x);
    expected_head.y = ceil(expected_place.y);

    CHECK(m.snake.fake_head == expected_place);
    CHECK(m.snake.head == expected_head);

    // Again, but only 0.25 s this time.
    m.on_frame(0.25);
    expected_place.x += 0.25 * m.snake.velocity.width;
    expected_place.y += 0.25 * m.snake.velocity.height;
    expected_head.x = ceil(expected_place.x);
    expected_head.y = ceil(expected_place.y);

    CHECK(m.snake.fake_head == expected_place);
    CHECK(m.snake.head == expected_head);

    // Again, but 0.125 s this time.
    m.on_frame(0.125);
    expected_place.x += 0.125 * m.snake.velocity.width;
    expected_place.y += 0.125 * m.snake.velocity.height;
    expected_head.x = ceil(expected_place.x);
    expected_head.y = ceil(expected_place.y);

    CHECK(m.snake.fake_head == expected_place);
    CHECK(m.snake.head == expected_head);

}
TEST_CASE("Snake correct") {
    Model m;

    // Make snake longer
    m.snake.longer();
    m.on_frame(0.100);
    m.snake.longer();
    m.on_frame(0.100);
    m.snake.longer();
    m.on_frame(0.100);

    CHECK(m.snake.body.size() == 3);

    // Get rid of all the bricks and make the ball move slowly upward so
    // we don't hit anything:
    m.snake.velocity = {5, 0};
    m.snake.live = true;

    // Move snake one block over
    m.on_frame(0.2);
    CHECK_FALSE(m.snake.at_food(m.all_food));
    CHECK(m.num_correct == 0);

    // Snake should be at correct food now
    m.all_food.clear();
    m.correct_answer = 30;
    Food new_food = Food{{11, 8}, 30};
    m.all_food.push_back(new_food);

    m.on_frame(0.2);

    // Reset to set before on _frame
    m.correct_answer = 30;
    new_food = Food{{11, 8}, 30};
    m.all_food.push_back(new_food);

    CHECK(m.snake.at_food(m.all_food));
    CHECK(m.snake_correct(m.snake.which_food(m.all_food)));

    // Check num_correct equals 1
    CHECK(m.num_correct == 1);
    // Check that snake grew
    CHECK(m.snake.body.size() == 4);

    //
    // Snake answers incorrect
    //

    // Clear food for the next set
    m.all_food.clear();
    m.correct_answer = 50;
    CHECK(m.num_incorrect == 0);

    // Add incorrect food to all_food
    new_food = Food{{13, 8}, 30};
    m.all_food.push_back(new_food);

    // Move snake one block over
    m.on_frame(0.2);
    CHECK_FALSE(m.snake.at_food(m.all_food));

    // Snake should be at incorrect food now
    m.on_frame(0.2);

    m.all_food.clear();
    new_food = Food{{13, 8}, 30};
    m.all_food.push_back(new_food);
    m.correct_answer = 50;

    CHECK(m.snake.at_food(m.all_food));
    CHECK_FALSE(m.snake_correct(m.snake.which_food(m.all_food)));

    // Check that number of incorrect questions is 1
    CHECK(m.num_incorrect == 1);
    // Check that snake shrank
    CHECK(m.snake.body.size() == 3);


}
TEST_CASE("Snake dies") {

    Model m;

    // Get rid of all the bricks and make the ball move slowly upward so
    // we don't hit anything:
    m.all_food.clear();
    m.snake.velocity = {5, 0};
    m.snake.live = true;

    // Make the snake longer
    m.snake.longer();
    m.on_frame(0.100);
    m.snake.longer();
    m.on_frame(0.100);
    m.snake.longer();
    m.on_frame(0.100);
    m.snake.longer();
    m.on_frame(0.100);
    m.snake.longer();
    m.on_frame(0.100);
    m.snake.longer();
    m.on_frame(0.100);
    m.snake.longer();
    m.on_frame(0.100);
    m.snake.longer();
    m.on_frame(0.100);


    Snake expected_snake = m.snake;

    CHECK(m.snake == expected_snake);

    m.snake.velocity = {0, 5};
    expected_snake.velocity = {0, 5};
    m.on_frame(0.5);
    expected_snake = expected_snake.next(0.5);

    CHECK(m.snake == expected_snake);

    m.snake.velocity = {-5, 0};
    expected_snake.velocity = {-5, 0};
    m.on_frame(0.5);
    expected_snake = expected_snake.next(0.5);

    CHECK(m.snake == expected_snake);

    m.snake.velocity = {0, -5};
    expected_snake.velocity = {0, -5};
    m.on_frame(0.5);

    // The model snake should hit itself during next frame, meaning
    // a new snake should be expected.
    expected_snake = Snake{};

    // Check that model snake has died by making sure it is a new snake
    CHECK(m.snake == expected_snake);

    // Check number of deaths has increased by one
    CHECK(m.num_deaths == 1);

    //
    // Now snake will die by hitting the boundary
    //

    // Left boundary
    m.snake.live = true;
    m.snake.velocity = {5, 0};
    expected_snake = m.snake;


    // Simulate until snake is about go over boundary
    for (size_t i = 0; i < 10; i++) {
        m.on_frame(0.2);
        expected_snake = expected_snake.next(0.2);
        CHECK(m.snake == expected_snake);
    }

    // Check that snake has not died yet
    CHECK(m.snake != Snake{});

    // Simulate so snake dies
    m.on_frame(0.2);
    expected_snake = expected_snake.next(0.2);
    CHECK(m.snake != expected_snake);

    // Check that snake died
    CHECK(m.snake == Snake{});

    // Check number of deaths has increased by one
    CHECK(m.num_deaths == 2);

    // Right boundary
    m.snake.live = true;
    m.snake.velocity = {-5, 0};
    expected_snake = m.snake;


    // Simulate until snake is about go over boundary
    for (size_t i = 0; i < 8; i++) {
        m.on_frame(0.2);
        expected_snake = expected_snake.next(0.2);
        CHECK(m.snake == expected_snake);
    }

    // Check that snake has not died yet
    CHECK(m.snake != Snake{});

    // Simulate so snake dies
    m.on_frame(0.2);
    expected_snake = expected_snake.next(0.2);
    CHECK(m.snake != expected_snake);

    // Check that snake died
    CHECK(m.snake == Snake{});

    // Check number of deaths has increased by one
    CHECK(m.num_deaths == 3);

    // Top boundary
    m.snake.live = true;
    m.snake.velocity = {0, 5};
    expected_snake = m.snake;


    // Simulate until snake is about go over boundary
    for (size_t i = 0; i < 9; i++) {
        m.on_frame(0.2);
        expected_snake = expected_snake.next(0.2);
        CHECK(m.snake == expected_snake);
    }

    // Check that snake has not died yet
    CHECK(m.snake != Snake{});

    // Simulate so snake dies
    m.on_frame(0.2);
    expected_snake = expected_snake.next(0.2);
    CHECK(m.snake != expected_snake);

    // Check that snake died
    CHECK(m.snake == Snake{});

    // Check number of deaths has increased by one
    CHECK(m.num_deaths == 4);

    // Bottom boundary
    m.snake.live = true;
    m.snake.velocity = {0, -5};
    expected_snake = m.snake;


    // Simulate until snake is about go over boundary
    for (size_t i = 0; i < 7; i++) {
        m.on_frame(0.2);
        expected_snake = expected_snake.next(0.2);
        CHECK(m.snake == expected_snake);
    }

    // Check that snake has not died yet
    CHECK(m.snake != Snake{});

    // Simulate so snake dies
    m.on_frame(0.2);
    expected_snake = expected_snake.next(0.2);
    CHECK(m.snake != expected_snake);

    // Check that snake died
    CHECK(m.snake == Snake{});

    // Check number of deaths has increased by one
    CHECK(m.num_deaths == 5);

    //
    // Check that snake dies when it is incorrect and body is empty
    //

    m.snake.live = true;
    m.snake.velocity = {5, 0};

    // Clear food for the next set
    m.all_food.clear();
    m.correct_answer = 50;

    // Add incorrect food to all_food
    Food new_food = Food{{11, 8}, 30};
    m.all_food.push_back(new_food);

    // Move snake one block over
    m.on_frame(0.2);
    CHECK_FALSE(m.snake.at_food(m.all_food));

    // Snake should be at incorrect food now
    m.on_frame(0.2);

    // Check snake has died
    CHECK(m.snake == Snake{});

    // Check number of deaths has increased by one
    CHECK(m.num_deaths == 6);

}

TEST_CASE("Generating new sets") {
    // Generate combiners in this sequence: +, -, *, /
    Model m;
    m.decider.stub_with({0, 1, 2, 3});

    m.next_set();

    CHECK(m.number1 + m.number2 == m.correct_answer);

    m.next_set();

    CHECK(m.number1 - m.number2 == m.correct_answer);

    m.next_set();

    CHECK(m.number1 * m.number2 == m.correct_answer);

    m.next_set();

    CHECK(m.number1 / m.number2 == m.correct_answer);
}



// These tests should demonstrate at least six of the functional
// requirements.
//
