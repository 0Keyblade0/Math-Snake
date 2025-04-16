#pragma once

#include "snake.hxx"
#include <ge211_random.hxx>

class Model
{
public:

    // Member Functions
    /// Constructs the model
    explicit Model();

    // Makes the snake live
    void launch();

    // Determines if the given position is not a snake position
    static bool position_not_snake(Snake snake, Position posn);


    // Determines if given food has same position or value as any of the foods
    // currently stored in the model
    static bool not_same_food_pos(std::vector<Food> curr_foods, Position position);

    // Determines if the food that the snake is at is correct
    bool snake_correct(Food food) const;

    // Chooses between making the question addition, subtraction, multiplication,
    // or division
    void next_set();

    // Makes the next_set addition
    void next_set_add();

    // Makes the next set subtraction
    void next_set_sub();

    // Makes the next_set multiplication
    void next_set_mul();

    // Makes next set division
    void next_set_div();

    /// Determines what to do on the given frame
    void on_frame(double dt);


    using Board = ge211::geometry::Rect<int>;


    // Member variables

    /// First term of the combination
    int number1;

    /// Second term of the combination
    int number2;

    // Model snake
    Snake snake;

    /// Model board
    Board board;

    /// All the foods
    std::vector<Food> all_food;

    /// Correct answer to given question
    int correct_answer;

    /// Number of correct questions
    int num_correct;

    /// Number of incorrect questions
    int num_incorrect;

    /// Number of deaths
    int num_deaths;

    /// Represents how the tow numbers will be combined
    int combiner_operator;

    ge211::Random_source<int> decider;
};
