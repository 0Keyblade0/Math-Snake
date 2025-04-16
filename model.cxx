#include "model.hxx"


Model::Model()
        : number1(0),
          number2(0),
          snake(Snake{}),
          board({0, 0, 19, 17}),
          all_food({}),
          correct_answer(number1 * number2),
          num_correct(0),
          num_incorrect(0),
          num_deaths(0),
          combiner_operator(0),
          decider(4)

{
    next_set();
}

// Makes snake live
void
Model::launch() {
    snake.live = true;
}

// Chooses, at random, the type of the next question,
// and its numbers
void
Model::next_set()
{;
    all_food.clear();
    combiner_operator = decider.next();
    if (combiner_operator == 0) {
        next_set_add();
    } else if (combiner_operator == 1) {
        next_set_sub();
    } else if (combiner_operator == 2) {
        next_set_mul();
    } else if (combiner_operator == 3) {
        next_set_div();
    }
}

// Position is not snake if there is not a snake_part at the position
bool
Model::position_not_snake(Snake snake, Position posn) {
    if (posn == snake.head) {
        return false;
    }
    for (size_t k = 0; k < snake.body.size(); k++) {
        if (posn == snake.body[k]) {
            return false;
        }
    }
    return true;
}


bool
Model::not_same_food_pos(std::vector<Food> curr_foods, Position position) {
    for (size_t k = 0;  k < curr_foods.size(); k++) {
        if (curr_foods[k].pos == position) {
            return false;
        }
    }
    return true;
}

void
Model::next_set_add()
{
    ge211::Random_source<int> range(101);
    number1 = range.next();
    number2 = range.next();
    correct_answer = number1 + number2;
    for (size_t i = 0; i < 3; i++) {
        Position new_position = {range.next_between(0, 18),
                                 range.next_between(0, 16)};
        while (!(not_same_food_pos(all_food, new_position) and
                position_not_snake(snake, new_position))) {
            new_position.x = range.next_between(0, 18);
            new_position.y = range.next_between(0, 16);
        }
        Food new_food = Food{new_position, correct_answer};
        if (i == 0) {
            if (number1 + 20 > 100) {
                new_food.value = number2 + (range.next_between(number1 - 20, 100));
            } else if (number1 - 20 < 0) {
                new_food.value = number2 + (range.next_between(0, number1 + 20));
            } else {
                new_food.value = number2 + (range.next_between(number1 - 20, number1 + 20));
            }
        } else if (i == 1) {
            if (number2 + 20 > 100) {
                new_food.value = number1 + (range.next_between(number2 - 20, 100));
            } else if (number1 - 20 < 0) {
                new_food.value = number1 + (range.next_between(0, number2 + 20));
            } else {
                new_food.value = number1 + (range.next_between(number2 - 20, number2 + 20));
            }
        } else {
            new_food.value = correct_answer;
        }

        if (i != 2 and new_food.value == correct_answer) {
            if (i == 0) {
                new_food.value += 5;
            } else {
                new_food.value += 3;
            }
        }

        all_food.push_back(new_food);

        /*
        if (not_same_food_pos_val(all_food, new_food) and
            position_not_snake(snake, new_food.pos)) {
            all_food.push_back(new_food);
        } else {
            i--;
        }
         */
    }
}

void
Model::next_set_sub() {
    ge211::Random_source<int> range(101);
    number1 = range.next();
    number2 = range.next();
    if (number1 < number2) {
        int temp = number1;
        number1 = number2;
        number2 = temp;
    }
    correct_answer = number1 - number2;
    for (size_t i = 0; i < 3; i++) {
        Position new_position = {range.next_between(0, 18),
                                 range.next_between(0, 16)};
        while (!(not_same_food_pos(all_food, new_position) and
                 position_not_snake(snake, new_position))) {
            new_position.x = range.next_between(0, 18);
            new_position.y = range.next_between(0, 16);
        }
        Food new_food = {new_position, correct_answer};
        if (i == 0 or i == 1) {
            if (number2 - 20 < 0) {
                if (number2 + 20 > number1) {
                    int temp_num =  (range.next_between(0, number1 + 5));
                    if (temp_num < number1) {
                        new_food.value = number1 - temp_num;
                    } else {
                        new_food.value = temp_num - number1;
                    }
                } else {
                    new_food.value = number1 - (range.next_between(0, number2 + 20));
                }
            } else {
                if (number2 + 20 < number1) {
                    new_food.value = number1 - (range.next_between(number2 - 20, number2 + 20));
                } else {
                    new_food.value = number1 + (range.next_between(number2 - 20, number2));
                }

            }
        } else {
            new_food.value = correct_answer;
        }

        if (i != 2 and new_food.value == correct_answer) {
            if (i == 0) {
                new_food.value += 5;
            } else {
                new_food.value += 3;
            }
        }

        all_food.push_back(new_food);

        /*
        if (not_same_food_pos_val(all_food, new_food) and
            position_not_snake(snake, new_food.pos)) {
            all_food.push_back(new_food);
        } else {
            i--;
        }
         */
    }
}

