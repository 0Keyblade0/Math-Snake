#include "controller.hxx"

Controller::Controller(Model& model)
        : model_(model),
          view_(model)
{ }

///
/// CONTROLLER FUNCTIONS
///

void
Controller::on_key(ge211::Key key)
{
    if ((key == ge211::Key::left() or key == ge211::Key::code('a')) and
        model_.snake.velocity != Velocity {5, 0}) {
        model_.snake.velocity = {-5, 0};
        model_.launch();
    } else if ((key == ge211::Key::right() or key == ge211::Key::code('d')) and
               model_.snake.velocity != Velocity {-5, 0}) {
        model_.snake.velocity = {5, 0};
        model_.launch();
    } else if ((key == ge211::Key::up()  or key == ge211::Key::code('w')) and
               model_.snake.velocity != Velocity {0, 5}) {
        model_.snake.velocity = {0, -5};
        model_.launch();
    } else if ((key == ge211::Key::down() or key == ge211::Key::code('s')) and
               model_.snake.velocity != Velocity {0, -5}) {
        model_.snake.velocity = {0, 5};
        model_.launch();
    } else if (key == ge211::Key::code('q')) {
        quit();
    }
}

// Makes the snake live
void
Controller::on_mouse_up(ge211::Mouse_button, ge211::Posn<int>)
{
    model_.launch();
}

//
// Forwarding functions
//

void
Controller::on_frame(double dt)
{
    model_.on_frame(dt);
}

ge211::Dims<int>
Controller::initial_window_dimensions() const
{
    return view_.initial_window_dimensions();
}

void
Controller::draw(ge211::Sprite_set& set)
{
    view_.draw(set);
}

