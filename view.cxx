#include "view.hxx"


// Convenient type aliases:
using Color = ge211::Color;
using Sprite_set = ge211::Sprite_set;

static ge211::Color const light_green {144, 238, 144};
static ge211::Color const dark_green {1, 50, 32, 50};
static ge211::Color const red {255, 0, 0};
static ge211::Color const purple {160, 32, 240};



// Size of grid squares
static int const grid_height = 36;
static int const grid_width = 36;

View::View(Model const& model)
        : model_(model),
          sans24_({"sans.ttf", 24}),
          sans18_({"sans.ttf", 18}),
          sans21_({"sans.ttf", 18}),
          food_sprite(18, red),
          snake_sprite(Dimensions(36, 36), purple),
          light_green_sprite(Dimensions(36, 36), light_green),
          dark_green_sprite(Dimensions(36, 36), dark_green)


{ }

void
View::draw(ge211::Sprite_set& set) {

    ge211::Text_sprite::Builder builder(sans24_);
    builder.color({255, 255, 255});

    ge211::Text_sprite::Builder builder1(sans18_);
    builder.color({255, 255, 255});

    ge211::Text_sprite::Builder builder2(sans21_);
    builder.color({255, 255, 255});

    builder.add_message("MATH SNAKE");
    title_.reconfigure(builder);
    set.add_sprite(title_, {5, 0}, 4);

    builder1.add_message("Correct:");
    text_correct_.reconfigure(builder1);
    set.add_sprite(text_correct_, {515, 0}, 4);

    builder1.message(ge211::to_string(model_.num_correct));
    num_correct_.reconfigure(builder1);
    set.add_sprite(num_correct_, {650, 0}, 4);

    builder1.message("Incorrect:");
    text_incorrect_.reconfigure(builder1);
    set.add_sprite(text_incorrect_, {515, 18}, 4);

    builder1.message(ge211::to_string(model_.num_incorrect));
    num_incorrect_.reconfigure(builder1);
    set.add_sprite(num_incorrect_, {650, 18}, 4);

    builder1.message("Deaths:");
    text_death_.reconfigure(builder1);
    set.add_sprite(text_death_, {515, 36}, 4);

    builder1.message(ge211::to_string(model_.num_deaths));
    num_deaths_.reconfigure(builder1);
    set.add_sprite(num_deaths_, {650, 36}, 4);

    builder.message("WHAT IS:");
    question_.reconfigure(builder);
    set.add_sprite(question_, {5, 26}, 4);

    int num1_op;

    if (model_.number1 < 10) {
        num1_op = 20;
    } else if (model_.number1 < 100) {
        num1_op = 35;
    } else {
        num1_op = 45;
    }

    if (model_.combiner_operator == 0) {
        builder.message(ge211::to_string(model_.number1));
        number1_.reconfigure(builder);
        set.add_sprite(number1_, {125, 26}, 1);
        builder.message("+");
        combiner_.reconfigure(builder);
        set.add_sprite(combiner_, {125 + num1_op, 26}, 1);
        builder.message(ge211::to_string(model_.number2));
        number2_.reconfigure(builder);
        set.add_sprite(number2_, {125 + num1_op + 20, 26}, 1);
    } else if (model_.combiner_operator == 1) {
        builder.message(ge211::to_string(model_.number1));
        number1_.reconfigure(builder);
        set.add_sprite(number1_, {125, 26}, 1);

        builder.message("-");
        combiner_.reconfigure(builder);
        set.add_sprite(combiner_, {125 + num1_op, 26}, 1);

        builder.message(ge211::to_string(model_.number2));
        number2_.reconfigure(builder);
        set.add_sprite(number2_, {125 + num1_op + 20, 26}, 1);
    } else if (model_.combiner_operator == 2) {
        builder.message(ge211::to_string(model_.number1));
        number1_.reconfigure(builder);
        set.add_sprite(number1_, {125, 26}, 1);
        builder.message("*");
        combiner_.reconfigure(builder);
        set.add_sprite(combiner_, {125 + num1_op, 26}, 1);
        builder.message(ge211::to_string(model_.number2));
        number2_.reconfigure(builder);
        set.add_sprite(number2_, {125 + num1_op + 20, 26}, 1);
    } else if (model_.combiner_operator == 3) {
        builder.message(ge211::to_string(model_.number1));
        number1_.reconfigure(builder);
        set.add_sprite(number1_, {125, 26}, 1);
        builder.message("/");
        combiner_.reconfigure(builder);
        set.add_sprite(combiner_, {125 + num1_op, 26}, 1);
        builder.message(ge211::to_string(model_.number2));
        number2_.reconfigure(builder);
        set.add_sprite(number2_, {125 + num1_op + 20, 26}, 1);
    }

    int num2_question = 125 + num1_op + 20;
    if (model_.number2 < 10) {
        num2_question += 20;
    } else if (model_.number1 < 100) {
        num2_question += 35;
    } else {
        num2_question += 45;
    }
    builder.message("?");
    question_mark_.reconfigure(builder);
    set.add_sprite(question_mark_, {num2_question, 26}, 1);

    int determiner = 0;
    ge211::Rect<int> all_positions = model_.board;
    for (auto pos: all_positions) {
        pos = board_to_screen(pos);
        if (determiner == 0) {
            set.add_sprite(light_green_sprite, pos, 0);
            determiner++;
        } else {
            set.add_sprite(light_green_sprite, pos, 0);
            set.add_sprite(dark_green_sprite, pos, 1);
            determiner--;
        }
    }
    set.add_sprite(snake_sprite, board_to_screen(model_.snake.head), 6);
    for (auto part: model_.snake.body) {
        set.add_sprite(snake_sprite, board_to_screen(part), 6);
    }
    for (size_t i = 0; i < model_.all_food.size(); i++) {
        set.add_sprite(food_sprite, board_to_screen(model_.all_food[i].pos), 4);
        if (i == 0) {
            builder2.message(ge211::to_string(model_.all_food[i].value));
            answer1.reconfigure(builder2);
            Position position = board_to_screen(model_.all_food[i].pos);
            if (model_.all_food[i].value < 10) {
                position.x += 12;
            } else if ((model_.all_food[i].value < 100)) {
                position.x += 8;
            } else {
                position.x += 2;
            }
            set.add_sprite(answer1, position, 5);
        }
        else if (i == 1) {
            builder2.message(ge211::to_string(model_.all_food[i].value));
            answer2.reconfigure(builder2);
            Position position = board_to_screen(model_.all_food[i].pos);
            if (model_.all_food[i].value < 10) {
                position.x += 12;
            } else if ((model_.all_food[i].value < 100)) {
                position.x += 8;
            } else {
                position.x += 2;
            }
            set.add_sprite(answer2, position, 5);
        } else {
            builder2.message(ge211::to_string(model_.all_food[i].value));
            answer3.reconfigure(builder2);
            Position position = board_to_screen(model_.all_food[i].pos);
            if (model_.all_food[i].value < 10) {
                position.x += 12;
            } else if ((model_.all_food[i].value < 100)) {
                position.x += 8;
            } else {
                position.x += 2;
            }
            set.add_sprite(answer3, position, 5);
        }
    }
}

View::Dimensions
View::initial_window_dimensions() const
{

    return {grid_width * model_.board.width,
            grid_height * model_.board.height + (2 * grid_width)} ;
}


Position
View::board_to_screen (Position logical) {
    logical.x *= grid_width;
    logical.y *= grid_height;
    logical.y += (2 * grid_height);
    Position physical = logical;
    return physical;
}