void Model::next_set_mul()
{
    ge211::Random_source<int> range(21);
    number1 = range.next();
    number2 = range.next();
    correct_answer = number1 * number2;
    for (size_t i = 0; i < 3; i++) {
        Position new_position = {range.next_between(0, 18),
                                 range.next_between(0, 16)};
        while (!(not_same_food_pos(all_food, new_position) and
                 position_not_snake(snake, new_position))) {
            new_position.x = range.next_between(0, 18);
            new_position.y = range.next_between(0, 16);
        }
        Food new_food = Food{new_position, correct_answer};
        if (i == 0) {
            if (number1 + 5 > 20) {
                new_food.value = number2 * (range.next_between(number1 -5, 20));
            } else if (number1 - 5 < 0) {
                new_food.value = number2 * (range.next_between(0, number1 + 5));
            } else {
                new_food.value = number2 * (range.next_between(number1 - 5, number1 + 5));
            }
        } else if (i == 1) {
            if (number2 + 5 > 20) {
                new_food.value = number1 * (range.next_between(number2 -5, 20));
            } else if (number1 - 5 < 0) {
                new_food.value = number1 * (range.next_between(0, number2 + 5));
            } else {
                new_food.value = number1 * (range.next_between(number2 - 5, number2 + 5));
            }
        } else {
            new_food.value = correct_answer;
        }

        if (i != 2 and new_food.value == correct_answer) {
            if (i == 0) {
                new_food.value += 5;
            } else {
                new_food.value += 3;
            }
        }

        all_food.push_back(new_food);

        /*
        if (not_same_food_pos_val(all_food, new_food) and
            position_not_snake(snake, new_food.pos)) {
            all_food.push_back(new_food);
        } else {
            i--;
        }
         */
    }
}

void
Model::next_set_div()
{
    ge211::Random_source<int> range(101);
    ge211::Random_source<int> range_num1(101);
    ge211::Random_source<int> range_num2(11);
    number1 = range_num1.next();
    number2 = range_num2.next();
    if (number1 < number2) {
        int temp = number1;
        number1 = number2;
        number2 = temp;
    }

    while (number1 % number2 != 0) {
        number1--;
    }

    correct_answer = number1 / number2;

    for (size_t i = 0; i < 3; i++) {
        Position new_position = {range.next_between(0, 18),
                                 range.next_between(0, 16)};
        while (!(not_same_food_pos(all_food, new_position) and
                 position_not_snake(snake, new_position))) {
            new_position.x = range.next_between(0, 18);
            new_position.y = range.next_between(0, 16);
        }
        Food new_food = {new_position, correct_answer};

        if (i == 0 or i == 1) {
            if (correct_answer + 10 > 100) {
                new_food.value = range.next_between(correct_answer - 10, 100);
            } else if (number1 - 10 < 0) {
                new_food.value = range.next_between(0, correct_answer + 10);
            } else {
                new_food.value = range.next_between(correct_answer - 10, number1 + 10);
            }
        } else {
            new_food.value = correct_answer;
        }


        if (i != 2 and new_food.value == correct_answer) {
            if (i == 0) {
                new_food.value += 5;
            } else {
                new_food.value += 3;
            }
        }

        all_food.push_back(new_food);
    }

}

bool
Model::snake_correct(Food food) const
{
    return (food.value == correct_answer);
}

void Model::on_frame(double dt)
{
    if (snake.live) {
        Snake next_snake = snake.next(dt);
        if (next_snake.hits_boundary() or
            next_snake.hits_self()) {
            num_deaths++;
            snake = Snake{};
        } else if (next_snake.at_food(all_food)) {
            Food food_at = next_snake.which_food(all_food);
            if (snake_correct(food_at)) {
                snake.longer();
                num_correct++;
                snake = snake.next(dt);
                next_set();
            } else {
                if (snake.body.empty()) {
                    snake = Snake{};
                    num_deaths++;
                    next_set();
                } else {
                    snake.shorter();
                    snake = snake.next(dt);
                    next_set();
                }
                num_incorrect++;
            }
        } else {
            snake = snake.next(dt);
        }
    }
}


