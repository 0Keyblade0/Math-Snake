#pragma once

#include "model.hxx"
#include <ge211_sprites.hxx>



class View {
public:
    /// View dimensions will use `int` coordinates.
    using Dimensions = ge211::Dims<int>;

    /// View positions will use `int` coordinates.
    using Position = ge211::Posn<int>;

    /// Constructs a view that knows about the given model.
    explicit View(Model const &model);

    void draw(ge211::Sprite_set &set);

    Dimensions initial_window_dimensions() const;

    static Position
    board_to_screen(Position logical) ;


private:
    Model const &model_;

    ge211::Font sans24_;
    ge211::Font sans18_;
    ge211::Font sans21_;


    ge211::Circle_sprite const food_sprite;
    ge211::Rectangle_sprite const snake_sprite;
    ge211::Rectangle_sprite const light_green_sprite;
    ge211::Rectangle_sprite const dark_green_sprite;
    ge211::Text_sprite title_;
    ge211::Text_sprite question_;
    ge211::Text_sprite number1_;
    ge211::Text_sprite number2_;
    ge211::Text_sprite combiner_;
    ge211::Text_sprite question_mark_;
    ge211::Text_sprite answer1;
    ge211::Text_sprite answer2;
    ge211::Text_sprite answer3;
    ge211::Text_sprite text_correct_;
    ge211::Text_sprite text_incorrect_;
    ge211::Text_sprite text_death_;
    ge211::Text_sprite num_correct_;
    ge211::Text_sprite num_incorrect_;
    ge211::Text_sprite num_deaths_;

};